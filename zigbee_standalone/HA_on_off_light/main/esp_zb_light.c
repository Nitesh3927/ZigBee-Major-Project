/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee HA_on_off_light Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include "esp_zb_light.h"
#include "esp_attr.h"
#include "esp_check.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "zcl/esp_zigbee_zcl_command.h"
#include "zcl/esp_zigbee_zcl_common.h"
#include "zb_osif_platform.h"


#if !defined ZB_ED_ROLE
#error Define ZB_ED_ROLE in idf.py menuconfig to compile light (End Device) source code.
#endif

static const char *TAG = "ESP_ZB_ON_OFF_LIGHT";

#define CUSTOM_CLUSTER_ID 0xFC00
#define CUSTOM_STRING_MAX_SIZE 255
/********************* Define functions **************************/
static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

static void send_data(packet *data_to_send)
{
    uint8_t buffer[sizeof(packet) + 1];
    buffer[0] = sizeof(packet);
    memcpy(&buffer[1], data_to_send, sizeof(packet));

    esp_zb_zcl_custom_cluster_cmd_req_t custom_req;
    custom_req.zcl_basic_cmd.src_endpoint = HA_ESP_LIGHT_ENDPOINT;
    custom_req.zcl_basic_cmd.dst_endpoint = 1;
    custom_req.zcl_basic_cmd.dst_addr_u.addr_short = 0x0000;
    custom_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    custom_req.cluster_id = CUSTOM_CLUSTER_ID;
    custom_req.custom_cmd_id = 0x01;
    custom_req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    custom_req.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI;
    custom_req.data.type = ESP_ZB_ZCL_ATTR_TYPE_OCTET_STRING;
    custom_req.data.value = buffer;
    custom_req.data.size = sizeof(packet);
    printf("Data Sent: %2f, %2f, %2f, %u, %d\n", data_to_send->latitude, data_to_send->longitude, data_to_send->speed, data_to_send->status, data_to_send->zigbeeAddress);
    esp_zb_zcl_custom_cluster_cmd_req(&custom_req);
}

static void slave_data_read_task() 
{
  packet buffer;
  while (true) {
    int buffer_size = i2c_slave_read_buffer(I2C_NUM_0, (uint8_t *)&buffer, sizeof(packet), pdMS_TO_TICKS(100));
    if (buffer_size == sizeof(packet)) {
      // printf("%u\n", buffer.status);
      switch (buffer.status) {
        case 128: // Car has crashed
          light_driver_set_color_RGB(255, 0, 0);
          buffer.zigbeeAddress = esp_zb_get_short_address();
          send_data(&buffer);
          break;
        case 100: // Caution
          light_driver_set_color_RGB(255, 255, 255);
          break;
        case 32: // A nearby Crash was detected
          light_driver_set_color_RGB(255, 255, 0);
          break;
        case 16: // Lane Change Left
          light_driver_set_color_RGB(0, 255, 255);
          break;
        case 8: // Lane Change Right
          light_driver_set_color_RGB(150, 50, 255);
          break;
        case 4: // Normal Operation
          light_driver_set_color_RGB(0, 255, 0);
          break;
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Start network steering");
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            /* commissioning failed */
            ESP_LOGW(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Joined network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d)",
                     extended_pan_id[0], extended_pan_id[1], extended_pan_id[2], extended_pan_id[3],
                     extended_pan_id[4], extended_pan_id[5], extended_pan_id[6], extended_pan_id[7],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel());
        } else {
            ESP_LOGI(TAG, "Network steering was not successful (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

static esp_err_t zb_custom_req_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    packet received_packet;
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    uint8_t *val = (uint8_t *)message->data.value;
    memcpy(&received_packet, &val[1], sizeof(packet));
    printf("%d\n", esp_zb_rssi_to_lqi(message->info.header.rssi));
    if (received_packet.zigbeeAddress != esp_zb_get_short_address()) {
      printf("Received data(%d): lat=%f, lon=%f, speed=%f, status=%u, addr=%d\n",
        message->data.size,
        received_packet.latitude,
        received_packet.longitude,
        received_packet.speed,
        received_packet.status,
        received_packet.zigbeeAddress);
      i2c_slave_write_buffer(I2C_NUM_0, (uint8_t *)&received_packet, sizeof(packet), pdMS_TO_TICKS(100));
    }
    return ESP_OK;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID:
        ret = zb_custom_req_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

signed int esp_zb_zcl_cluster_check_value_handler(uint16_t attr_id, uint8_t endpoint, uint8_t *value)
{
    printf("check value endpoint:%d, attr: %d\n", endpoint, attr_id);
    return 0;
}

void esp_zb_zcl_cluster_write_attr_handler(uint8_t endpoint, uint16_t attr_id, uint8_t *new_value, uint16_t manuf_code)
{
    printf("write attr endpoint:%d, attr: %d\n", endpoint, attr_id);
    return;
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZED_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();

    esp_zb_on_off_cluster_cfg_t on_off_cfg;
    on_off_cfg.on_off = ESP_ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE;
    esp_zb_attribute_list_t *esp_zb_on_off_cluster = esp_zb_on_off_cluster_create(&on_off_cfg);
    esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_on_off_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

    esp_zb_attribute_list_t *custom_attr = esp_zb_zcl_attr_list_create(CUSTOM_CLUSTER_ID);
    uint8_t custom_value = 0xf0;
    uint8_t custom_string[CUSTOM_STRING_MAX_SIZE] = "_ESPRESSIF";
    custom_string[0] = CUSTOM_STRING_MAX_SIZE - 1;
    uint32_t custom_array[] = {1, 2, 3, 4, 5};
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x01, ESP_ZB_ZCL_ATTR_TYPE_U64, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, &custom_value);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x02, ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_string);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x03, ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_array);
    esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_attr, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_ESP_LIGHT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
    esp_zb_device_register(ep_list);

    esp_zb_zcl_custom_cluster_handlers_t obj = {.cluster_id = CUSTOM_CLUSTER_ID,
                                                .cluster_role = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE,
                                                .check_value_cb = esp_zb_zcl_cluster_check_value_handler,
                                                .write_attr_cb = esp_zb_zcl_cluster_write_attr_handler};
    esp_zb_zcl_custom_cluster_handlers_update(obj);

    esp_zb_core_action_handler_register(zb_action_handler);
    esp_zb_nvram_erase_at_start(1);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_stack_main_loop();
}

void app_main(void)
{
    // I2C device Config
    i2c_config_t i2c_slave_config = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SDA_NUM,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SCL_NUM,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave = {
            .slave_addr = I2C_SLAVE_ADDR,
            .maximum_speed = I2C_CLK_SPEED,
        },
    };

    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &i2c_slave_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_SLAVE, 128, 128, 0));

    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    light_driver_init(true);
    light_driver_set_color_RGB(255, 255, 255);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);

    xTaskCreate(slave_data_read_task, "Data_Read_Task", 4096, NULL, 5, NULL);
}

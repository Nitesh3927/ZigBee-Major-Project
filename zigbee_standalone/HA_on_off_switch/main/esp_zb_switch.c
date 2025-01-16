/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee HA_on_off_switch Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "string.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "zcl/esp_zigbee_zcl_common.h"
#include "esp_zb_switch.h"

#if defined ZB_ED_ROLE
#error Define ZB_COORDINATOR_ROLE in idf.py menuconfig to compile light switch source code.
#endif
typedef struct light_bulb_device_params_s {
    esp_zb_ieee_addr_t ieee_addr;
    uint8_t  endpoint;
    uint16_t short_addr;
} light_bulb_device_params_t;

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

static const char *TAG = "ESP_ZB_ON_OFF_SWITCH";

#define CUSTOM_CLUSTER_ID 0xFC00
#define CUSTOM_STRING_MAX_SIZE 127

void *esp_zb_zcl_attr_string_array_value_create(esp_zb_zcl_attr_type_t type, void *array, uint32_t elem_size, uint32_t elem_count)
{
    uint8_t *value = NULL;
    uint8_t offset = 0;
    switch (type) {
    case ESP_ZB_ZCL_ATTR_TYPE_LONG_OCTET_STRING:
    case ESP_ZB_ZCL_ATTR_TYPE_LONG_CHAR_STRING:
    case ESP_ZB_ZCL_ATTR_TYPE_ARRAY:
    case ESP_ZB_ZCL_ATTR_TYPE_16BIT_ARRAY:
    case ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY:
        value = malloc(sizeof(uint16_t) + elem_size * elem_count);
        memcpy(value + offset, &elem_count, sizeof(uint16_t));
        offset += sizeof(uint16_t);
        break;
    case ESP_ZB_ZCL_ATTR_TYPE_OCTET_STRING:
    case ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING:
        value = malloc(sizeof(uint8_t) + elem_size * elem_count);
        memcpy(value + offset, &elem_count, sizeof(uint8_t));
        offset += sizeof(uint8_t);
        break;
    default:
        ESP_LOGW(TAG, "The data type(0x%x) is not array or string, failed to create it", type);
        value = NULL;
        break;
    }
    memcpy(value + offset, array, elem_count * elem_size);
    return value;
};

void esp_zb_zcl_attr_string_array_value_free(uint8_t *array)
{
    if (array) {
        free(array);
    }
}

static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    static uint8_t flag = 0;
    if (button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        /* implemented light switch toggle functionality */
        switch (flag) {
        case 0: {
            esp_zb_zcl_custom_cluster_cmd_req_t custom_req;
            uint32_t message[] = {0x11223344, 0x44332211};
            uint8_t *value = esp_zb_zcl_attr_string_array_value_create(ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY, message, sizeof(message[0]),
                                                                       sizeof(message) / sizeof(uint32_t));
            custom_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
            custom_req.zcl_basic_cmd.dst_endpoint = 10;
            custom_req.zcl_basic_cmd.dst_addr_u.addr_short = 0xffff;
            custom_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
            custom_req.cluster_id = CUSTOM_CLUSTER_ID;
            custom_req.custom_cmd_id = 0x01;
            custom_req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
            custom_req.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
            custom_req.data.type = ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY;
            custom_req.data.value = value;
            esp_zb_zcl_custom_cluster_cmd_req(&custom_req);
            ESP_EARLY_LOGI(TAG, "Send 'specified custom number' command");
            esp_zb_zcl_attr_string_array_value_free(value);
            flag = 1;
            break;
        }
        case 1: {
            uint8_t value[CUSTOM_STRING_MAX_SIZE];
            value[0] = CUSTOM_STRING_MAX_SIZE - 1;
            for (int i = 1; i < CUSTOM_STRING_MAX_SIZE; i++) {
                value[i] = i;
            }
            esp_zb_zcl_attribute_t attrs = {2, {ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING, sizeof(value), value}};
            esp_zb_zcl_write_attr_cmd_t cmd_req = {
                .zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT,
                .address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
                .clusterID = CUSTOM_CLUSTER_ID,
                .attr_number = 1,
                .attr_field = &attrs,
            };
            esp_zb_zcl_write_attr_cmd_req(&cmd_req);
            ESP_LOGI(TAG, "Send 'write large data(%d)' command", sizeof(value));
            flag = 2;
            break;
        }
        case 2: {
            uint16_t attrs = {0x02};
            esp_zb_zcl_read_attr_cmd_t cmd_req = {
                .zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT,
                .address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
                .clusterID = CUSTOM_CLUSTER_ID,
                .attr_number = 1,
                .attr_field = &attrs,
            };
            esp_zb_zcl_read_attr_cmd_req(&cmd_req);
            ESP_EARLY_LOGI(TAG, "Send 'read large attr(%d)' command", attrs);
            flag = 0;
            break;
        }
        default:
            break;
        }
    }
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        if (user_ctx) {
            light_bulb_device_params_t *light = (light_bulb_device_params_t *)user_ctx;
            ESP_LOGI(TAG, "Successfully bound the light originating from address(0x%x) on endpoint(%d)", light->short_addr, light->endpoint);
            free(light);
        }
    }
}

static void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        /* Bound the light device to its own bind table. */
        esp_zb_zdo_bind_req_param_t bind_req;
        light_bulb_device_params_t *light = (light_bulb_device_params_t *)malloc(sizeof(light_bulb_device_params_t));
        light->endpoint = endpoint;
        light->short_addr = addr;
        esp_zb_ieee_address_by_short(light->short_addr, light->ieee_addr);
        esp_zb_get_long_address(bind_req.src_address);
        bind_req.src_endp = HA_ONOFF_SWITCH_ENDPOINT;
        bind_req.cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;
        bind_req.dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        memcpy(bind_req.dst_address_u.addr_long, light->ieee_addr, sizeof(esp_zb_ieee_addr_t));
        bind_req.dst_endp = endpoint;
        bind_req.req_dst_addr = esp_zb_get_short_address();
        ESP_LOGI(TAG, "Found light, binding...");
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, NULL);
        bind_req.cluster_id = CUSTOM_CLUSTER_ID;
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, (void *)light);
    }
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Start network formation");
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d)",
                     extended_pan_id[0], extended_pan_id[1], extended_pan_id[2], extended_pan_id[3],
                     extended_pan_id[4], extended_pan_id[5], extended_pan_id[6], extended_pan_id[7],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        esp_zb_zdo_match_desc_req_param_t  cmd_req;
        cmd_req.dst_nwk_addr = dev_annce_params->device_short_addr;
        cmd_req.addr_of_interest = dev_annce_params->device_short_addr;
        esp_zb_zdo_find_on_off_light(&cmd_req, user_find_cb, NULL);
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

static esp_err_t zb_write_resp_handler(const esp_zb_zcl_cmd_write_attr_resp_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Write attribute successfully");
    return ESP_OK;
}

static esp_err_t zb_custom_resp_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Received %s message: endpoint(%d), cluster(0x%x), data size(%d)", message->info.command.direction ? "response" : "request",
             message->info.dst_endpoint, message->info.cluster, message->data.size);

    printf("Receive(%d) response: ", message->data.size);
    for (int i = 0; i < message->data.size; i++) {
        printf("%02x, ", *((uint8_t *)message->data.value + i));
    }
    printf("\n");

    return ESP_OK;
}

static esp_err_t zb_read_attr_resp_handler(const esp_zb_zcl_cmd_read_attr_resp_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Received %s message: endpoint(%d), cluster(0x%x)", message->info.command.direction ? "response" : "request",
             message->info.dst_endpoint, message->info.cluster);

    esp_zb_zcl_read_attr_resp_variable_t *vars = message->variables;
    printf("size: %d\n", message->variables->attribute.data.size);
    while (vars) {
        for (int i = 0; i < vars->attribute.data.size; i++) {
            printf("0x%x ", *(uint8_t *)(vars->attribute.data.value + i));
        }
        printf("\n");
        vars = vars->next;
    }
    return ESP_OK;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_CMD_WRITE_ATTR_RESP_CB_ID:
        zb_write_resp_handler((esp_zb_zcl_cmd_write_attr_resp_message_t *)message);
        break;
    case ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID:
        ret = zb_read_attr_resp_handler((esp_zb_zcl_cmd_read_attr_resp_message_t *)message);
        break;
    case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID:
        ret = zb_custom_resp_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();

    esp_zb_on_off_cluster_cfg_t on_off_cfg;
    on_off_cfg.on_off = ESP_ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE;
    esp_zb_attribute_list_t *esp_zb_on_off_cluster = esp_zb_on_off_cluster_create(&on_off_cfg);
    esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_on_off_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

    esp_zb_attribute_list_t *custom_attr = esp_zb_zcl_attr_list_create(CUSTOM_CLUSTER_ID);
    uint8_t custom_value = 0xf0;
    uint8_t custom_string[CUSTOM_STRING_MAX_SIZE] = "_hello_world";
    custom_string[0] = CUSTOM_STRING_MAX_SIZE - 1;
    uint16_t custom_array[] = {1, 2, 3, 4, 5};
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x01, ESP_ZB_ZCL_ATTR_TYPE_U64, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, &custom_value);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x02, ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_string);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x03, ESP_ZB_ZCL_ATTR_TYPE_ARRAY, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_array);
    esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_attr, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_ONOFF_SWITCH_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);

    esp_zb_device_register(ep_list);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    esp_zb_core_action_handler_register(zb_action_handler);
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), esp_zb_buttons_handler);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
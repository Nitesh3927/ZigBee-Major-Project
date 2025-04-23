#include "esp_check.h"
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "string.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "zcl/esp_zigbee_zcl_common.h"

#include "led_strip.h"
#include "driver/gpio.h"

#include "coordinator_config.h"

static const char *TAG = "ESP_ZB_COORDINATOR";
static led_strip_handle_t led_strip;

void send_data(packet *data_to_send)
{
  uint8_t buffer[sizeof(packet) + 1];
  buffer[0] = sizeof(packet);
  memcpy(&buffer[1], data_to_send, sizeof(packet));

  esp_zb_zcl_custom_cluster_cmd_req_t custom_req = {
    .zcl_basic_cmd = {
      .dst_addr_u.addr_short = 0xFFFF, // Broadcast Address (Max data size 50)
      .dst_endpoint = END_DEVICE_END_POINT,
      .src_endpoint = COORDINATOR_END_POINT,
    },
    .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
    .cluster_id = ZB_ZCL_CUSTOM_CLUSTER_ID,
    .custom_cmd_id = 0x01,
    .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
    .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI,
    .data = {
      .type = ESP_ZB_ZCL_ATTR_TYPE_OCTET_STRING,
      .size = sizeof(packet),
      .value = buffer,
    },
  };
  printf("Data Sent: %2f, %2f, %2f, %u, %ld\n", data_to_send->latitude, data_to_send->longitude, data_to_send->speed, data_to_send->status, data_to_send->zigbeeAddress);
  esp_zb_zcl_custom_cluster_cmd_req(&custom_req);
}

static void slave_data_read_task() 
{
  packet buffer;
  while (true) {
    int buffer_size = i2c_slave_read_buffer(I2C_NUM_0, (uint8_t *)&buffer, sizeof(packet), pdMS_TO_TICKS(500));
    if (buffer_size == sizeof(packet)) {
      if (buffer.status == 128) { // Car has crashed
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
        buffer.zigbeeAddress = (uint32_t)esp_zb_get_short_address();
        send_data(&buffer);
      } else if (buffer.status == 32) { // A nearby Crash was detected
        led_strip_set_pixel(led_strip, 0, 255, 255, 0);
        led_strip_refresh(led_strip);
      } else {
        led_strip_set_pixel(led_strip, 0, 0, 255, 0);
        led_strip_refresh(led_strip);
      }
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }
}

static esp_err_t zb_custom_cluster_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    packet received_packet;
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    uint8_t *val = (uint8_t *)message->data.value;
    memcpy(&received_packet, &val[1], sizeof(packet));
    printf("Received data(%d): lat=%f, lon=%f, speed=%f, status=%u, addr=%lu\n",
      message->data.size,
      received_packet.latitude,
      received_packet.longitude,
      received_packet.speed,
      received_packet.status,
      received_packet.zigbeeAddress);
    i2c_slave_write_buffer(I2C_NUM_0, (uint8_t *)&received_packet, sizeof(packet), pdMS_TO_TICKS(500));
    send_data(&received_packet);
    return ESP_OK;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{   
  esp_err_t ret = ESP_OK;
  switch (callback_id) {
    case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID:
      ret = zb_custom_cluster_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
      break;
    default:
      ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
      break;
  }
  return ret;
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
  ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_s) {
  uint32_t *p_sg_p = signal_s->p_app_signal;
  esp_err_t err_status = signal_s->esp_err_status;
  esp_zb_app_signal_type_t sig_type = *p_sg_p;
  esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;

  switch(sig_type) {
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
        ESP_LOGI(TAG, "New device commissioned or rejoined (ieee adress: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, short: 0x%04hx, capability: %x)", 
          dev_annce_params->ieee_addr[0], dev_annce_params->ieee_addr[1], dev_annce_params->ieee_addr[2], dev_annce_params->ieee_addr[3],
          dev_annce_params->ieee_addr[4], dev_annce_params->ieee_addr[5], dev_annce_params->ieee_addr[6], dev_annce_params->ieee_addr[7],
          dev_annce_params->device_short_addr, dev_annce_params->capability);
        break;
      default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
        esp_err_to_name(err_status));
        break;
  }
}

static void esp_zb_task(void *pvParameters) {
  esp_zb_cfg_t zb_nwk_cfg = {
    .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,
    .install_code_policy = CODE_SECURITY_POLICY,
    .nwk_cfg.zczr_cfg.max_children = MAX_CHILDREN,
  };
  esp_zb_init(&zb_nwk_cfg);

  esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
  esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
  esp_zb_attribute_list_t *custom_attr_list = esp_zb_zcl_attr_list_create(ZB_ZCL_CUSTOM_CLUSTER_ID);

  packet custom_packet = {
    .latitude = 1.0f,
    .longitude = 1.0f,
    .speed = 1.0f,
    .status = 'W',
    .zigbeeAddress = 0xFFFFUL,
  };
  esp_zb_custom_cluster_add_custom_attr(custom_attr_list, 0x0001, ESP_ZB_ZCL_ATTR_TYPE_STRUCTURE, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, &custom_packet);
  esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_attr_list, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

  esp_zb_endpoint_config_t endpoint_config = {
    .endpoint = COORDINATOR_END_POINT,
    .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
    .app_device_version = 0,
    .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
  };
  esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
  esp_zb_device_register(ep_list);
  
  esp_zb_core_action_handler_register(zb_action_handler);
  esp_zb_set_primary_network_channel_set(NWK_CHANNEL_MASK);
  ESP_ERROR_CHECK(esp_zb_start(false));
  esp_zb_stack_main_loop();
}

static void configure_led(void) {
  led_strip_config_t strip_config = {
    .max_leds = 1,
    .strip_gpio_num = LED_GPIO,
  };
  led_strip_rmt_config_t rmt_config = {
    .resolution_hz = 0,
    .flags.with_dma = false,
  };
  ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
  led_strip_clear(led_strip);
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

  // Zigbee Device Config
  esp_zb_platform_config_t config = {
    .host_config = {
      .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,
    },
    .radio_config = {
      .radio_mode = ZB_RADIO_MODE_NATIVE,
    },
  };
  
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_zb_platform_config(&config));

  // LED Strip Config
  configure_led();

  xTaskCreate(esp_zb_task, "Zigbee_Task", 4096, NULL, 5, NULL);

  vTaskDelay(3000 / portTICK_PERIOD_MS);
  led_strip_set_pixel(led_strip, 0, 0, 255, 0);
  led_strip_refresh(led_strip);

  xTaskCreate(slave_data_read_task, "Data_Read_Task", 4096, NULL, 10, NULL);
}
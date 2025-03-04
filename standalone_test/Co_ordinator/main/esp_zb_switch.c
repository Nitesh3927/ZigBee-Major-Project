#include "esp_zb_switch.h"
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

#include "driver/i2c.h"
#include "driver/i2c_master.h"

#if defined ZB_ED_ROLE
#error Define ZB_COORDINATOR_ROLE in idf.py menuconfig to compile light switch source code.
#endif

static const char *TAG = "ESP_ZB_ON_OFF_SWITCH";

#define CUSTOM_CLUSTER_ID 0xFC00
#define CUSTOM_STRING_MAX_SIZE 30

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

typedef struct light_bulb_device_params_s {
    esp_zb_ieee_addr_t ieee_addr;
    uint8_t  endpoint;
    uint16_t short_addr;
} light_bulb_device_params_t;

static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    uint8_t value[CUSTOM_STRING_MAX_SIZE];
    // value[0] = CUSTOM_STRING_MAX_SIZE - 1;
    // for (int i = 1; i < CUSTOM_STRING_MAX_SIZE; i++) {
    //     value[i] = 'A';
    // }
    esp_zb_zcl_custom_cluster_cmd_req_t custom_req;
    custom_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
    custom_req.zcl_basic_cmd.dst_endpoint = 10;
    custom_req.zcl_basic_cmd.dst_addr_u.addr_short = 0xffff;
    custom_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    custom_req.cluster_id = CUSTOM_CLUSTER_ID;
    custom_req.custom_cmd_id = 0x01;
    custom_req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    custom_req.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
    custom_req.data.type = ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING;
    // while (true) {
        i2c_slave_read_buffer(I2C_NUM_0, value, sizeof(value), 10 / portTICK_PERIOD_MS);
        custom_req.data.value = value;
        for (int i = 0; i < CUSTOM_STRING_MAX_SIZE; i++) {
            printf("%c", value[i]);
        }
        esp_zb_zcl_custom_cluster_cmd_req(&custom_req);
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        printf("\n");
    // }
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

static esp_err_t zb_custom_req_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    printf("Receive(%d) request: ", message->data.size);
    for (int i = 0; i < message->data.size; i++) {
        printf("%c ", *((uint8_t *)message->data.value + i));
    }
    printf("\n");

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    esp_zb_buttons_handler(button_func_pair);  
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
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();

    esp_zb_attribute_list_t *custom_attr = esp_zb_zcl_attr_list_create(CUSTOM_CLUSTER_ID);
    uint8_t custom_value = 0xf0;
    uint8_t custom_string[CUSTOM_STRING_MAX_SIZE] = "_hello_world";
    custom_string[0] = CUSTOM_STRING_MAX_SIZE - 1;
    uint32_t custom_array[] = {1, 2, 3, 4, 5};
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x01, ESP_ZB_ZCL_ATTR_TYPE_U64, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, &custom_value);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x02, ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_string);
    esp_zb_custom_cluster_add_custom_attr(custom_attr, 0x03, ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE, custom_array);
    esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_attr, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_ONOFF_SWITCH_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
    esp_zb_device_register(ep_list);

    esp_zb_zcl_custom_cluster_handlers_t obj = {.cluster_id = CUSTOM_CLUSTER_ID,
                                                .cluster_role = ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE,
                                                .check_value_cb = esp_zb_zcl_cluster_check_value_handler,
                                                .write_attr_cb = esp_zb_zcl_cluster_write_attr_handler};
    esp_zb_zcl_custom_cluster_handlers_update(obj);

    esp_zb_core_action_handler_register(zb_action_handler);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = 5,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = 4,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave.slave_addr = 0x3C,
        .slave.maximum_speed = 400000,
        .clk_flags = 0,
    };
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, conf.mode, 127, 127, 0);


    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), esp_zb_buttons_handler);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}

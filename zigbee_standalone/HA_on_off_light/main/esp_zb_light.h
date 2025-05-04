#include "esp_zigbee_core.h"
#include "light_driver.h"
#include "driver/i2c.h"

#pragma pack(1)
typedef struct packet {
  float latitude;
  float longitude;
  float speed;
  uint16_t zigbeeAddress;
  uint8_t status;
} packet;
#pragma pack()

// I2C Config Parameters
#define I2C_SDA_NUM 5
#define I2C_SCL_NUM 4
#define I2C_SLAVE_ADDR 0x3c
#define I2C_CLK_SPEED 400000

/* Zigbee configuration */
#define INSTALLCODE_POLICY_ENABLE       false    /* enable the install code policy for security */
#define ED_AGING_TIMEOUT                ESP_ZB_ED_AGING_TIMEOUT_64MIN
#define ED_KEEP_ALIVE                   3000    /* 3000 millisecond */
#define HA_ESP_LIGHT_ENDPOINT           10    /* esp light bulb device endpoint, used to process light controlling commands */
#define ESP_ZB_PRIMARY_CHANNEL_MASK     (1 << 18)  /* Zigbee primary channel mask use in the example */

#define ESP_ZB_ZED_CONFIG()                                         \
    {                                                               \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_ED,                       \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,           \
        .nwk_cfg.zed_cfg = {                                        \
            .ed_timeout = ED_AGING_TIMEOUT,                         \
            .keep_alive = ED_KEEP_ALIVE,                            \
        },                                                          \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
    {                                                           \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                        \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,      \
    }

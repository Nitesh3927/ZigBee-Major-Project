#include "esp_zigbee_core.h"
#include "driver/i2c.h"
#include "light_driver.h"

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
#define MAX_CHILDREN                    10          /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE       false    /* enable the install code policy for security */
#define HA_ONOFF_SWITCH_ENDPOINT        1          /* esp light switch device endpoint */
#define ESP_ZB_PRIMARY_CHANNEL_MASK     (1l << 18)  /* Zigbee primary channel mask use in the example */

#define ESP_ZB_ZC_CONFIG()                                                              \
    {                                                                                   \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                                  \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,                               \
        .nwk_cfg.zczr_cfg = {                                                           \
            .max_children = MAX_CHILDREN,                                               \
        },                                                                              \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
    {                                                           \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                        \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,      \
    }

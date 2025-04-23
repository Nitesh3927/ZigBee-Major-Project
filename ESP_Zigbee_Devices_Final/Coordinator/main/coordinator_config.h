#include "driver/i2c.h"

typedef struct packet {
  float latitude;
  float longitude;
  float speed;
  uint8_t status;
  uint32_t zigbeeAddress;
} packet;

// I2C Config Parameters
#define I2C_SDA_NUM 5
#define I2C_SCL_NUM 4
#define I2C_SLAVE_ADDR 0x3c
#define I2C_CLK_SPEED 400000

// Zigbee Config Parameters
#define COORDINATOR_END_POINT 10
#define END_DEVICE_END_POINT 20
#define MAX_CHILDREN 10
#define CODE_SECURITY_POLICY false
#define ZB_ZCL_CUSTOM_CLUSTER_ID 0xFC00U
#define NWK_CHANNEL_MASK (1L << 18)

// LED Strip Config Parameters
#define LED_GPIO 8
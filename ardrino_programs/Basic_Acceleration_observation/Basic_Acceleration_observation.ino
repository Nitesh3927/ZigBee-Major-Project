#include <Wire.h>

#define MPU6050_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define CONFIG 0x1A
#define SMPLRT_DIV 0x19
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

uint16_t accel_scale_factor;
uint16_t gyro_scale_factor;

void i2cWrite(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

void i2cRead(uint8_t reg, uint8_t count, uint8_t *data) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, count);
    for (uint8_t i = 0; i < count; i++) {
        data[i] = Wire.read();
    }
}

void setup() {
    Wire.begin();
    Serial.begin(921600);

    // Power Management
    i2cWrite(PWR_MGMT_1, 0x00);
    i2cWrite(PWR_MGMT_2, 0x00);

    // Accelerometer Configuration
    uint8_t ACCEL_RANGE = 2; // Change this as needed
    switch (ACCEL_RANGE) {
        case 2:
            i2cWrite(ACCEL_CONFIG, 0x00);
            accel_scale_factor = 16384;
            break;
        case 4:
            i2cWrite(ACCEL_CONFIG, 0x08);
            accel_scale_factor = 8192;
            break;
        case 8:
            i2cWrite(ACCEL_CONFIG, 0x10);
            accel_scale_factor = 4096;
            break;
        case 16:
            i2cWrite(ACCEL_CONFIG, 0x18);
            accel_scale_factor = 2048;
            break;
        default:
            Serial.println("Invalid Accelerometer Range");
            return;
    }

    // Gyroscope Configuration
    uint8_t GYRO_RANGE = 250; // Change this as needed
    switch (GYRO_RANGE) {
        case 250:
            i2cWrite(GYRO_CONFIG, 0x00);
            gyro_scale_factor = 131;
            break;
        case 500:
            i2cWrite(GYRO_CONFIG, 0x08);
            gyro_scale_factor = 65.5;
            break;
        case 1000:
            i2cWrite(GYRO_CONFIG, 0x10);
            gyro_scale_factor = 32.8;
            break;
        case 2000:
            i2cWrite(GYRO_CONFIG, 0x18);
            gyro_scale_factor = 16.4;
            break;
        default:
            Serial.println("Invalid Gyroscope Range");
            return;
    }

    // Digital Low-Pass Filter
    uint8_t DLPF_SETTING = 0; // Change this as needed
    if (DLPF_SETTING <= 6) {
        i2cWrite(CONFIG, DLPF_SETTING);
    } else {
        Serial.println("Invalid DLPF setting");
        return;
    }

    // Sampling Configuration
    uint8_t SAMPLE_RATE_DIV = 0; // Change as needed
    i2cWrite(SMPLRT_DIV, SAMPLE_RATE_DIV);

    // Interrupt Configuration
    i2cWrite(INT_PIN_CFG, 0x10);
    i2cWrite(INT_ENABLE, 0x00);

    Serial.println("MPU6050 Initialization Completed.");
}

void loop() {
    uint8_t rawData[6];

    // Read Accelerometer Data
    i2cRead(ACCEL_XOUT_H, 6, rawData);
    int16_t raw_acc_x = (rawData[0] << 8) | rawData[1];
    int16_t raw_acc_y = (rawData[2] << 8) | rawData[3];
    int16_t raw_acc_z = (rawData[4] << 8) | rawData[5]; 

    float acc_x = (float)raw_acc_x / accel_scale_factor;
    float acc_y = (float)raw_acc_y / accel_scale_factor;
    float acc_z = (float)raw_acc_z / accel_scale_factor;

    // Read Gyroscope Data
    i2cRead(GYRO_XOUT_H, 6, rawData);
    int16_t raw_gyro_x = (rawData[0] << 8) | rawData[1];
    int16_t raw_gyro_y = (rawData[2] << 8) | rawData[3];
    int16_t raw_gyro_z = (rawData[4] << 8) | rawData[5];
    
    float gyro_x = (float)raw_gyro_x / gyro_scale_factor;
    float gyro_y = (float)raw_gyro_y / gyro_scale_factor;
    float gyro_z = (float)raw_gyro_z / gyro_scale_factor;

    // Print Accelerometer and Gyroscope Data
    Serial.printf("Time: %7.3f | Acc: %+10.7f, %+10.7f, %+10.7f | Gyro: %+13.7f, %+13.7f, %+13.7f\n",
                  millis() / 1000.0, acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);

    delay(10);
}

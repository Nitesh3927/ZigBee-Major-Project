#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\acc_observer\accleration_reader.h"

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include <Wire.h>

#define MPU6050_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define ACCEL_CONFIG 0x1C
#define CONFIG 0x1A
#define SMPLRT_DIV 0x19
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define ACCEL_XOUT_H 0x3B

uint16_t scale_factor;
uint8_t rawData[6];

// ACCEL_RANGE uint8 [1,1] Non tunable
// ENABLE_GYRO logical [1,1] Non tunable
// DLPF_SETTING uint8 [1,1] Non tunable

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


void setupFunctionaccleration_reader(uint8_T  ACCEL_RANGE,int size_vector__1,boolean_T  ENABLE_GYRO,int size_vector__2,uint8_T  DLPF_SETTING,int size_vector__3){
    Wire.begin();

    // Power Management
    i2cWrite(PWR_MGMT_1, 0x00);
    i2cWrite(PWR_MGMT_2, 0x00);

    // Accelerometer Configuration
    switch (ACCEL_RANGE) {
        case 2:
            i2cWrite(ACCEL_CONFIG, 0x00);
            scale_factor = 16384;
            break;
        case 4:
            i2cWrite(ACCEL_CONFIG, 0x08);
            scale_factor = 8192;
            break;
        case 8:
            i2cWrite(ACCEL_CONFIG, 0x10);
            scale_factor = 4096;
            break;
        case 16:
            i2cWrite(ACCEL_CONFIG, 0x18);
            scale_factor = 2048;
            break;
        default:
            return;
    }
    
    // Digital Low-Pass Filter
    if (DLPF_SETTING <= 6) {
        i2cWrite(CONFIG, DLPF_SETTING);
    }


    // Interrupt Configuration
    i2cWrite(INT_PIN_CFG, 0x10);
    i2cWrite(INT_ENABLE, 0x00);

}

// acc_x double [1,1]
// acc_y double [1,1]
// acc_z double [1,1]


void stepFunctionaccleration_reader(double * acc_x,int size_vector_1,double * acc_y,int size_vector_2,double * acc_z,int size_vector_3){
  

    i2cRead(ACCEL_XOUT_H, 6, rawData);
    
    int16_t raw_acc_x = (rawData[0] << 8) | rawData[1];
    int16_t raw_acc_y = (rawData[2] << 8) | rawData[3];
    int16_t raw_acc_z = (rawData[4] << 8) | rawData[5];
    
    *acc_x = (double)raw_acc_x / scale_factor;
    *acc_y = (double)raw_acc_y / scale_factor;
    *acc_z = (double)raw_acc_z / scale_factor;
}
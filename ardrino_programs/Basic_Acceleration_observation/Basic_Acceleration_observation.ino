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
            Serial.println("Invalid Accelerometer Range");
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
  i2cRead(ACCEL_XOUT_H, 6, rawData);
  
  int16_t raw_acc_x = (rawData[0] << 8) | rawData[1];
  int16_t raw_acc_y = (rawData[2] << 8) | rawData[3];
  int16_t raw_acc_z = (rawData[4] << 8) | rawData[5];
  
  float acc_x = (float)raw_acc_x / scale_factor;
  float acc_y = (float)raw_acc_y / scale_factor;
  float acc_z = (float)raw_acc_z / scale_factor;

  
  // Serial.print("Acc X: "); Serial.print(acc_x, 7);
  // Serial.print(" | Acc Y: "); Serial.print(acc_y, 7);
  // Serial.print(" | Acc Z: "); Serial.println(acc_z, 7);

  // float X_out = acc_x;
  // float Y_out = acc_y;
  // float Z_out = acc_z;
  
  // Serial.print("Time_Stamp= "); 
  // Serial.print(millis()/1000.0, 3);
  // Serial.print(" Xa= "); 
  // Serial.print(X_out, 7); 
  // Serial.print("   Ya= "); 
  // Serial.print(Y_out, 7); 
  // Serial.print("   Za= "); 
  // Serial.println(Z_out, 7); 

  Serial.printf("%0.3f | %.7f | %.7f | %.7f\n", millis()/1000.0, acc_x, acc_y, acc_z);
    
    // delay(10);
}

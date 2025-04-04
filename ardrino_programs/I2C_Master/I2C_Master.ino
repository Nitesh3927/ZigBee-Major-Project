/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-i2c-master-slave-arduino/
  ESP32 I2C Master Example: https://github.com/espressif/arduino-esp32/blob/master/libraries/Wire/examples/WireMaster/WireMaster.ino
*********/

#include "Wire.h"

#define I2C_FREQ 400000
#define TARGET_I2C_ADDR 0x3C  // Target device address
#define SCL_PIN 22
#define SDA_PIN 21

void setup() {
  Serial.begin(115200);
  Serial.println("I2C Scanner and Master Example");

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Perform an initial scan
  scanI2CDevices();
}

void loop() {
  delay(5000); // Delay between scans

  // Repeatedly scan for I2C devices
  scanI2CDevices();

  // Write message to the target I2C device
  Wire.beginTransmission(TARGET_I2C_ADDR);
  Wire.print("Hello World!");

  uint8_t error = Wire.endTransmission(true);
  if (error == 0) {
    Serial.println("Message sent successfully.");
  } else {
    Serial.printf("Error sending message: %u\n", error);
  }

  // Read 16 bytes from the target I2C device
  uint8_t bytesReceived = Wire.requestFrom(TARGET_I2C_ADDR, 16);
  if (bytesReceived > 0) {
    Serial.printf("Received %u bytes: ", bytesReceived);
    while (Wire.available()) {
      Serial.write(Wire.read());
    }
    Serial.println();
  } else {
    Serial.println("No data received.");
  }
}



void scanI2CDevices() {
  Serial.println("Scanning for I2C devices...");
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf("I2C device found at address 0x%02X\n", address);
    } else if (error == 4) {
      Serial.printf("Unknown error at address 0x%02X\n", address);
    }
  }
  Serial.println("I2C scan complete.");
}
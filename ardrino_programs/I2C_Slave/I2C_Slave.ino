/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-i2c-master-slave-arduino/
  ESP32 I2C Slave example: https://github.com/espressif/arduino-esp32/blob/master/libraries/Wire/examples/WireSlave/WireSlave.ino
*********/

#include <Wire.h>

#define SLAVE_ADDRESS 0x3F
#define I2C_FREQ 400000
// #define I2C_FREQ 0
#define SCL_PIN 4
#define SDA_PIN 5

volatile int receivedData = 0; // Variable to store received data
volatile bool dataAvailable = false; // Flag to indicate data reception

#include "driver/gpio.h"

void enableInternalPullups() {
    gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);  // SDA (default GPIO 8)
    gpio_set_pull_mode(GPIO_NUM_5, GPIO_PULLUP_ONLY);  // SCL (default GPIO 9)
}

void setup() {
  // Wire.begin(SLAVE_ADDRESS, SDA_PIN, SCL_PIN); 
  // Wire.begin(80, SCL_PIN, SDA_PIN, 0);
  // Wire.setPins(SDA_PIN, SCL_PIN);
  enableInternalPullups();
  Wire.begin(SLAVE_ADDRESS, SDA_PIN, SCL_PIN, 10000); 
  // pinMode(SDA_PIN, INPUT_PULLUP);
  // pinMode(SCL_PIN, INPUT_PULLUP); 
  
  Wire.onReceive(onReceive); 
  Wire.onRequest(onRequest); 
  Serial.println(Wire.available());
  Serial.begin(115200);
  Serial.println("I2C Slave Initialized");
}

void loop() {
  if (dataAvailable) {
    Serial.print("Received data: ");
    Serial.println(receivedData);
    dataAvailable = false; // Reset the flag after processing the data
  }
  // Serial.println(SDA);
  // Serial.println(SCL);
  delay(100); // Small delay to avoid flooding the serial monitor
}

// Function to handle data received from the master
void onReceive(int numBytes) {
  if (Wire.available()) {
    receivedData = Wire.read(); // Read the first byte of data
    dataAvailable = true;       // Set the flag to indicate data is available
  }
}

// Function to handle data requested by the master
void onRequest() {
  int response = receivedData + 1; // Example response: increment received data
  Wire.write(response);           // Send the response back to the master
}

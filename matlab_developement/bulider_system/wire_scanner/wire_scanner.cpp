#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\wire_scanner\wire_scanner.h"

#include "Arduino.h" // Include the Arduino library
#include <Wire.h> // Include the I2C library

void setupFunctionwire_scanner() {
    // Initialize the I2C bus
    // Wire.begin();
    // Serial.begin(9600); // Initialize serial communication for debugging
    // Serial.println("I2C Scanner Initialized");
}

// i2c_slaves uint32 [1,5]

void stepFunctionwire_scanner(uint32_T *i2c_slaves, int size_vector_1) {
    Wire.begin();
    int found_devices = 0;
    
    // Serial.println("Scanning for I2C devices...");
    for (uint8_t address = 1; address < 127; address++) { // I2C addresses range from 1 to 127
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();
        
        if (error == 0) { // Device found
            if (found_devices < size_vector_1) {
                i2c_slaves[found_devices] = address; // Store the address in the array
                found_devices++;
            }
            // Serial.print("Device found at address: 0x");
            // Serial.println(address, HEX);
        }
    }
    
    // Fill remaining slots with 0 if fewer devices are found
    for (int i = found_devices; i < size_vector_1; i++) {
        i2c_slaves[i] = 0;
    }
    
    Wire.end(); // End the I2C bus
    Wire.endTransmission(); // End transmission
    delay(50); // Delay for stability
}
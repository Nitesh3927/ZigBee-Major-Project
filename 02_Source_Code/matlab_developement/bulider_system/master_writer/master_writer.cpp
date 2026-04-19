#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\master_writer\master_writer.h"


#include <Wire.h> // Include the I2C library
#include <Arduino.h> // Include the Arduino library

struct i2cPacket {
    float latitude;
    float longitude;
    float speed;
    uint8_t status;
    uint64_t zigbeeAddress;
};

// I2C slave address
uint16_t SLAVE_ADDRESS;

// slave_address uint16 [1,1] Non tunable
// bus_frequency uint64 [1,1] Non tunable

void setupFunctionmaster_writer(uint16_T slave_address, int size_vector__1, uint_T bus_frequency, int size_vector__2) {
    // if (!Wire.available()) {
    //     Wire.begin(); // Join the I2C bus as a master
    // }
    // Wire.setClock(bus_frequency); // Set the I2C bus frequency
    SLAVE_ADDRESS = slave_address; // Set the slave address
}

// WRITING_ACK logical [1,1]
// local_lat double [1,1]
// local_lat_isValid logical [1,1]
// local_lng double [1,1]
// local_lng_inValid logical [1,1]
// local_speed double [1,1]
// local_speed_isValid logical [1,1]
// TRANSMITTING logical [1,1]

void stepFunctionmaster_writer(boolean_T *WRITING_ACK, int size_vector_1, double local_lat, int size_vector_a, boolean_T local_lat_isValid, int size_vector_b, double local_lng, int size_vector_c, boolean_T local_lng_inValid, int size_vector_d, double local_speed, int size_vector_e, boolean_T local_speed_isValid, int size_vector_f, boolean_T TRANSMITTING, int size_vector_g) {
    Wire.begin(); // Initialize the I2C bus
    if (TRANSMITTING) {
        // Create an i2cPacket instance and populate it with data
        i2cPacket packet;
        packet.latitude = static_cast<float>(local_lat);
        packet.longitude = static_cast<float>(local_lng);
        packet.speed = static_cast<float>(local_speed);
        packet.status = (local_lat_isValid && local_speed_isValid) ? 1 : 0;
        packet.zigbeeAddress = 0x123456789ABCDEF; // Example ZigBee address

        // Transmit the packet via I2C
        // Wire.beginTransmission(SLAVE_ADDRESS); // Start transmission to the slave

        Wire.beginTransmission(60); // Start transmission to the slave
        if (Wire.write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet)) != sizeof(packet)) {
            *WRITING_ACK = false; // Transmission failed
            Wire.endTransmission(false);
            return;
        }
        uint8_t result = Wire.endTransmission(true); // End transmission

        // Set WRITING_ACK based on the transmission result
        *WRITING_ACK = (result == 0); // 0 indicates success
    }
    Wire.end(); // End the I2C bus
    Wire.endTransmission(); // End transmission
    delay(50); // Delay for 50ms
}
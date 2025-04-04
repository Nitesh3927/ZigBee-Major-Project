#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\serial_starter\serial_starter.h"

#include <Wire.h> // Include the I2C library
#include <Arduino.h> // Include the Arduino library

void setupFunctionserial_starter(){
    
    pinMode(21, INPUT_PULLUP); // Enable pull-up resistor on pin 21
    pinMode(22, INPUT_PULLUP); // Enable pull-up resistor on pin 22

    // Wire.begin(); // Join the I2C bus as a master
    // Wire.setClock(100000); // Set the I2C bus frequency to 400kHz

}




void stepFunctionserial_starter(){
  
}
#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\gps_parser\GPS_Parser.h"

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include "TinyGPSPlus.h"

TinyGPSPlus gps;

void setupFunctionGPS_Parser(){
    Serial2.begin(9600);
}

// Lat double [1,1]
// Lng double [1,1]
// Speed double [1,1]


void stepFunctionGPS_Parser(double * Lat,int size_vector_1,double * Lng,int size_vector_2,double * Speed,int size_vector_3){
    while (Serial2.available() > 0) {
        char c = Serial2.read();
        gps.encode(c);   // Parse the data
    }
    
    if (gps.location.isValid()) {
        *Lat = gps.location.lat();
        *Lng = gps.location.lng();
    } else { *Lat = 0.0; *Lng = 0.0;}
    
    if (gps.speed.isValid()) {
        *Speed = gps.speed.kmph();
    } else {*Speed = 0.0;}
}
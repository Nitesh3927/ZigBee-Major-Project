#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\gps_reader\gps_reader.h"

#ifndef Arduino_h
#include "Arduino.h"
#endif

#include "TinyGPSPlus.h"

TinyGPSPlus gps;

void setupFunctiongps_reader(){
    // if (!Serial) {
    //     Serial.begin(115200);
    // }
    // if (!Serial2) {
    //     Serial2.begin(9600);
    // }
    Serial2.begin(9600);
}

// hdop double [1,1]
// hdop_isValid logical [1,1]
// satellite uint8 [1,1]
// satellite_isValid logical [1,1]
// time_hours uint8 [1,1]
// time_mins uint8 [1,1]
// time_sec uint8 [1,1]
// time_isValid logical [1,1]
// date_day uint8 [1,1]
// date_month uint8 [1,1]
// date_year uint16 [1,1]
// date_isValid logical [1,1]
// speed double [1,1]
// speed_isValid logical [1,1]
// lat double [1,1]
// lat_isValid logical [1,1]
// lng double [1,1]
// lng_isValid logical [1,1]


void stepFunctiongps_reader(double * hdop,int size_vector_1,boolean_T * hdop_isValid,int size_vector_2,uint8_T * satellite,int size_vector_3,boolean_T * satellite_isValid,int size_vector_4,uint8_T * time_hours,int size_vector_5,uint8_T * time_mins,int size_vector_6,uint8_T * time_sec,int size_vector_7,boolean_T * time_isValid,int size_vector_8,uint8_T * date_day,int size_vector_9,uint8_T * date_month,int size_vector_10,uint16_T * date_year,int size_vector_11,boolean_T * date_isValid,int size_vector_12,double * speed,int size_vector_13,boolean_T * speed_isValid,int size_vector_14,double * lat,int size_vector_15,boolean_T * lat_isValid,int size_vector_16,double * lng,int size_vector_17,boolean_T * lng_isValid,int size_vector_18){
    
    while (Serial2.available() > 0) {
        char c = Serial2.read();
        gps.encode(c);   // Parse the data
    }

    if (gps.hdop.isValid()) {
        *hdop = gps.hdop.value() / 100.0;
        *hdop_isValid = true;
    } else {
        *hdop = 0.0;
        *hdop_isValid = false;
    }

    if (gps.satellites.isValid()) {
        *satellite = gps.satellites.value();
        *satellite_isValid = true;
    } else {
        *satellite = 0;
        *satellite_isValid = false;
    }

    if (gps.time.isValid()) {
        *time_hours = gps.time.hour();
        *time_mins = gps.time.minute();
        *time_sec = gps.time.second();
        *time_isValid = true;
    } else {
        *time_hours = 0;
        *time_mins = 0;
        *time_sec = 0;
        *time_isValid = false;
    }

    if (gps.date.isValid()) {
        *date_day = gps.date.day();
        *date_month = gps.date.month();
        *date_year = gps.date.year();
        *date_isValid = true;
    } else {
        *date_day = 0;
        *date_month = 0;
        *date_year = 0;
        *date_isValid = false;
    }

    if (gps.speed.isValid()) {
        *speed = gps.speed.kmph();
        *speed_isValid = true;
    } else {
        *speed = 0.0;
        *speed_isValid = false;
    }

    if (gps.location.isValid()) {
        *lat = gps.location.lat();
        *lat_isValid = true;
        *lng = gps.location.lng();
        *lng_isValid = true;
    } else {
        *lat = 0.0;
        *lat_isValid = false;
        *lng = 0.0;
        *lng_isValid = false;
    }
    // Serial.println("hdop: " + String(*hdop));
    // Serial.println("hdop_isValid: " + String(*hdop_isValid));
    // Serial.println("satellite: " + String(*satellite));
    // Serial.println("satellite_isValid: " + String(*satellite_isValid));
    // Serial.println("time: " + String(*time_hours) + ":" + String(*time_mins) + ":" + String(*time_sec));
    // Serial.println("time_isValid: " + String(*time_isValid));
    // Serial.println("date: " + String(*date_day) + "/" + String(*date_month) + "/" + String(*date_year));
    // Serial.println("date_isValid: " + String(*date_isValid));
    // Serial.println("speed: " + String(*speed));
    // Serial.println("speed_isValid: " + String(*speed_isValid));
    // Serial.println("lat: " + String(*lat));
    // Serial.println("lat_isValid: " + String(*lat_isValid));
    // Serial.println("lng: " + String(*lng));
    // Serial.println("lng_isValid: " + String(*lng_isValid));
    // Serial.println();
}

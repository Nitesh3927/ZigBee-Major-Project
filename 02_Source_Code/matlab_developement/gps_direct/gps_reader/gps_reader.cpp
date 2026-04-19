#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\gps_reader\gps_reader.h"

#include "TinyGPSPlus.h"
#include "Arduino.h"

TinyGPSPlus gps;

void setupFunctiongps_reader(){
    Serial.begin(9600);
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
    

    *hdop = gps.hdop.value()/100.0 ;
    *hdop_isValid = gps.hdop.isValid(); 
    *satellite = gps.satellites.value(); 
    *satellite_isValid = gps.satellites.isValid() ;
    *time_hours = gps.time.hour() ;
    *time_mins = gps.time.minute() ;
    *time_sec = gps.time.second() ;
    *time_isValid = gps.time.isValid() ; ;
    *date_day = gps.date.day() ;
    *date_month = gps.date.month() ;
    *date_year = gps.date.year() ;
    *date_isValid = gps.date.isValid() ;
    *speed = gps.speed.kmph() ;
    *speed_isValid = gps.speed.isValid() ;
    *lat = gps.location.lat() ;
    *lat_isValid = gps.location.isValid() ;
    *lng = gps.location.lng() ;
    *lng_isValid = gps.location.isValid() ;

}
#include "C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\reader.h"


// #include "SoftwareSerial.h"
#include "TinyGPSPlus.h"
#include "Arduino.h"


TinyGPSPlus gps;
// SoftwareSerial gpsSerial(16, 17);

void setupFunctionreader(){
  Serial.begin(9600);
  Serial2.begin(9600);
    // Serial2.begin(9600);
}

// lat double [1,1]
// lng double [1,1]


void stepFunctionreader(double * lat,int size_vector_1,double * lng,int size_vector_2){
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    gps.encode(c);   // Parse the data
  }

  *lat = gps.location.lat(); 
  *lng = gps.location.lng();

}
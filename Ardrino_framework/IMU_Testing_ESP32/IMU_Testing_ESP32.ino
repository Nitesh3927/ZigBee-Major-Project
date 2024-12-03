#include <TinyGPS++.h>

// PIN DEFININATION
// --------------------------------------------------------------------------
#define RXD2 23
#define TXD2 24
// #define RXD 3
// #define RXD 1
// #define TXD 16
// #define TXD 17


// BAUD AND SERIAL DEFINATION 
// --------------------------------------------------------------------------
#define GPS_BAUD 9600
HardwareSerial hardSerial(1);
TinyGPSPlus gps;

// --------------------------------------------------------------------------
// SUPPORT FUNCTIONS
// --------------------------------------------------------------------------
void smartDelay(unsigned long ms) {
  // READ THE SERIAL VALUE AND THEN GO FOR A PAUSE
  unsigned long start = millis();
  do 
  {
    while (hardSerial.available())
      gps.encode(hardSerial.read());
  } while (millis() - start < ms);
}

// --------------------------------------------------------------------------
// GPS FUNCTIONS
// --------------------------------------------------------------------------
void initializeGPSSerial() {
  hardSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
}

void processGPSData() {  
    // CHECK IF HARDWARE SERIAL IS AVAILABLE 
    while (hardSerial.available() > 0) {
      gps.encode(hardSerial.read());
    }
    delay(800);
}

void displayGPSData() {
  // DISPLAY GPS VALUES (NOTHING ELSE)

  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");
  Serial.println(hardSerial.read());

  // Serial.printf("Time: %.4f, Lat: %.6f, Lon: %.6f, Speed: %.2f km/h, Alt: %.2f m, Sat: %d, Time (UTC): %02d:%02d:%02d\n",
  //                 millis()/ 1000.0, 
  //                 gps.location.lat(), gps.location.lng(), gps.speed.kmph(), 
  //                 gps.altitude.meters(), gps.satellites.value(), 
  //                 gps.time.hour(), gps.time.minute(), gps.time.second());
  // Serial.println("------------------------------");
}

// --------------------------------------------------------------------------


void setup() {
  Serial.begin(115200); 
  initializeGPSSerial();
  Serial.println("Serial 2 started at 9600 baud rate");
}

void loop() {
  processGPSData();
  displayGPSData();
}
// --------------------------------------------------------------------------





// void setup() {
//   Serial.begin(115200);
  
//   hardSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
//   Serial.println("Serial 2 started at 9600 baud rate");
// }

// void loop() {

//   unsigned long start = millis();

//   while (millis() - start < 1000) {
//     while (hardSerial.available() > 0) {
//       gps.encode(hardSerial.read());
//     }
//     if (gps.location.isUpdated()) {
//       Serial.print("LAT: ");
//       Serial.println(gps.location.lat(), 6);
//       Serial.print("LONG: "); 
//       Serial.println(gps.location.lng(), 6);
//       Serial.print("SPEED (km/h) = "); 
//       Serial.println(gps.speed.kmph()); 
//       Serial.print("ALT (min)= "); 
//       Serial.println(gps.altitude.meters());
//       Serial.print("HDOP = "); 
//       Serial.println(gps.hdop.value() / 100.0); 
//       Serial.print("Satellites = "); 
//       Serial.println(gps.satellites.value()); 
//       Serial.print("Time in UTC: ");
//       Serial.println(String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()) + "," + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
//       Serial.println("");
//     }
//   }
// }


// void processGPSData(bool countinousCapture, short captureInterval_ms) {
  
//   unsigned long start = millis();
  
//   while (millis() - start < captureInterval_ms && countinousCapture) { // Collect data for 1 second
//     while (hardSerial.available() > 0) {
//       gps.encode(hardSerial.read());
//     }
//   }
// }

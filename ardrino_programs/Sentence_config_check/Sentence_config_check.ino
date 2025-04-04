/*
  This program reads GPS data from a NEO-6M GPS module and displays the date/time,
  location, speed, HDOP, and number of satellites information on the Serial Monitor.
  This is specific to ESP32.

  Configuration:
  - GPS_BAUD: Baud rate for GPS module communication
  - GPS_RX_PIN: RX pin for SoftwareSerial communication
  - GPS_TX_PIN: TX pin for SoftwareSerial communication

  Output format:
  Date/Time: <month>/<day>/<year> <hour>:<minute>:<second>.<centisecond>  Location: <latitude>,<longitude>  Speed: <speed> km/h  HDOP: <hdop> (<V/NV>)  Satellites: <satellites> (<V/NV>)

  Example output:
  Date/Time: 3/2/2025 04:41:19.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
  Date/Time: 3/2/2025 04:41:19.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
  Date/Time: 3/2/2025 04:41:20.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
  Date/Time: 3/2/2025 04:41:20.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
  Date/Time: 3/2/2025 04:41:20.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
  Date/Time: 3/2/2025 04:41:20.00  Location: 30.651246,76.846963  Speed: 0.00 km/h  HDOP: 1.00 (V)  Satellites: 8 (V)
*/

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Configuration constants
#define GPS_BAUD 9600
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// Configuration flags
bool showDateTime = true;
bool showLocation = true;
bool showSpeed = true;
bool showHDOP = true;
bool showSatellites = true;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

// Function to send UBX command
void sendUBXCommand(byte *MSG, uint8_t len) {
    for (int i = 0; i < len; i++) {
        gpsSerial.write(MSG[i]);
    }
    gpsSerial.println();
}

// Function to disable GGA sentence
void disableGGA() {
    byte disableGGA[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x23 };
    sendUBXCommand(disableGGA, sizeof(disableGGA));
}

// Function to disable GLL sentence
void disableGLL() {
    byte disableGLL[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x22 };
    sendUBXCommand(disableGLL, sizeof(disableGLL));
}

// Function to disable GSA sentence
void disableGSA() {
    byte disableGSA[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFD, 0x21 };
    sendUBXCommand(disableGSA, sizeof(disableGSA));
}

// Function to disable GSV sentence
void disableGSV() {
    byte disableGSV[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x20 };
    sendUBXCommand(disableGSV, sizeof(disableGSV));
}

// Function to disable RMC sentence
void disableRMC() {
    byte disableRMC[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFB, 0x1F };
    sendUBXCommand(disableRMC, sizeof(disableRMC));
}

// Function to disable VTG sentence
void disableVTG() {
    byte disableVTG[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFA, 0x1E };
    sendUBXCommand(disableVTG, sizeof(disableVTG));
}

// Function to disable TXT sentence
void disableTXT() {
    byte disableTXT[] = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9, 0x1D };
    sendUBXCommand(disableTXT, sizeof(disableTXT));
}

void setup() {
    Serial.begin(115200);    // Serial monitor
    gpsSerial.begin(9600); // GPS baud rate (default is 9600)

    delay(2000); // Wait for GPS module to initialize

    Serial.println("Disabling selected NMEA sentences...");

    disableGGA();
    disableGLL();
    disableGSA();
    disableGSV();
    disableRMC();
    disableVTG();
    disableTXT();

    Serial.println("NMEA sentences disabled.");
}

void loop() {
    while (gpsSerial.available()) {
        Serial.write(gpsSerial.read()); // Print remaining GPS data
    }
}



// void setup() {
//   Serial.begin(115200);
//   gpsSerial.begin(GPS_BAUD);
//   Serial.println("Waiting for GPS signal...");
// }

// void loop() {
//   while (gpsSerial.available() > 0) {
//     char c = gpsSerial.read();
//     Serial.print(c); // Print raw NMEA sentence
//     gps.encode(c);   // Parse the data
//   }
//   displayInfo();
//   delay(300);
// }

void displayInfo() {
  if (showDateTime) displayDateTime();
  if (showLocation) displayLocation();
  if (showSpeed) displaySpeed();
  if (showHDOP) displayHDOP();
  if (showSatellites) displaySatellites();
  Serial.println();
}

void displayDateTime() {
  Serial.print(F("Date/Time: "));
  if (gps.date.isValid() && gps.time.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    Serial.print(F(" "));
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  "));
}

void displayLocation() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  "));
}

void displaySpeed() {
  Serial.print(F("Speed: "));
  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph());
    Serial.print(F(" km/h"));
  } else {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  "));
}

void displayHDOP() {
  Serial.print(F("HDOP: "));
  Serial.print(gps.hdop.value() / 100.0);
  if (gps.hdop.isValid()) {
    Serial.print(F(" (V)"));
  } else {
    Serial.print(F(" (NV)"));
  }
  Serial.print(F("  "));
}

void displaySatellites() {
  Serial.print(F("Satellites: "));
  Serial.print(gps.satellites.value());
  if (gps.satellites.isValid()) {
    Serial.print(F(" (V)"));
  } else {
    Serial.print(F(" (NV)"));
  }
  Serial.print(F("  "));
}
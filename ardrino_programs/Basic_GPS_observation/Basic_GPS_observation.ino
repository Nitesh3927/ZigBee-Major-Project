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

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD);
  Serial.println("Waiting for GPS signal...");

  Serial.println("Sending factory reset command to GPS...");
  resetToFactorySettings();
  Serial.println("Factory reset command sent. Restart the GPS module to apply changes.");
}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    // Serial.print(c); // Print raw NMEA sentence
    gps.encode(c);   // Parse the data
  }
  
  displayInfo();
  delay(300);
}

// Function to reset GPS to factory settings
void resetToFactorySettings() {
  // UBX-CFG-CFG command to reset to factory settings
  uint8_t factoryResetCommand[] = {
      0xB5, 0x62, // UBX header
      0x06, 0x09, // CFG-CFG class and ID
      0x0D, 0x00, // Payload length (13 bytes)
      0xFF, 0xFF, 0x00, 0x00, // Clear mask (reset all configurations)
      0xFF, 0xFF, 0x00, 0x00, // Save mask (not saving anything)
      0xFF, 0xFF, 0x00, 0x00, // Load mask (load factory defaults)
      0x01,                   // Device mask (apply to GPS module)
      0x1D, 0xAB              // Checksum (calculated for the payload)
  };

  // Send the command to the GPS module
  for (uint8_t i = 0; i < sizeof(factoryResetCommand); i++) {
    gpsSerial.write(factoryResetCommand[i]);
  }
}

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

// void gpsStuff() {
  
//   gps.altitude.feet()
//   gps.altitude.kilometers()
//   gps.altitude.meters()
//   gps.altitude.miles()
//   gps.altitude.value()

//   gps.course.deg()
//   gps.course.value()

//   gps.date.day()
//   gps.date.month()
//   gps.date.year()
  
//   gps.time.hour()
//   gps.time.minute()
//   gps.time.second()
//   gps.time.centisecond()

//   gps.hdop.value()
  
//   gps.satellites.value()

//   gps.speed.kmph()

//   gps.location.lat()
//   gps.location.lng()

// }
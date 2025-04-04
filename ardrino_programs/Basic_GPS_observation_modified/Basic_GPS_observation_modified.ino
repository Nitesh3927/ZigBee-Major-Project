#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Configuration constants
#define GPS_BAUD 9600
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17


byte setUpdateRate[] = {
  0xB5, // sync char 1
  0x62, // sync char 2
  0x06, // class
  0x08, // id
  0x06, // length
  0x00, // length
  0x64, // payload
  0x00, // payload
  0x01, // payload
  0x00, // payload
  0x01, // payload
  0x00, // payload
  0x7A, // CK_A
  0x12, // CK_B
};

byte setBaudRate[] = {	  
  0xB5, // sync char 1
  0x62, // sync char 2
  0x06, // class
  0x00, // id
  0x14, // length
  0x00, // length
  0x01, // payload
  0x00, // payload
  0x00, // payload
  0x00, // payload
  0xD0, // payload
  0x08, // payload
  0x00, // payload
  0x00, // payload
  0x00, // payload
  0xC2, // payload
  0x01, // payload
  0x00, // payload
  0x07, // payload
  0x00, // payload
  0x03, // payload
  0x00, // payload
  0x00, // payload
  0x00, // payload
  0x00, // payload
  0x00, // payload
  0xC0, // CK_A
  0x7E}; // CK_B
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

  setGPSBaudRate(115200); // Set GPS baud rate to 115200
  setGPSUpdateRate(5);    // Set GPS update rate to 5Hz

}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    Serial.print(c);
    gps.encode(c);   // Parse the data
  }
  
  // displayInfo();
  delay(200);
}


void setGPSBaudRate(unsigned long baudRate) {
  // byte setBaudRate[] = {
  //   0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00,
  //   0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xC2,
  //   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //   0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  // };
  // setBaudRate[14] = (byte)(baudRate & 0xFF);
  // setBaudRate[15] = (byte)((baudRate >> 8) & 0xFF);
  // setBaudRate[16] = (byte)((baudRate >> 16) & 0xFF);
  // setBaudRate[17] = (byte)((baudRate >> 24) & 0xFF);

  sendUBXCommand(setBaudRate, sizeof(setBaudRate));
  gpsSerial.end();
  gpsSerial.begin(baudRate);
}

void setGPSUpdateRate(int hz) {
  // byte setUpdateRate[] = {
  //   0xB5, 0x62, 0x06, 0x08, 0x06, 0x00,
  //   0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12
  // };
  // int period = 1000 / hz; // Calculate update period in milliseconds
  // setUpdateRate[6] = (byte)(period & 0xFF);
  // setUpdateRate[7] = (byte)((period >> 8) & 0xFF);

  sendUBXCommand(setUpdateRate, sizeof(setUpdateRate));
}

void sendUBXCommand(byte *command, int length) {
  for (int i = 0; i < length; i++) {
    gpsSerial.write(command[i]);
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


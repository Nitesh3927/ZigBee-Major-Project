
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>

// Configuration constants
#define GPS_BAUD 9600
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_UPDATE_RATE_HZ  5 // Update rate in Hz
#define GPS_DYNAMIC_MODE 4   // Dynamic mode (4: Automotive)
#define I2C_ADDRESS 0x3C     // I2C address

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD);
  Wire.begin(); // Initialize I2C as master
  Serial.println("Waiting for GPS signal...");

  // Configure update rate
  configureGPSUpdateRate(GPS_UPDATE_RATE_HZ);

  // Configure dynamic mode
  configureGPSDynamicMode(GPS_DYNAMIC_MODE);

  // Change GPS baud rate to 57600
  // setGPSBaudRate(57600);
  // gpsSerial.end();
  // gpsSerial.begin(57600);
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  String gpsData = getGPSData();
  Serial.println(gpsData);
  // Serial.println(gpsData.length());
  sendI2CData(gpsData);
  delay(1000 / GPS_UPDATE_RATE_HZ);
}

String getGPSData() {
  String gpsData = "";

  if (gps.location.isValid()) {
    gpsData += String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) + "  ";
  } else {
    gpsData += "INVALID ";
  }

  if (gps.speed.isValid()) {
    gpsData += String(gps.speed.kmph());
  } else {
    gpsData += "INVALID ";
  }
  return gpsData;
}

void sendI2CData(String data) {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((const uint8_t*)data.c_str(), data.length());
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("I2C Error: ");
    Serial.println(error);
  }
}
void configureGPSUpdateRate(int rateHz) {
  int rateMs = 1000 / rateHz;
  byte setRate[] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, (byte)(rateMs & 0xFF), (byte)((rateMs >> 8) & 0xFF), 0x00, 0x00, 0x00, 0x00};
  sendUBX(setRate, sizeof(setRate) / sizeof(byte));
}

void configureGPSDynamicMode(int mode) {
  byte setMode[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x00, (byte)mode, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  sendUBX(setMode, sizeof(setMode) / sizeof(byte));
}

void setGPSBaudRate(long baudRate) {
  byte baudRateBytes[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 
                          0x01, 0x00, 0x00, 0x00, 
                          (byte)(baudRate & 0xFF), (byte)((baudRate >> 8) & 0xFF), (byte)((baudRate >> 16) & 0xFF), (byte)((baudRate >> 24) & 0xFF), 
                          0x00, 0x00, 0x00, 0x00, 
                          0x00, 0x00, 0x00, 0x00, 
                          0x00, 0x00, 0x00, 0x00};
  sendUBX(baudRateBytes, sizeof(baudRateBytes) / sizeof(byte));
}

void sendUBX(byte *msg, byte len) {
  for (byte i = 0; i < len; i++) {
    gpsSerial.write(msg[i]);
  }
  gpsSerial.flush();
}
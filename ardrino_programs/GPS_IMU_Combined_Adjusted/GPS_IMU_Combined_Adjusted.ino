#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TinyGPS++.h>

#define I2C_ADDR_32_H2 0x3C
#define STRING_LENGHT 127

#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600
HardwareSerial hardSerial(2);
TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

float acc_x_offset = 0.9;
float acc_y_offset = -0.5;
float acc_z_offset = 0.9;
uint32_t i = 0;
String data;

void initializeMPU6050() {
  Serial.println("Initializing MPU6050...");
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip. Retrying in 1 second...");
    delay(1000);
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.println("MPU6050 configuration complete.");
}

void initializeGPSSerial() {
  hardSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("GPS Serial started at 9600 baud rate");
}

void processGPSData() {
  while (hardSerial.available() > 0) {
    gps.encode(hardSerial.read());
  }
}

void printCombinedData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  a.acceleration.x -= acc_x_offset;
  a.acceleration.y -= acc_y_offset;
  a.acceleration.z -= acc_z_offset;

  data = "";

  char buffer[100];
  sprintf(buffer, 
          "%+06.2f%+06.2f%+06.2f%09.6f%010.6f%05.2f",
          a.acceleration.x, a.acceleration.y, a.acceleration.z, 
          gps.location.lat(), gps.location.lng(), gps.speed.kmph());

  data = String(buffer); 
}

void onRequest() {
  Wire.print(i++);
  Wire.print(" Packets.");
  Serial.println("onRequest");
  Serial.println();
}

void onReceive(int len) {
  Serial.printf("Recived Data: ");
  while (Wire.available()) {
    Serial.write(Wire.read());
  }
  Serial.println();
}


void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22, 400000);
  initializeGPSSerial();
  initializeMPU6050();
  Serial.println("Setup complete.");
  delay(1000);
}

void loop() {
  processGPSData();
  printCombinedData();
  Serial.println(data);
  Serial.print(">>");
  Serial.print(gps.distanceBetween(gps.location.lat(), gps.location.lng(), 30.76671716, 76.789977));
  Serial.println("<<");

  Wire.beginTransmission(I2C_ADDR_32_H2);
  // Serial.println(data.length());
  Wire.print(data);
  Wire.endTransmission();
  delay(100);
}

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TinyGPS++.h>
// #include <string.h>

// Default I2C address for MPU6050 0x68

// PIN DEFINITIONS
// --------------------------------------------------------------------------
#define I2C_ADDR_32_H2 0x3C
#define STRING_LENGHT 127

// ESP32
#define RXD2 16
#define TXD2 17

// ESP32-H2
// #define RXD2 23
// #define TXD2 24


// BAUD AND SERIAL DEFINITIONS
// --------------------------------------------------------------------------
#define GPS_BAUD 9600
HardwareSerial hardSerial(2);
TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

// --------------------------------------------------------------------------
// MPU6050 FUNCTIONS
// --------------------------------------------------------------------------
float acc_x_offset = 0.47;
float acc_y_offset = -0.12;
float acc_z_offset = 10.63;
uint32_t i = 0;
// const char newData[STRING_LENGHT]; 
String data;

void initializeMPU6050() {
  Serial.println("Initializing MPU6050...");
  while (!mpu.begin()) {  // Try to initialize MPU6050
    Serial.println("Failed to find MPU6050 chip. Retrying in 1 second...");
    delay(1000);          // Wait for 1 second before retrying
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.println("MPU6050 configuration complete.");
}

void displayMPU6050Data() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calibrate accelerometer values
  a.acceleration.x -= 0.47;
  a.acceleration.y += 0.12;
  a.acceleration.z -= 10.63;

  Serial.println("MPU6050 Data:");
  Serial.printf("Time: %.3f ", millis() / 1000.0);
  Serial.printf("Accel X: %.2f m/s^2, Y: %.2f m/s^2, Z: %.2f m/s^2\n",
                a.acceleration.x, a.acceleration.y, a.acceleration.z);
}

// --------------------------------------------------------------------------
// GPS FUNCTIONS
// --------------------------------------------------------------------------
void initializeGPSSerial() {
  hardSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("GPS Serial started at 9600 baud rate");
}

void processGPSData() {
  while (hardSerial.available() > 0) {
    gps.encode(hardSerial.read());
  }
}

void displayGPSData() {
  if (gps.location.isUpdated()) {
    Serial.println("GPS Data:");
    Serial.printf("Time: %.4f, Lat: %.6f, Lon: %.6f, Speed: %.2f km/h, Alt: %.2f m\n",
                  millis() / 1000.0, gps.location.lat(), gps.location.lng(),
                  gps.speed.kmph(), gps.altitude.meters());
  } else {
    Serial.println("No GPS data available.");
  }
}

// --------------------------------------------------------------------------
// SUPPORT FUNCTIONS
// --------------------------------------------------------------------------
void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (hardSerial.available()) {
      gps.encode(hardSerial.read());
    }
  } while (millis() - start < ms);
}

void printCombinedData() {
  // Get MPU6050 data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calibrate accelerometer values
  a.acceleration.x -= acc_x_offset;
  a.acceleration.y -= acc_y_offset;
  a.acceleration.z -= acc_z_offset;

  data = "";

  // Format the accelerometer and GPS data using sprintf and store it in the String
  char buffer[100];  // Temporary buffer for formatted string
  sprintf(buffer, 
          "Acc: %+06.2f %+06.2f %+06.2f | Lat: %+012.6f Lon: %+012.6f V: %+07.2f m/s",
          a.acceleration.x, a.acceleration.y, a.acceleration.z, 
          gps.location.lat(), gps.location.lng(), gps.speed.kmph());

  // Append the formatted string to the String variable
  data = String(buffer); 

}

void onRequest() {
  Wire.print(i++);
  Wire.print(" Packets.");
  Serial.println("onRequest");
  Serial.println();
}

void onReceive(int len) {
  // Serial.printf("Recived Data of [%d]: ", len);
  Serial.printf("Recived Data: ");
  while (Wire.available()) {
    Serial.write(Wire.read());
  }
  Serial.println();
}


// --------------------------------------------------------------------------
// SETUP AND LOOP
// --------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  // Wire.begin((uint8_t)I2C_ADDR_32_H2, 21, 22);
  Wire.begin(21, 22, 400000);
  // Wire.onReceive(onReceive);
  // Wire.onRequest(onRequest);
  initializeGPSSerial();
  initializeMPU6050();
  Serial.println("Setup complete.");
  delay(1000);
}

void loop() {
  processGPSData();
  printCombinedData();
  Serial.println(data);
  Serial.println(data.length());

  Wire.beginTransmission(I2C_ADDR_32_H2);
  Wire.print(data);  // Send data with a specified length
  Wire.endTransmission();
  delay(200);
}

import serial
import time
import re

# ===== Constants =====
COM_PORT = 'COM7'
BAUD_RATE = 921600

# ===== Setup =====
ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
time.sleep(2)  # Wait for Arduino to reset
pattern = re.compile(
    r'<\s*([A-Z|_]+)\s*\(\s*(\d+)\s*\)\s*\|\|\s*TRANSMIT:\s*(\d+)\s*\|\|\s*\(([\d.]+),\s*([\d.]+),\s*([\d.]+)\)\s*\|\|\s*RECEIVING:\s*(\d+)\s*\|\|\s*\(([\d.]+),\s*([\d.]+),\s*([\d.]+)\)'
)


# ===== Main Loop =====
try:
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if line:
            status, status_code, transmit, lat, lng, speed, receiving, foreign_lat, foreign_lng, foreign_speed = pattern.findall(line)[0]
            print(f"Status: {status}, Code: {status_code}, Transmit: {transmit}, "
                      f"Lat: {lat}, Lng: {lng}, Speed: {speed}, Receiving: {receiving}, "
                      f"Foreign Lat: {foreign_lat}, Foreign Lng: {foreign_lng}, Foreign Speed: {foreign_speed}")


except KeyboardInterrupt:
    print("Logging stopped by user.")
finally:
    ser.close()

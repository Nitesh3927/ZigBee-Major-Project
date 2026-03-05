Zigbee based Machine to Machine Communication for On-road Low-visibility Collision Prevention

<img width="1403" height="784" alt="Screenshot 2026-03-05 at 8 48 01 PM" src="https://github.com/user-attachments/assets/3fa9b99a-6c09-4fd4-92e4-6868d7e530d0" />

THIS PROJECT AIMS TO ACCOMPLISH THE FOLLOWING:

1.Vehicle-to-vehicle (V2V) communication to enhance transportation safety and efficiency, especially in adverse conditions like snowstorm or smog where traditional navigation aids often fail.

2.Zigbee, a low-power and cost-effective protocol, to be integrated with ESP32-H2 micro controllers to establish reliable short-range wireless communication between vehicles.

3. To use GPS modules (Neo-6M) for real-time location tracking and acceleration monitoring (MPU-6050) for motion monitoring, ensuring precise and timely data exchange.

A high level overview:

<img width="574" height="396" alt="Screenshot 2026-03-05 at 8 48 52 PM" src="https://github.com/user-attachments/assets/41fded1d-fd06-4b83-9db1-43627eded5d1" />

1.	Sensors collect data
	•	MPU6050 (Accelerometer + Gyroscope) sends motion data (X, Y, Z) through the I²C bus.
	•	NEO-6M GPS module sends latitude, longitude, and speed through UART serial.
2.	Data processing
	•	A warning algorithm receives:
	•	Vehicle motion data from the MPU6050
	•	GPS location and speed from the NEO-6M
	•	Data received from other vehicles via Zigbee
	•	It calibrates acceleration and checks thresholds to detect events like sudden braking or danger.
3.	Vehicle communication
	•	An ESP32-H2 Zigbee transmitter:
	•	Receives packets from nearby vehicles.
	•	Sends warning packets containing the vehicle’s GPS and status.
4.	Hence, as a result,
	•	Vehicles share position and warning signals wirelessly, allowing nearby cars to detect hazards early and react.

The complete physical circuit diagram of a single node would look something like this:
<img width="4449" height="1776" alt="COMPLETE CIRCUIT DIAGRAM" src="https://github.com/user-attachments/assets/38950552-d581-40a6-8c47-e15c03adf85f" />

A detailed flowchart ( for nerds ):
<img width="8064" height="5283" alt="MCU-FLOWCHART" src="https://github.com/user-attachments/assets/bf70e22f-6881-42a2-9081-68e6a7c66078" />



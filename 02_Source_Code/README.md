# Source Code Overview

This folder contains all development code including firmware, algorithms, and utilities.

## Directory Structure

### 📁 ESP_Zigbee_Devices_Final/
**Zigbee Firmware for ESP32-H2 devices**

#### Coordinator/
- **Purpose**: Acts as the Zigbee network coordinator
- **Responsibilities**:
  - Forms and manages the Zigbee network
  - Routes packets between vehicles
  - Stores and forwards warning messages
  - Manages device joining/leaving

- **Key Files**:
  - `main/` - Coordinator firmware source code
  - `CMakeLists.txt` - Build configuration
  - `sdkconfig.defaults` - ESP-IDF default settings
  - `partitions.csv` - Memory partition layout

#### End_Device/
- **Purpose**: Vehicle node firmware for ESP32-H2
- **Responsibilities**:
  - Collects GPS and accelerometer data
  - Implements collision detection algorithm
  - Creates and transmits VSP packets
  - Receives warnings from other vehicles

- **Key Files**:
  - `main/` - Vehicle node firmware source code
  - `CMakeLists.txt` - Build configuration
  - `sdkconfig.defaults` - ESP-IDF default settings
  - `partitions.csv` - Memory partition layout

**Build & Deploy**:
```bash
# Build coordinator or end device
idf.py build

# Flash to device
idf.py -p COM3 flash

# Monitor serial output
idf.py -p COM3 monitor
```

---

### 📁 matlab_developement/
**Simulink Models and Algorithm Development**

#### core_logic/
- **Description**: Core collision detection and warning algorithm
- **Key Files**:
  - `core_logic.slx` - Main Simulink model
  - `warning_system_harness.slx` - Test harness
  - Data structures and configuration files

#### acceration/
- **Description**: Accelerometer data processing
- **Files**:
  - `Acc.slx` - MPU-6050 data acquisition model
  - `config.m` - Acceleration sensor configuration

#### acceration_interface/
- **Description**: MATLAB/Simulink interface for accelerometer
- **Contains**: Integration between real hardware and simulation

#### example_GPS/
- **Description**: GPS module integration examples
- **Key Files**:
  - `arduino_serial_gps.slx` - GPS communication model
  - `GPSParser.m` - NMEA sentence parser
  - Sample GPS data files
  - `gps_parser/` - GPS parsing subsystem

#### example_MPU6050/
- **Description**: MPU-6050 accelerometer examples
- **Contains**: Reference implementations for sensor integration

#### gps_direct/
- **Description**: Direct GPS communication without Simulink
- **Key Files**:
  - `gps_direct.slx` - Direct GPS interface model
  - C++ implementations for embedded systems
  - `GPSParser.m` - NMEA parser

#### warning_system/
- **Description**: Complete warning system implementation
- **Key Files**:
  - `warning_system.slx` - Complete warning algorithm
  - `WarningSystem.prj` - Project file
  - `gps_parser/` - GPS parsing module
  - `TinyGPSPlus/` - GPS library

#### builder_system/
- **Description**: Integrated system builder
- **Purpose**: Combines all subsystems into complete model
- **Files**:
  - `builder_system.slx` - Master integration model
  - Data structure definitions
  - Subsystem references

---

### 📁 common/
**Shared Utilities and Drivers**

#### Files:
- `serial_reader.py` - Python utility to read serial data from devices
- `map.py` - Visualization and mapping utilities
- `try_map.html` / `route_map_custom_colors.html` - Interactive map visualizations

#### light_driver/
- **Purpose**: Lightweight driver implementation
- **Contents**:
  - `CMakeLists.txt` - Build configuration
  - `include/` - Header files
  - `src/` - Source implementation

---

### 📁 standalone_test/
**Standalone Test Builds**

#### Co_ordinator/
- **Description**: Standalone coordinator test build
- **Contents**:
  - `build/` - Compiled binaries
  - `managed_components/` - Dependencies

#### Endpoint_1/
- **Description**: Standalone end-device test build
- **Contents**:
  - `build/` - Compiled binaries
  - `managed_components/` - Dependencies

---

## Development Workflow

### 1. **Algorithm Development** (MATLAB/Simulink)
```
Open matlab_developement/core_logic/core_logic.slx
 ↓
Modify algorithm parameters
 ↓
Run simulation with test data
 ↓
Export to C code or deploy to device
 ↓
Validate results
```

### 2. **Firmware Development** (C/C++)
```
Edit code in ESP_Zigbee_Devices_Final/End_Device/main/
 ↓
Build with: idf.py build
 ↓
Flash to device: idf.py -p COM3 flash
 ↓
Monitor output: idf.py -p COM3 monitor
 ↓
Debug and iterate
```

### 3. **Testing & Validation**
```
Run firmware on multiple devices
 ↓
Capture serial output to log files
 ↓
Process with Python utilities
 ↓
Analyze results and generate plots
```

---

## Key Algorithms & Models

### Vehicular Status Packet (VSP) Creation
- Formats: Latitude, Longitude, Speed, Address, Status
- Transmission: Via Zigbee to other vehicles
- Processing: Collision detection based on proximity and motion

### Collision Detection Algorithm
```
Input: GPS position, Velocity, Acceleration
 ↓
Calculate relative position to other vehicles
 ↓
Compute time-to-collision (TTC)
 ↓
Apply safety thresholds
 ↓
Generate warning if threshold exceeded
```

### Acceleration Data Processing
```
Read I²C data from MPU-6050
 ↓
Calibrate X, Y, Z values
 ↓
Detect sudden changes (braking events)
 ↓
Feed into warning algorithm
```

---

## Important Configuration Files

### CMakeLists.txt
- Defines build targets and compilation flags
- Specifies dependencies and libraries
- Configures partition sizes

### sdkconfig.defaults
- ESP-IDF configuration options
- Feature enables/disables
- Performance parameters

### config.m (MATLAB)
- Simulation parameters
- Sensor calibration values
- Timing and thresholds

---

## Building & Deployment

### Build Firmware:
```bash
cd ESP_Zigbee_Devices_Final/End_Device
idf.py build
```

### Flash to Device:
```bash
idf.py -p COM3 flash
```

### Monitor Serial Output:
```bash
idf.py -p COM3 monitor
```

### View Available COM Ports:
```bash
device manager  # Windows
ls /dev/tty*    # Linux/Mac
```

---

## Debugging

### Using MATLAB Debugger:
- Open Simulink model
- Set breakpoints
- Run step-by-step simulation
- Monitor variable values

### Using Serial Monitor:
- Run: `idf.py -p COM3 monitor`
- View real-time device output
- Troubleshoot serial communication

### Log Files:
- Captured in `03_Testing_Validation/log_data_files/`
- Parse with Python scripts
- Generate analysis plots

---

## Next Steps

1. **Start with MATLAB**: Understand algorithms in `matlab_developement/core_logic/`
2. **Review Examples**: Check `example_GPS/` and `example_MPU6050/`
3. **Build Firmware**: Compile `ESP_Zigbee_Devices_Final/End_Device/`
4. **Test System**: Deploy and validate with test data
5. **Analyze Results**: Process logs in `03_Testing_Validation/`

---

For more details, refer to `PROJECT_DEVELOPMENT_GUIDE.md` in the root directory.

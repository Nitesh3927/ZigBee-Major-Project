# ZigBee Vehicle-to-Vehicle Communication System - Development Guide

## Project Overview

This is a comprehensive guide to the **ZigBee-based Machine-to-Machine Communication for On-road Low-visibility Collision Prevention** project. The project implements vehicle-to-vehicle (V2V) communication using Zigbee protocol to enhance transportation safety in adverse weather conditions.

### Project Objectives
1. **Enable V2V Communication**: Establish reliable wireless communication between vehicles using Zigbee
2. **Real-time Tracking**: Integrate GPS modules for accurate vehicle location and speed monitoring
3. **Motion Detection**: Use accelerometers to detect vehicle dynamics and sudden events
4. **Safety Alerts**: Implement a warning algorithm to detect and communicate collision hazards

---

## Directory Structure Guide

### 📁 01_Setup_Configuration/
**Purpose**: Contains all configuration files and setup documentation
- `MATLAB_ESP_setup.txt` - Arduino CLI and MATLAB setup instructions for ESP32
- `Links.txt` - Reference links to documentation and resources
- `README.md` - Original project overview and architecture diagrams

**Key Setup Steps**:
1. Configure Arduino CLI with ESP32 board manager
2. Install ESP32 core v2.0.11 or compatible version
3. Set up MATLAB support packages for ESP32 and sensors
4. Configure serial communication paths for GPS and MPU-6050

---

### 📁 02_Source_Code/
**Purpose**: Contains all development code and firmware

#### Structure:
```
02_Source_Code/
├── ESP_Zigbee_Devices_Final/     # Final Zigbee device firmware
│   ├── Coordinator/              # Zigbee coordinator node
│   │   ├── main/                 # Main coordinator code
│   │   ├── CMakeLists.txt
│   │   ├── partitions.csv
│   │   └── sdkconfig.defaults
│   └── End_Device/               # Zigbee end device (vehicle nodes)
│       ├── main/                 # Vehicle node firmware
│       ├── CMakeLists.txt
│       ├── partitions.csv
│       └── sdkconfig.defaults
│
├── matlab_developement/          # MATLAB Simulink models
│   ├── core_logic/              # Core collision detection algorithm
│   │   ├── core_logic.slx       # Main Simulink model
│   │   ├── warning_system_harness.slx
│   │   └── data structures
│   ├── acceration/              # Accelerometer processing
│   │   ├── Acc.slx
│   │   └── config.m
│   ├── acceration_interface/    # Accelerometer-Simulink integration
│   ├── example_GPS/             # GPS module integration examples
│   │   ├── arduino_serial_gps.slx
│   │   ├── GPSParser.m
│   │   └── gps_parser/
│   ├── example_MPU6050/         # MPU6050 accelerometer examples
│   ├── gps_direct/              # Direct GPS communication
│   ├── warning_system/          # Complete warning system
│   └── bulider_system/          # System builder/integration models
│
├── common/                       # Shared utilities and utilities
│   ├── map.py                   # Map visualization and processing
│   ├── serial_reader.py         # Serial data reading utilities
│   ├── light_driver/            # Light driver implementation
│   │   ├── CMakeLists.txt
│   │   ├── include/
│   │   └── src/
│   └── HTML map files           # Interactive map visualizations
│
└── standalone_test/             # Standalone testing implementations
    ├── Co_ordinator/            # Coordinator test build
    │   ├── build/
    │   └── managed_components/
    └── Endpoint_1/              # End device test build
        ├── build/
        └── managed_components/
```

---

### 📁 03_Testing_Validation/
**Purpose**: Contains all test data, logs, and validation materials

#### Structure:
```
03_Testing_Validation/
├── testing_stuff/
│   ├── log_data_files/          # Raw test logs from devices
│   │   ├── acc_test_*.txt       # Accelerometer test data
│   │   ├── COM*_distance_test_*.txt  # Distance/range tests
│   │   ├── COM*_static_test_*.txt    # Static position tests
│   │   └── [Various COM port data]
│   ├── log_processing/          # Log analysis and processing scripts
│   ├── last_test/               # Latest test results
│   │   ├── plot1.py             # Test plotting scripts
│   │   └── nitesh_ep/           # Endpoint-specific tests
│   └── Documentation/           # Test documentation and results
```

**Test Categories**:
- **Distance Tests**: Validate communication range at various distances
- **Static Tests**: Test position accuracy and signal stability
- **Acceleration Tests**: Verify MPU-6050 data collection and processing
- **Integration Tests**: End-to-end system validation

---

### 📁 04_Resources/
**Purpose**: Contains images, diagrams, and reference materials

- **System architecture diagrams**
- **Circuit schematics**
- **Block diagrams and flowcharts**
- **Project photos and documentation images**

---

## Development Process Overview

### Phase 1: Environment Setup
1. **MATLAB/Simulink Installation**
   - Install MATLAB with Simulink support packages
   - Configure Arduino support for ESP32
   - Add necessary third-party toolchain support

2. **Hardware Setup**
   - Configure ESP32-H2 microcontrollers
   - Set up serial communication interface (COM ports)
   - Install necessary drivers for sensors and debuggers

3. **Reference Documentation**
   - Review Links.txt for ESP32 and sensor documentation
   - Study provided MATLAB/Simulink examples
   - Understand Zigbee protocol basics

### Phase 2: Algorithm Development (MATLAB/Simulink)
1. **GPS Module Integration** (`example_GPS/`, `gps_direct/`)
   - Parse NEO-6M GPS NMEA sentences
   - Extract latitude, longitude, and speed
   - Implement serial communication protocol

2. **Accelerometer Processing** (`acceration/`, `example_MPU6050/`)
   - Read I²C data from MPU-6050
   - Calibrate and process X, Y, Z acceleration values
   - Implement event detection (sudden braking, collision risk)

3. **Core Logic Development** (`core_logic/`)
   - Implement warning algorithm
   - Define collision detection thresholds
   - Create Vehicular Status Packet (VSP) structure
   - Design state machine for vehicle status (normal, warning, emergency)

### Phase 3: System Integration (`bulider_system/`)
1. Combine GPS, accelerometer, and communication modules
2. Integrate all subsystems into complete model
3. Test data flow and timing between components
4. Validate packet structure and communication

### Phase 4: Firmware Development (ESP32-H2)
1. **Coordinator Firmware** (`ESP_Zigbee_Devices_Final/Coordinator/`)
   - Implement Zigbee coordinator role
   - Manage network formation
   - Handle packet routing and forwarding
   - Store and distribute vehicle warning information

2. **End Device Firmware** (`ESP_Zigbee_Devices_Final/End_Device/`)
   - Implement Zigbee end device role
   - Interface with sensors (GPS, MPU-6050)
   - Create and transmit VSP packets
   - Receive and process warnings from other vehicles

### Phase 5: Testing & Validation (`03_Testing_Validation/`)
1. **Unit Testing**
   - Test individual sensor interfaces
   - Validate serial communication
   - Verify packet structure

2. **Integration Testing**
   - Test multiple devices communicating
   - Validate range and signal strength
   - Test in various weather/visibility conditions

3. **Range Testing**
   - Document maximum transmission distance
   - Test signal stability over distance
   - Identify dead zones or interference areas

4. **Static Testing**
   - Verify position accuracy
   - Test GPS signal acquisition time
   - Validate system reliability in stationary state

---

## Key Components

### Hardware Stack
| Component | Purpose | Interface |
|-----------|---------|-----------|
| **ESP32-H2** | Microcontroller | Central processing unit |
| **NEO-6M GPS** | Location tracking | UART Serial (RX/TX) |
| **MPU-6050** | Motion detection | I²C Bus (SDA/SCL) |
| **Zigbee Module** | V2V Communication | Integrated/External module |

### Software Stack
| Layer | Technology | Purpose |
|-------|-----------|---------|
| **Firmware** | C/C++ (ESP-IDF) | Device control and communication |
| **Simulation** | MATLAB/Simulink | Algorithm design and validation |
| **Testing** | Python | Data processing and analysis |
| **Visualization** | HTML/Python | Results display and mapping |

---

## Data Structures

### Vehicular Status Packet (VSP)
```
Total Size: 15 bytes
├─ Latitude (float, 4 bytes)      - Vehicle GPS latitude
├─ Longitude (float, 4 bytes)     - Vehicle GPS longitude
├─ Speed (float, 4 bytes)         - Current vehicle speed
├─ Address (uint16, 2 bytes)      - Vehicle unique identifier
└─ Status (uint8, 1 byte)         - Vehicle state (0=normal, 1=warning, 2=emergency)
```

---

## Communication Flow

```
Sensors (GPS, MPU-6050)
    ↓
[MATLAB Algorithm Processing]
    ↓
[Collision Detection Logic]
    ↓
[Create VSP Packet]
    ↓
[Zigbee Transmission via ESP32-H2]
    ↓
[Other Vehicles Receive]
    ↓
[Update Local Warning System]
```

---

## Development Workflow

### 1. **Simulink Development**
- Open `matlab_developement/` models
- Modify and simulate algorithms
- Test with sample data
- Validate packet structure
- Export to code generation

### 2. **Firmware Deployment**
- Update firmware in `ESP_Zigbee_Devices_Final/`
- Configure CMake and build settings
- Flash to ESP32-H2 devices
- Verify serial communication

### 3. **Testing & Validation**
- Collect data logs to `03_Testing_Validation/log_data_files/`
- Process logs using scripts in `log_processing/`
- Analyze results and document findings
- Generate plots and reports

### 4. **Iteration**
- Review test results
- Identify issues or improvements
- Update algorithm or firmware
- Repeat testing cycle

---

## Key Files & Scripts

### Python Utilities (`common/`)
- `serial_reader.py` - Read and parse serial data from devices
- `map.py` - Visualize vehicle positions and routes
- HTML map files - Interactive web-based visualization

### MATLAB Scripts
- `config.m` - Configuration files across all directories
- `createfigure.m` - Figure generation for analysis
- `GPSParser.m` - GPS NMEA sentence parsing

### Test Data Analysis
- Scripts in `03_Testing_Validation/log_processing/`
- Processing and visualization of collected data
- Performance metrics extraction

---

## Quick Start Guide

### For Algorithm Development:
1. Navigate to `02_Source_Code/matlab_developement/core_logic/`
2. Open `core_logic.slx` in MATLAB/Simulink
3. Modify algorithm as needed
4. Run simulations with test data

### For Firmware Development:
1. Navigate to `02_Source_Code/ESP_Zigbee_Devices_Final/End_Device/`
2. Edit main firmware code in `main/` directory
3. Configure CMakeLists.txt if needed
4. Build and flash to device

### For Testing:
1. Run device firmware on multiple ESP32 boards
2. Capture serial data to log files
3. Move log files to `03_Testing_Validation/log_data_files/`
4. Run processing scripts for analysis
5. Review results and plots

---

## Documentation Structure

- **PROJECT_DEVELOPMENT_GUIDE.md** (this file) - Overall development process
- **01_Setup_Configuration/README.md** - Initial setup instructions
- **02_Source_Code/README.md** - Source code organization details
- **03_Testing_Validation/README.md** - Testing procedures and results
- **04_Resources/README.md** - Hardware diagrams and architecture

---

## Important Links & References

See `01_Setup_Configuration/Links.txt` for:
- ESP32-H2 official documentation
- Arduino-CLI setup guides
- GPS module references
- Accelerometer examples
- MATLAB support packages

---

## Version History
- **v1.0** - Complete system with Zigbee V2V communication
- Includes GPS tracking, motion detection, and collision warning algorithm

---

## Next Steps for Development
1. Expand communication range with relay/repeater devices
2. Implement multi-hop Zigbee mesh networking
3. Add real-time visualization dashboard
4. Integrate with vehicle CAN-bus systems
5. Test in actual vehicles under real-world conditions

---

*Last Updated: April 2026*
*For questions or updates, refer to project documentation and team notes.*

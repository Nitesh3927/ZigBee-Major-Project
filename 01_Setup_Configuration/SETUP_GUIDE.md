# Setup & Configuration Guide

This folder contains all configuration files and setup instructions needed to get the ZigBee V2V communication system running.

## Contents

**Start here** to understand the project scope and design.

### 📄 MATLAB_ESP_setup.txt
Complete setup instructions for:
1. **Arduino CLI Configuration**
   - Setting up Arduino board manager for ESP32
   - Installing ESP32 core (v2.0.11)
   - Configuring additional URLs

2. **MATLAB Support Packages**
   - Installing Arduino support for MATLAB/Simulink
   - Adding support for ESP32 hardware
   - Setting up sensor integration

3. **Commands to Execute**
   - Arduino-CLI path configuration
   - Board manager setup
   - Core installation

**Follow these steps** in order to prepare your development environment.

### 📄 Links.txt
Reference documentation links for:
- **ESP32-H2 Developer Kit** - Official hardware documentation
- **FreeRTOS API** - Task delay and scheduling functions
- **Arduino Examples** - GPS and MPU-6050 integration examples
- **MATLAB Support** - Setup guides for third-party hardware

**Use this** when you need detailed documentation on specific components.

---

## Quick Setup Checklist

- [ ] Install MATLAB/Simulink (R2024b or later)
- [ ] Install Arduino IDE and Arduino CLI
- [ ] Follow MATLAB_ESP_setup.txt commands in order
- [ ] Configure ESP32-H2 board in Arduino/MATLAB
- [ ] Set up serial port connections to COM ports
- [ ] Install required drivers for USB programming
- [ ] Verify board detection with Arduino CLI
- [ ] Test sample project compilation and flashing

---

## Next Steps

After completing setup:
1. Review the architecture in README.md
2. Explore `02_Source_Code/` for firmware and algorithms
3. Check `03_Testing_Validation/` for test procedures
4. Refer to `04_Resources/` for diagrams and images

---

## Troubleshooting

**Arduino CLI not found?**
- Check MATLAB support package installation
- Verify path in MATLAB settings
- Reinstall Arduino support package

**ESP32 board not detected?**
- Install USB drivers for ESP32
- Check COM port in Device Manager
- Verify board manager URLs are correct

**Serial communication issues?**
- Ensure baud rate matches (typically 115200)
- Check USB cable is data cable (not charge-only)
- Verify GPIO pins for serial communication

---

For detailed configuration help, refer to the links in Links.txt

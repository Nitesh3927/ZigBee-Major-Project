# ZigBee V2V Communication System - Project Index

## Quick Navigation

Welcome to the organized ZigBee Vehicle-to-Vehicle Communication System project! This guide will help you navigate the project structure.

---

## 📋 Start Here

### 🎯 First Time? Read These in Order:

1. **[PROJECT_DEVELOPMENT_GUIDE.md](PROJECT_DEVELOPMENT_GUIDE.md)** 
   - Complete overview of project, architecture, and development process
   - Understand the system design and workflow
   - *Start here for best understanding*

2. **[01_Setup_Configuration/README.md](01_Setup_Configuration/README.md)**
   - Environment setup and configuration instructions
   - Links to all necessary documentation
   - Setup checklist

3. **[02_Source_Code/README.md](02_Source_Code/README.md)**
   - Source code organization and structure
   - Build and deployment instructions
   - Development workflow

4. **[03_Testing_Validation/README.md](03_Testing_Validation/README.md)**
   - Testing procedures and validation methods
   - Log file descriptions
   - Test analysis workflows

5. **[04_Resources/README.md](04_Resources/README.md)**
   - Hardware diagrams and system architecture
   - Reference materials and documentation
   - Image and diagram guide

---

## 📁 Project Organization

### 01_Setup_Configuration/
**Setup files and configuration guides**
- `README.md` - Original project overview with diagrams
- `SETUP_GUIDE.md` - Setup and configuration instructions
- `MATLAB_ESP_setup.txt` - Arduino CLI and MATLAB setup commands
- `Links.txt` - Reference links to documentation

→ **Use this to**: Set up your development environment

---

### 02_Source_Code/
**All development code and firmware**

**Contents:**
- `ESP_Zigbee_Devices_Final/` - Zigbee firmware for devices
  - `Coordinator/` - Zigbee network coordinator
  - `End_Device/` - Vehicle node firmware
- `matlab_developement/` - Simulink models and algorithms
  - `core_logic/` - Collision detection algorithm
  - `acceration/` - Accelerometer processing
  - `example_GPS/` - GPS integration examples
  - `warning_system/` - Complete warning system
  - Other subsystems and integrations
- `common/` - Shared utilities and drivers
- `standalone_test/` - Test builds for devices

→ **Use this to**: Develop firmware and algorithms

---

### 03_Testing_Validation/
**Test data and validation results**

**Contents:**
- `testing_stuff/log_data_files/` - Raw test logs
  - Accelerometer tests
  - Distance/range tests
  - Static position tests
  - Various COM port captures
- `log_processing/` - Python scripts for data analysis
- `last_test/` - Latest test results
- `Documentation/` - Test reports and methodology

→ **Use this to**: Test, validate, and analyze system performance

---

### 04_Resources/
**Diagrams, images, and documentation**

**Contains:**
- `Documentation/` - Technical specifications and guides
- `pics/` - System diagrams, circuit schematics, photos
  - Circuit diagrams
  - System flowcharts
  - Block diagrams
  - Test setup photos

→ **Use this to**: Reference hardware/system details

---

## 🚀 Quick Start Paths

### Path 1: I want to understand the project
1. Read: `PROJECT_DEVELOPMENT_GUIDE.md`
2. Review: `04_Resources/README.md` for diagrams
3. Study: `01_Setup_Configuration/README.md` for overview

**Time: ~30 minutes**

---

### Path 2: I want to set up the environment
1. Follow: `01_Setup_Configuration/SETUP_GUIDE.md`
2. Execute: Commands from `01_Setup_Configuration/MATLAB_ESP_setup.txt`
3. Reference: `01_Setup_Configuration/Links.txt` for detailed docs

**Time: ~1-2 hours**

---

### Path 3: I want to develop firmware
1. Study: `PROJECT_DEVELOPMENT_GUIDE.md` - Phase 4
2. Review: `02_Source_Code/README.md`
3. Navigate to: `02_Source_Code/ESP_Zigbee_Devices_Final/End_Device/`
4. Edit: Code in `main/` directory
5. Build: Using CMake commands

**Time: Variable**

---

### Path 4: I want to develop algorithms
1. Review: `PROJECT_DEVELOPMENT_GUIDE.md` - Phase 2
2. Open: `02_Source_Code/matlab_developement/core_logic/core_logic.slx`
3. Study: `02_Source_Code/README.md` for model details
4. Modify: Simulink models
5. Test: Run simulations

**Time: Variable**

---

### Path 5: I want to test the system
1. Read: `03_Testing_Validation/README.md`
2. Follow: Test procedures for your scenario
3. Collect: Data in `log_data_files/`
4. Process: Using scripts in `log_processing/`
5. Analyze: Results and compare with baselines

**Time: Variable**

---

## 📊 Directory Statistics

| Directory | Purpose | Key Files |
|-----------|---------|-----------|
| 01_Setup_Configuration | Setup & Config | 4 files |
| 02_Source_Code | Code & Firmware | 4 major directories |
| 03_Testing_Validation | Testing & Data | Test logs + scripts |
| 04_Resources | Diagrams & Docs | Images + documentation |

---

## 🔍 Finding Specific Information

### Looking for...

| Item | Location |
|------|----------|
| **Hardware Circuit Diagram** | `04_Resources/pics/` |
| **System Flowchart** | `04_Resources/pics/` |
| **Algorithm Implementation** | `02_Source_Code/matlab_developement/core_logic/` |
| **Firmware Code** | `02_Source_Code/ESP_Zigbee_Devices_Final/` |
| **Test Procedures** | `03_Testing_Validation/README.md` |
| **Setup Instructions** | `01_Setup_Configuration/SETUP_GUIDE.md` |
| **Arduino Commands** | `01_Setup_Configuration/MATLAB_ESP_setup.txt` |
| **Reference Links** | `01_Setup_Configuration/Links.txt` |
| **Test Data** | `03_Testing_Validation/testing_stuff/log_data_files/` |
| **Project Overview** | `PROJECT_DEVELOPMENT_GUIDE.md` |

---

## 📝 File Descriptions

### Core Files

**PROJECT_DEVELOPMENT_GUIDE.md**
- Complete project documentation
- Development phases explained
- Data structures described
- Workflow diagrams
- Component specifications
- Quick start guides

**README Files (in each directory)**
- Directory-specific guides
- Content organization
- Usage instructions
- Quick reference checklists

---

## 🎓 Learning Path

**Beginner** (Understanding the project):
1. PROJECT_DEVELOPMENT_GUIDE.md
2. 01_Setup_Configuration/README.md
3. 04_Resources/README.md (view diagrams)

**Intermediate** (Setting up & running):
1. Follow setup checklist
2. Review code organization
3. Run basic tests

**Advanced** (Developing & modifying):
1. Study firmware architecture
2. Understand algorithm design
3. Implement custom features
4. Run comprehensive testing

---

## ✅ Organization Summary

✅ **Setup files organized** - All configuration in one place  
✅ **Source code organized** - Firmware and algorithms separated  
✅ **Testing data organized** - Logs and analysis tools grouped  
✅ **Resources organized** - Diagrams and documentation centralized  
✅ **Documentation created** - Clear guides for each section  
✅ **Index created** - This file for easy navigation  

---

## 🔗 Navigation Quick Links

**Getting Started:**
- [PROJECT_DEVELOPMENT_GUIDE.md](PROJECT_DEVELOPMENT_GUIDE.md) - Start here
- [01_Setup_Configuration/SETUP_GUIDE.md](01_Setup_Configuration/SETUP_GUIDE.md) - Setup instructions

**Development:**
- [02_Source_Code/README.md](02_Source_Code/README.md) - Code overview
- [02_Source_Code/matlab_developement/](02_Source_Code/matlab_developement/) - Simulink models
- [02_Source_Code/ESP_Zigbee_Devices_Final/](02_Source_Code/ESP_Zigbee_Devices_Final/) - Firmware

**Testing & Validation:**
- [03_Testing_Validation/README.md](03_Testing_Validation/README.md) - Test procedures
- [03_Testing_Validation/testing_stuff/](03_Testing_Validation/testing_stuff/) - Test data

**Resources:**
- [04_Resources/README.md](04_Resources/README.md) - Diagrams guide
- [04_Resources/pics/](04_Resources/pics/) - System diagrams
- [01_Setup_Configuration/Links.txt](01_Setup_Configuration/Links.txt) - Reference links

---

## ⚠️ Important Notes

- **Nothing was deleted** - All original files are preserved in organized directories
- **Git history preserved** - .git folder maintained for version control
- **Backward compatible** - Original file structure still accessible
- **Expandable** - Easy to add new sections as needed

---

## 💡 Tips for Using This Organization

1. **Bookmark PROJECT_DEVELOPMENT_GUIDE.md** - Return to it frequently
2. **Keep README.md files open** - They guide navigation
3. **Use links** - Click through the markdown links for quick access
4. **Check the index** - This file helps locate anything quickly
5. **Read sequentially** - Follow suggested reading order for new topics

---

## 🆘 Need Help?

1. **Understanding the project?** → Read PROJECT_DEVELOPMENT_GUIDE.md
2. **Setting up environment?** → Follow 01_Setup_Configuration/SETUP_GUIDE.md
3. **Finding code?** → Check 02_Source_Code/README.md
4. **Testing system?** → See 03_Testing_Validation/README.md
5. **Understanding hardware?** → Review 04_Resources/README.md

---

## 📅 Last Updated
**April 2026**

For project updates and team notes, refer to respective directory documentation.

---

**Happy developing! 🚀**

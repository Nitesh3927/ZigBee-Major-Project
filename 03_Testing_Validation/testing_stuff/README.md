# Testing & Validation Documentation

This folder contains all test data, logs, and validation results from the ZigBee V2V communication system.

## Directory Structure

### 📁 testing_stuff/

#### log_data_files/
**Raw test data collected from devices**

##### Accelerometer Tests:
- `acc_test_1.txt` - Accelerometer data collection test 1
- `acc_test_2.txt` - Accelerometer data collection test 2

**Contents**: X, Y, Z acceleration values, timestamps, processing status

##### Distance & Range Tests:
- `COM4_distance_test_1_aman.txt` - Distance test 1 (COM4)
- `COM4_distance_test_2_aman.txt` - Distance test 2 (COM4)
- `COM4_distance_test_far_aman.txt` - Long-distance transmission test
- `COM6_distance_test_1_aman.txt` - Distance test 1 (COM6)
- `COM6_distance_test_2_aman.txt` - Distance test 2 (COM6)

**Purpose**: Validate Zigbee communication range and signal strength

##### Static Position Tests:
- `COM4_static_test_90m.txt` - Static position at 90m distance
- `COM4_static_test_180m.txt` - Static position at 180m distance
- `COM4_static_test_270m.txt` - Static position at 270m distance
- `COM4_static_test_270m_bad.txt` - Static test with poor signal
- `COM4_static_test_300m.txt` - Static position at 300m distance

**Purpose**: Test system stability when devices are stationary

##### Other Logs:
- `COM4_dump.txt` - Raw data dump from COM4
- Other COM port captures as needed

#### log_processing/
**Scripts and tools for analyzing test data**

**Contains**:
- Python scripts for data parsing
- Log analysis and filtering tools
- Statistics calculation
- Data visualization generators

**Usage**:
```bash
python log_processing/analyze_logs.py log_data_files/COM4_distance_test_1_aman.txt
```

#### last_test/
**Latest test execution results**

- `plot1.py` - Plotting script for latest results
- `nitesh_ep/` - Endpoint-specific test data
- Generated graphs and analysis

#### Documentation/
**Test reports and methodology**

---

## Test Categories & Procedures

### 1. Accelerometer Tests
**Objective**: Validate MPU-6050 data collection and calibration

**Procedure**:
1. Deploy end device firmware on ESP32
2. Connect MPU-6050 sensor via I²C
3. Run acceleration data collection
4. Save raw sensor readings to log file
5. Verify data range and accuracy

**Expected Results**:
- Consistent data readings every sampling interval
- X, Y, Z values within expected range (±16g for default)
- Smooth transitions without extreme jumps
- Timestamp accuracy

**Analysis**:
- Check for sensor drift or calibration errors
- Identify noise in data
- Validate sampling frequency
- Compare with calibration standards

---

### 2. Distance Tests
**Objective**: Determine maximum communication range

**Procedure**:
1. Set up two devices with known distance between them
2. Run Zigbee transmitter on device 1
3. Run Zigbee receiver on device 2
4. Increase distance incrementally
5. Record signal strength (RSSI) and packet loss
6. Document maximum range achieved

**Test Distances**:
- Short range: 10-50m
- Medium range: 50-150m
- Long range: 150-300m
- Far distance: 300m+

**Expected Results**:
- Clear communication up to rated Zigbee range (100-300m)
- Signal degradation with increasing distance
- Acceptable packet loss rate (<5% in normal conditions)
- Rapid degradation beyond maximum range

**Analysis**:
- Plot signal strength vs. distance
- Calculate effective range
- Identify interference zones
- Document environmental factors (weather, obstacles)

---

### 3. Static Tests
**Objective**: Validate system reliability in stationary conditions

**Procedure**:
1. Position devices at fixed distance
2. Run for extended period (hours)
3. Collect periodic position and status updates
4. Monitor for packet loss or connectivity issues
5. Record environmental conditions

**Test Scenarios**:
- Indoor: Line-of-sight vs. obstacles
- Outdoor: Open area, near buildings, trees
- Variable weather: Clear, rain, snow

**Expected Results**:
- Stable position readings
- Consistent Zigbee connectivity
- Low packet loss rate
- Accurate GPS fixes (when available)

**Analysis**:
- Time-series plot of position data
- Connectivity uptime percentage
- Position accuracy distribution
- Environmental impact assessment

---

## Log File Format

### Standard Format:
```
TIMESTAMP: 2026-04-19 14:35:42.123
DEVICE_ID: 0x0042
SOURCE: GPS/Accelerometer/Zigbee
DATA: [values]
SIGNAL_STRENGTH: -75dBm
STATUS: SUCCESS/FAILED
```

### Example Accelerometer Log:
```
TIMESTAMP: 2026-04-19 14:35:42.123
DEVICE_ID: 0x0042
ACC_X: 0.234 g
ACC_Y: -0.145 g
ACC_Z: 1.023 g
TEMP: 28.5°C
```

### Example Range Test Log:
```
TIMESTAMP: 2026-04-19 14:35:42.123
TX_DEVICE: 0x0042
RX_DEVICE: 0x0043
DISTANCE: 150m
RSSI: -78dBm
PACKETS_SENT: 100
PACKETS_RECEIVED: 98
LOSS_RATE: 2%
```

---

## Data Processing Workflow

### Step 1: Collection
- Run firmware on devices
- Capture serial output to files
- Organize by test type and date

### Step 2: Parsing
```python
# Parse log files
import log_processing.parse_logs as parser
data = parser.parse_distance_test('COM4_distance_test_1_aman.txt')
```

### Step 3: Analysis
- Calculate statistics (mean, std dev, min, max)
- Detect anomalies or outliers
- Compare against baselines
- Generate reports

### Step 4: Visualization
```python
# Generate plots
import plot1
plot1.generate_distance_plot(data)
plot1.generate_signal_strength_plot(data)
```

### Step 5: Documentation
- Record findings in test reports
- Document environmental conditions
- Update performance baselines
- Recommend optimizations

---

## Test Results Checklist

For each test, verify:

### Performance Metrics:
- [ ] Communication range: _____ m
- [ ] Signal strength at max range: _____ dBm
- [ ] Packet loss rate: _____ %
- [ ] GPS accuracy: _____ m
- [ ] Acceleration sampling rate: _____ Hz
- [ ] System uptime: _____ %

### Environmental Factors:
- [ ] Temperature: _____ °C
- [ ] Weather conditions: _____
- [ ] Obstacles/interference: _____
- [ ] Antenna orientation: _____

### Issues Found:
- [ ] Communication failures at distance > _____ m
- [ ] Intermittent GPS fixes
- [ ] Acceleration sensor drift
- [ ] Zigbee packet corruption
- [ ] Other: _____

### Recommendations:
- [ ] Firmware optimization needed
- [ ] Antenna repositioning recommended
- [ ] Environmental testing expansion
- [ ] Parameter tuning required

---

## Troubleshooting Tests

If tests fail:

1. **Check Hardware**:
   - Verify device power supply
   - Test serial connections
   - Validate sensor connections

2. **Review Logs**:
   - Look for error messages
   - Check for missing data
   - Identify timing issues

3. **Validate Firmware**:
   - Recompile and reflash
   - Check serial communication
   - Monitor device output

4. **Repeat Test**:
   - Change test conditions
   - Modify parameters
   - Document differences

---

## Test Schedule

### Phase 1: Unit Tests (Week 1)
- Accelerometer data collection
- GPS module communication
- Zigbee transmit/receive

### Phase 2: Integration Tests (Week 2)
- Multi-device communication
- Data fusion (GPS + acceleration)
- End-to-end packet processing

### Phase 3: Range Tests (Week 3)
- Distance testing at various intervals
- Signal strength measurement
- Range limitation documentation

### Phase 4: Field Tests (Week 4)
- Real-world vehicle testing
- Weather condition testing
- Urban/rural environments

### Phase 5: Validation (Week 5)
- Performance benchmarking
- Safety validation
- System reliability certification

---

## Generated Reports

Location: `03_Testing_Validation/last_test/`

- `distance_analysis_report.txt` - Range test findings
- `acceleration_calibration_report.txt` - Sensor validation
- `communication_reliability_report.txt` - Zigbee network performance
- `summary_report.txt` - Overall system assessment

---

## Key Metrics to Track

| Metric | Target | Current |
|--------|--------|---------|
| Max Communication Range | >200m | _____ |
| Signal Strength @ 100m | >-85dBm | _____ |
| Packet Loss Rate | <5% | _____ |
| GPS Accuracy | <10m | _____ |
| System Uptime | >99% | _____ |
| Acceleration Resolution | 0.01g | _____ |

---

## Next Steps

1. **Run Tests**: Execute test procedures for your specific use case
2. **Collect Data**: Save logs with descriptive names and timestamps
3. **Process Results**: Use provided Python scripts for analysis
4. **Document Findings**: Record metrics and observations
5. **Optimize**: Adjust parameters based on results
6. **Iterate**: Repeat tests to validate improvements

---

For detailed development information, refer to `PROJECT_DEVELOPMENT_GUIDE.md`

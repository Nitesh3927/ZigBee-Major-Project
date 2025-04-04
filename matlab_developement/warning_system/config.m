    %% === MPU6050 Initialization and Model Parameters ===

% I2C Address (Default: 0x68)
MPU6050_ADDR = '0x68';

% Simulation Time Step (For Discrete Models)
Ts = 0.01; % 10ms sample time

%% Configuration Options 

%% ⚡ Accelerometer Range (Sensitivity Setting)
% Determines the range of acceleration values the sensor can measure.
% Options:
% '±2g'  → Highest sensitivity (smallest range)  → Scale factor: 16384
% '±4g'  → Moderate sensitivity  → Scale factor: 8192
% '±8g'  → Lower sensitivity  → Scale factor: 4096
% '±16g' → Lowest sensitivity (largest range)  → Scale factor: 2048

%% ⚙️ Gyroscope Enable/Disable
% If true → Gyroscope is active and will return angular velocity data.
% If false → Gyroscope is disabled (saves power & reduces data processing).

%% 🔁 Digital Low-Pass Filter (DLPF)
% Filters out high-frequency noise from sensor readings.
% Options:
% 0 → 260Hz bandwidth, 0ms delay (No filtering)
% 1 → 184Hz bandwidth, 2.0ms delay
% 2 → 94Hz bandwidth, 3.0ms delay
% 3 → 44Hz bandwidth, 4.9ms delay
% 4 → 21Hz bandwidth, 8.5ms delay
% 5 → 10Hz bandwidth, 13.8ms delay
% 6 → 5Hz bandwidth, 19.0ms delay (Strongest filtering, smoothest data)

%% ⏱️ Sample Rate Divider (SMPLRT_DIV)
% Determines the output data rate (ODR) based on the internal clock.
% Formula: Sample Rate = Gyro Output Rate / (1 + SMPLRT_DIV)
% - Gyro Output Rate:
%   - 8kHz if DLPF is disabled (0x00)
%   - 1kHz if DLPF is enabled (0x01 to 0x06)
% Example values:
% 0  → 1kHz  (Default if DLPF enabled)
% 7  → 125Hz (1kHz / (1+7))
% 19 → 50Hz (1kHz / (1+19))
% 39 → 25Hz (1kHz / (1+39))

%% ==================== MPU6050 Configuration ====================

% ⚡ Accelerometer Range (Sensitivity Setting)
ACCEL_RANGE = Simulink.Parameter;
ACCEL_RANGE.Value = 4;  % Numeric value, e.g., 2, 4, 8, 16 (corresponding to ±2g, ±4g, etc.)
ACCEL_RANGE.DataType = 'uint8';
ACCEL_RANGE.StorageClass = 'ExportedGlobal';

% ⚙️ Gyroscope Enable/Disable
ENABLE_GYRO = Simulink.Parameter;
ENABLE_GYRO.Value = false; % false = Disabled, true = Enabled
ENABLE_GYRO.DataType = 'boolean';
ENABLE_GYRO.StorageClass = 'ExportedGlobal';

% 🔁 Digital Low-Pass Filter (DLPF)
DLPF_SETTING = Simulink.Parameter;
DLPF_SETTING.Value = 6; % Options: 0-6 (Lower value = less filtering)
DLPF_SETTING.DataType = 'uint8';
DLPF_SETTING.StorageClass = 'ExportedGlobal';

% ⏱️ Sample Rate Divider (SMPLRT_DIV)
SAMPLE_RATE_DIV = Simulink.Parameter;
SAMPLE_RATE_DIV.Value = 7; % Defines output data rate
SAMPLE_RATE_DIV.DataType = 'uint8';
SAMPLE_RATE_DIV.StorageClass = 'ExportedGlobal';

%% ==================== Assign Variables to Workspace ====================
% This ensures that Simulink can access the variables.

assignin('base', 'ACCEL_RANGE', ACCEL_RANGE);
assignin('base', 'ENABLE_GYRO', ENABLE_GYRO);
assignin('base', 'DLPF_SETTING', DLPF_SETTING);
assignin('base', 'SAMPLE_RATE_DIV', SAMPLE_RATE_DIV);


disp('📢 MPU6050 Configuration Parameters Loaded.');

%% ==================== TIME STEP SETUP ====================
MPU_TS = 0.1;
GPS_TS = 0.5;
MODEL_TS = 0.1;
READER_TS = 0.5;
CORE_TS = 0.1;

disp('📢 TIME STEPS LOADED.');
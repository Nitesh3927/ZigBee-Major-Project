% ================= GPS Configuration for Simulink =================

% Sampling Rate (Update Rate in Hz)
gps_update_rate = Simulink.Parameter;
gps_update_rate.Value = 1;  % Default 1Hz
gps_update_rate.DataType = 'double';
gps_update_rate.CoderInfo.StorageClass = 'ExportedGlobal';

% Baud Rate (bps)
gps_baud_rate = Simulink.Parameter;
gps_baud_rate.Value = 9600;  % Default baud rate
gps_baud_rate.DataType = 'double';
gps_baud_rate.CoderInfo.StorageClass = 'ExportedGlobal';

% GPS Dynamic Mode (Airborne, Pedestrian, Automotive, etc.)
gps_dynamic_mode = Simulink.Parameter;
gps_dynamic_mode.Value = 2;  % 2 = Stationary, 3 = Pedestrian, 4 = Automotive
gps_dynamic_mode.DataType = 'double';
gps_dynamic_mode.CoderInfo.StorageClass = 'ExportedGlobal';

% ================= UBX Command Storage =================

% UBX Command for Update Rate 1Hz
ubx_update_rate_1Hz = uint8([181, 98, 6, 8, 6, 0, 232, 3, 1, 0, 0, 0, 1, 57]);

% UBX Command for Update Rate 2Hz
ubx_update_rate_2Hz = uint8([181, 98, 6, 8, 6, 0, 244, 1, 1, 0, 0, 0, 14, 121]);

% UBX Command for Update Rate 3Hz
ubx_update_rate_3Hz = uint8([181, 98, 6, 8, 6, 0, 160, 1, 1, 0, 0, 0, 74, 34]);

% UBX Command for Update Rate 4Hz
ubx_update_rate_4Hz = uint8([181, 98, 6, 8, 6, 0, 128, 1, 1, 0, 0, 0, 106, 14]);

% UBX Command for Update Rate 5Hz
ubx_update_rate_5Hz = uint8([181, 98, 6, 8, 6, 0, 200, 0, 1, 0, 0, 0, 222, 106]);

% UBX Command for Baud Rate Change to 38400
ubx_baud_rate_38400 = uint8([181, 98, 6, 0, 20, 0, 1, 0, 0, 0, 128, 9, 0, 0, 0, 192, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 199, 92]);

% UBX Command for Baud Rate Change to 57600
ubx_baud_rate_57600 = uint8([181, 98, 6, 0, 20, 0, 1, 0, 0, 0, 224, 14, 0, 0, 0, 192, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 17, 179]);

% UBX Command for Baud Rate Change to 115200
ubx_baud_rate_115200 = uint8([181, 98, 6, 0, 20, 0, 1, 0, 0, 0, 208, 7, 0, 0, 0, 192, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 231, 77]);

% UBX Command for Dynamic Mode - Automotive
ubx_dynamic_mode_automotive = uint8([181, 98, 6, 24, 24, 0, 255, 255, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 189, 81]);

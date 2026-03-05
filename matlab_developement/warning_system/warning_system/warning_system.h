/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: warning_system.h
 *
 * Code generated for Simulink model 'warning_system'.
 *
 * Model version                  : 1.950
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Oct 31 20:08:55 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef warning_system_h_
#define warning_system_h_
#ifndef warning_system_COMMON_INCLUDES_
#define warning_system_COMMON_INCLUDES_
#include <stdio.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#include "GPS_Parser.h"
#include "MW_I2C.h"
#endif                                 /* warning_system_COMMON_INCLUDES_ */

#include "warning_system_types.h"
#include "core_logic.h"
#include "output_transmitter.h"
#include "input_transmitter.h"
#include "input_mpu6050.h"
#include "half_type.h"
#include "rt_nonfinite.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  char_T str[130];
  uint8_T dataIn[130];
  VSP SignalConversion_BusCreator1_m;  /* '<S5>/Signal Conversion' */
  accel SignalConversion_BusCreator1;  /* '<Root>/Signal Conversion' */
  accel delta;                         /* '<Root>/core_logic' */
  accel acc_offset;                    /* '<Root>/core_logic' */
  accel acc_calibrated;                /* '<Root>/core_logic' */
  char_T validatedHoleFilling_f1_data[18];
  char_T b_varargin_1_data[18];
  char_T varargin_1_data[17];
  real_T VEHICLE_STATUS;               /* '<Root>/core_logic' */
  real_T gyro_x;
  real_T gyro_y;
  real_T gyro_z;
  real_T d;
  int32_T nbytes;
  int32_T vehicle_status;
  int32_T loop_ub;
  int32_T loop_ub_tmp;
  int32_T newNumel;
  int32_T i;
  int32_T i_c;
  uint8_T transmit;                    /* '<Root>/core_logic' */
  boolean_T reciving_flag;             /* '<S5>/Cast To Boolean' */
  boolean_T b;
  ITC_status rtb_writing_flag_k;
  B_core_logic_warning_system_T sf_core_logic;/* '<Root>/core_logic' */
} B_warning_system_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_internal_arduino_SerialWr_T obj;/* '<S1>/Serial Transmit' */
  GPS_Parser_warning_system_T obj_f;   /* '<Root>/input_gps' */
  DW_output_transmitter_warning_system_T output_transmitter;/* '<Root>/output_transmitter' */
  DW_input_transmitter_warning_system_T input_transmitter;/* '<Root>/input_transmitter' */
  DW_input_mpu6050_warning_system_T sf_input_mpu6050;/* '<Root>/input_mpu6050' */
  DW_core_logic_warning_system_T sf_core_logic;/* '<Root>/core_logic' */
} DW_warning_system_T;

/* Parameters (default storage) */
struct P_warning_system_T_ {
  real_T THRESHOLD_CAUTION;            /* Variable: THRESHOLD_CAUTION
                                        * Referenced by: '<Root>/core_logic'
                                        */
  real_T THRESHOLD_CRASHED;            /* Variable: THRESHOLD_CRASHED
                                        * Referenced by: '<Root>/core_logic'
                                        */
  real_T THRESHOLD_LANE_CHANGE;        /* Variable: THRESHOLD_LANE_CHANGE
                                        * Referenced by: '<Root>/core_logic'
                                        */
  real_T THRESHOLD_REST;               /* Variable: THRESHOLD_REST
                                        * Referenced by: '<Root>/core_logic'
                                        */
  real_T TS_GPS;                       /* Variable: TS_GPS
                                        * Referenced by: '<Root>/input_gps'
                                        */
  real16_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<Root>/Constant1'
                                        */
  P_output_transmitter_warning_system_T output_transmitter;/* '<Root>/output_transmitter' */
  P_input_transmitter_warning_system_T input_transmitter;/* '<Root>/input_transmitter' */
  P_input_mpu6050_warning_system_T sf_input_mpu6050;/* '<Root>/input_mpu6050' */
  P_core_logic_warning_system_T sf_core_logic;/* '<Root>/core_logic' */
};

/* Real-time Model Data Structure */
struct tag_RTM_warning_system_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (default storage) */
extern P_warning_system_T warning_system_P;

/* Block signals (default storage) */
extern B_warning_system_T warning_system_B;

/* Block states (default storage) */
extern DW_warning_system_T warning_system_DW;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern uint16_T GYRO_RANGE;            /* Variable: GYRO_RANGE
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
extern boolean_T ENABLE_GYRO;          /* Variable: ENABLE_GYRO
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
extern uint8_T ACCEL_RANGE;            /* Variable: ACCEL_RANGE
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
extern uint8_T DLPF_SETTING;           /* Variable: DLPF_SETTING
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */

/* Model entry point functions */
extern void warning_system_initialize(void);
extern void warning_system_step(void);
extern void warning_system_terminate(void);

/* Real-time Model object */
extern RT_MODEL_warning_system_T *const warning_system_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Display1' : Unused code path elimination
 * Block '<S2>/Display2' : Unused code path elimination
 * Block '<S2>/Display22' : Unused code path elimination
 * Block '<S2>/Display23' : Unused code path elimination
 * Block '<S2>/Display24' : Unused code path elimination
 * Block '<S2>/Display3' : Unused code path elimination
 * Block '<S2>/Display4' : Unused code path elimination
 * Block '<S2>/Display5' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'warning_system'
 * '<S1>'   : 'warning_system/ serial_printing'
 * '<S2>'   : 'warning_system/OBSERVATION'
 * '<S3>'   : 'warning_system/core_logic'
 * '<S4>'   : 'warning_system/input_mpu6050'
 * '<S5>'   : 'warning_system/input_transmitter'
 * '<S6>'   : 'warning_system/output_transmitter'
 * '<S7>'   : 'warning_system/ serial_printing/MATLAB Function'
 * '<S8>'   : 'warning_system/core_logic/calibrate'
 * '<S9>'   : 'warning_system/core_logic/check_jerk'
 * '<S10>'  : 'warning_system/core_logic/check_jerk/Difference'
 * '<S11>'  : 'warning_system/core_logic/check_jerk/Difference1'
 * '<S12>'  : 'warning_system/core_logic/check_jerk/Difference2'
 * '<S13>'  : 'warning_system/input_mpu6050/i2cRd'
 * '<S14>'  : 'warning_system/input_mpu6050/i2cWr'
 * '<S15>'  : 'warning_system/input_transmitter/MATLAB Function'
 * '<S16>'  : 'warning_system/output_transmitter/MATLAB Function'
 */
#endif                                 /* warning_system_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

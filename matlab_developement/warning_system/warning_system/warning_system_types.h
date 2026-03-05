/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: warning_system_types.h
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

#ifndef warning_system_types_h_
#define warning_system_types_h_
#include "rtwtypes.h"
#include "MW_SVD.h"
#ifndef DEFINED_TYPEDEF_FOR_accel_
#define DEFINED_TYPEDEF_FOR_accel_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} accel;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Vehicle_Status_
#define DEFINED_TYPEDEF_FOR_Vehicle_Status_

typedef uint8_T Vehicle_Status;

/* enum Vehicle_Status */
#define INVALID                        ((Vehicle_Status)0U)      /* Default value */
#define NORMAL                         ((Vehicle_Status)4U)
#define LANE_CHANGE_RIGHT              ((Vehicle_Status)8U)
#define LANE_CHANGE_LEFT               ((Vehicle_Status)16U)
#define NEARBY_CRASH                   ((Vehicle_Status)32U)
#define CAUTION                        ((Vehicle_Status)100U)
#define CRASH                          ((Vehicle_Status)128U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_VSP_
#define DEFINED_TYPEDEF_FOR_VSP_

typedef struct {
  real_T lat;
  real_T lng;
  real_T speed;
  uint16_T address;
  Vehicle_Status status;
} VSP;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ITC_status_
#define DEFINED_TYPEDEF_FOR_ITC_status_

typedef uint8_T ITC_status;

/* enum ITC_status */
#define SUCCESS                        ((ITC_status)0U)
#define OCCUPIED                       ((ITC_status)1U)
#define ARBITRATION_LOST               ((ITC_status)2U)
#define NO_ACKNOWLEDGE                 ((ITC_status)4U)          /* Default value */
#define BUS_ERROR                      ((ITC_status)8U)
#define BUS_NOT_IN_USE                 ((ITC_status)16U)
#endif

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_warning_system_T
#define typedef_cell_wrap_warning_system_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_warning_system_T;

#endif                                 /* typedef_cell_wrap_warning_system_T */

#ifndef struct_tag_JWcuUSYp0PvSKTyOAPxz7G
#define struct_tag_JWcuUSYp0PvSKTyOAPxz7G

struct tag_JWcuUSYp0PvSKTyOAPxz7G
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_warning_system_T inputVarSize;
  int32_T NumChannels;
  int32_T FrameLength;
  real_T pCumSum;
  real_T pCumSumRev[3];
  real_T pCumRevIndex;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_JWcuUSYp0PvSKTyOAPxz7G */

#ifndef typedef_dsp_simulink_MovingAverage_warning_system_T
#define typedef_dsp_simulink_MovingAverage_warning_system_T

typedef struct tag_JWcuUSYp0PvSKTyOAPxz7G
  dsp_simulink_MovingAverage_warning_system_T;

#endif                 /* typedef_dsp_simulink_MovingAverage_warning_system_T */

/* Custom Type definition for MATLABSystem: '<S14>/Ecriture I2C' */
#include "MW_SVD.h"
#ifndef struct_tag_BczSCX0m9Gp7rApo3jZAxG
#define struct_tag_BczSCX0m9Gp7rApo3jZAxG

struct tag_BczSCX0m9Gp7rApo3jZAxG
{
  MW_Handle_Type MW_I2C_HANDLE;
};

#endif                                 /* struct_tag_BczSCX0m9Gp7rApo3jZAxG */

#ifndef typedef_c_arduinodriver_ArduinoI2C_warning_system_T
#define typedef_c_arduinodriver_ArduinoI2C_warning_system_T

typedef struct tag_BczSCX0m9Gp7rApo3jZAxG
  c_arduinodriver_ArduinoI2C_warning_system_T;

#endif                 /* typedef_c_arduinodriver_ArduinoI2C_warning_system_T */

#ifndef struct_tag_kHIoPIOtGLhFJAEYiu4mFB
#define struct_tag_kHIoPIOtGLhFJAEYiu4mFB

struct tag_kHIoPIOtGLhFJAEYiu4mFB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_warning_system_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
};

#endif                                 /* struct_tag_kHIoPIOtGLhFJAEYiu4mFB */

#ifndef typedef_codertarget_arduinobase_internal_arduinoI2CWrite__T
#define typedef_codertarget_arduinobase_internal_arduinoI2CWrite__T

typedef struct tag_kHIoPIOtGLhFJAEYiu4mFB
  codertarget_arduinobase_internal_arduinoI2CWrite__T;

#endif         /* typedef_codertarget_arduinobase_internal_arduinoI2CWrite__T */

#ifndef struct_tag_NY00b9HBulK1thgQUijEwC
#define struct_tag_NY00b9HBulK1thgQUijEwC

struct tag_NY00b9HBulK1thgQUijEwC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_warning_system_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
};

#endif                                 /* struct_tag_NY00b9HBulK1thgQUijEwC */

#ifndef typedef_codertarget_arduinobase_internal_arduinoI2CRead_w_T
#define typedef_codertarget_arduinobase_internal_arduinoI2CRead_w_T

typedef struct tag_NY00b9HBulK1thgQUijEwC
  codertarget_arduinobase_internal_arduinoI2CRead_w_T;

#endif         /* typedef_codertarget_arduinobase_internal_arduinoI2CRead_w_T */

#ifndef struct_tag_toi4g1nosdSlS6VWrT6XNG
#define struct_tag_toi4g1nosdSlS6VWrT6XNG

struct tag_toi4g1nosdSlS6VWrT6XNG
{
  int32_T __dummy;
};

#endif                                 /* struct_tag_toi4g1nosdSlS6VWrT6XNG */

#ifndef typedef_c_arduinodriver_ArduinoSerial_warning_system_T
#define typedef_c_arduinodriver_ArduinoSerial_warning_system_T

typedef struct tag_toi4g1nosdSlS6VWrT6XNG
  c_arduinodriver_ArduinoSerial_warning_system_T;

#endif              /* typedef_c_arduinodriver_ArduinoSerial_warning_system_T */

#ifndef struct_tag_BH6tQyJGRpfzwbONQYwL2E
#define struct_tag_BH6tQyJGRpfzwbONQYwL2E

struct tag_BH6tQyJGRpfzwbONQYwL2E
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T port;
  real_T dataSizeInBytes;
  real_T dataType;
  real_T sendModeEnum;
  real_T sendFormatEnum;
  c_arduinodriver_ArduinoSerial_warning_system_T SerialDriverObj;
};

#endif                                 /* struct_tag_BH6tQyJGRpfzwbONQYwL2E */

#ifndef typedef_codertarget_arduinobase_internal_arduino_SerialWr_T
#define typedef_codertarget_arduinobase_internal_arduino_SerialWr_T

typedef struct tag_BH6tQyJGRpfzwbONQYwL2E
  codertarget_arduinobase_internal_arduino_SerialWr_T;

#endif         /* typedef_codertarget_arduinobase_internal_arduino_SerialWr_T */

#ifndef struct_tag_3hqHXjfW3HdRnUSlmqEUmC
#define struct_tag_3hqHXjfW3HdRnUSlmqEUmC

struct tag_3hqHXjfW3HdRnUSlmqEUmC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T SampleTime;
};

#endif                                 /* struct_tag_3hqHXjfW3HdRnUSlmqEUmC */

#ifndef typedef_GPS_Parser_warning_system_T
#define typedef_GPS_Parser_warning_system_T

typedef struct tag_3hqHXjfW3HdRnUSlmqEUmC GPS_Parser_warning_system_T;

#endif                                 /* typedef_GPS_Parser_warning_system_T */

#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T

struct emxArray_char_T
{
  char_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /* struct_emxArray_char_T */

#ifndef typedef_emxArray_char_T_warning_system_T
#define typedef_emxArray_char_T_warning_system_T

typedef struct emxArray_char_T emxArray_char_T_warning_system_T;

#endif                            /* typedef_emxArray_char_T_warning_system_T */

/* Parameters for system: '<Root>/core_logic' */
typedef struct P_core_logic_warning_system_T_ P_core_logic_warning_system_T;

/* Parameters for system: '<Root>/input_mpu6050' */
typedef struct P_input_mpu6050_warning_system_T_
  P_input_mpu6050_warning_system_T;

/* Parameters for system: '<Root>/input_transmitter' */
typedef struct P_input_transmitter_warning_system_T_
  P_input_transmitter_warning_system_T;

/* Parameters for system: '<Root>/output_transmitter' */
typedef struct P_output_transmitter_warning_system_T_
  P_output_transmitter_warning_system_T;

/* Parameters (default storage) */
typedef struct P_warning_system_T_ P_warning_system_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_warning_system_T RT_MODEL_warning_system_T;

#endif                                 /* warning_system_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

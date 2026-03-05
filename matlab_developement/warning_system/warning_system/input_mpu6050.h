/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_mpu6050.h
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

#ifndef input_mpu6050_h_
#define input_mpu6050_h_
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

/* Block states (default storage) for system '<S4>/i2cWr' */
typedef struct {
  codertarget_arduinobase_internal_arduinoI2CWrite__T obj;/* '<S14>/Ecriture I2C' */
} DW_i2cWr_warning_system_T;

/* Block states (default storage) for system '<Root>/input_mpu6050' */
typedef struct {
  codertarget_arduinobase_internal_arduinoI2CRead_w_T obj;/* '<S13>/I2C Read' */
  real_T gyro_scale_factor;            /* '<Root>/input_mpu6050' */
  real_T acc_scale_factor;             /* '<Root>/input_mpu6050' */
  int32_T val_sizes;                   /* '<Root>/input_mpu6050' */
  uint8_T is_active_c1_warning_system; /* '<Root>/input_mpu6050' */
  uint8_T is_c1_warning_system;        /* '<Root>/input_mpu6050' */
  DW_i2cWr_warning_system_T i2cWr;     /* '<S4>/i2cWr' */
} DW_input_mpu6050_warning_system_T;

/* Parameters for system: '<Root>/input_mpu6050' */
struct P_input_mpu6050_warning_system_T_ {
  int16_T datar_Y0;                    /* Computed Parameter: datar_Y0
                                        * Referenced by: '<S13>/datar'
                                        */
};

extern void warning_system_i2cWr_Init(DW_i2cWr_warning_system_T *localDW);
extern void warning_system_i2cWr(uint16_T rtu_dataw, DW_i2cWr_warning_system_T
  *localDW);
extern void warning_system_input_mpu6050_Init(real_T *rty_acc_x, real_T
  *rty_acc_z, real_T *rty_acc_y, real_T *rty_gyro_x, real_T *rty_gyro_y, real_T *
  rty_gyro_z, DW_input_mpu6050_warning_system_T *localDW);
extern void warning_system_input_mpu6050(real_T *rty_acc_x, real_T *rty_acc_z,
  real_T *rty_acc_y, real_T *rty_gyro_x, real_T *rty_gyro_y, real_T *rty_gyro_z,
  DW_input_mpu6050_warning_system_T *localDW);
extern void warning_system_i2cWr_Term(DW_i2cWr_warning_system_T *localDW);
extern void warning_system_input_mpu6050_Term(DW_input_mpu6050_warning_system_T *
  localDW);

#endif                                 /* input_mpu6050_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

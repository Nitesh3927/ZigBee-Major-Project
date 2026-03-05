/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: output_transmitter.h
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

#ifndef output_transmitter_h_
#define output_transmitter_h_
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
#include "half_type.h"

/* Block states (default storage) for system '<Root>/output_transmitter' */
typedef struct {
  codertarget_arduinobase_internal_arduinoI2CWrite__T obj;/* '<S6>/I2C Write' */
  boolean_T output_transmitter_MODE;   /* '<Root>/output_transmitter' */
} DW_output_transmitter_warning_system_T;

/* Parameters for system: '<Root>/output_transmitter' */
struct P_output_transmitter_warning_system_T_ {
  ITC_status Status_Y0;                /* Computed Parameter: Status_Y0
                                        * Referenced by: '<S6>/Status'
                                        */
};

extern void warning_system_output_transmitter_Init(ITC_status *rty_Status,
  DW_output_transmitter_warning_system_T *localDW,
  P_output_transmitter_warning_system_T *localP);
extern void warning_system_output_transmitter_Disable
  (DW_output_transmitter_warning_system_T *localDW);
extern void warning_system_output_transmitter(RT_MODEL_warning_system_T * const
  warning_system_M, boolean_T rtu_Enable, real_T rtu_local_gps, real_T
  rtu_local_gps_g, real_T rtu_local_gps_p, real_T rtu_status, real16_T
  rtu_zigbeeAddress, ITC_status *rty_Status,
  DW_output_transmitter_warning_system_T *localDW);
extern void warning_system_output_transmitter_Term
  (DW_output_transmitter_warning_system_T *localDW);

#endif                                 /* output_transmitter_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

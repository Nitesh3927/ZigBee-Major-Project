/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_transmitter.h
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

#ifndef input_transmitter_h_
#define input_transmitter_h_
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

/* Block states (default storage) for system '<Root>/input_transmitter' */
typedef struct {
  codertarget_arduinobase_internal_arduinoI2CRead_w_T obj;/* '<S5>/I2C Read' */
  uint8_T UnitDelay_DSTATE[15];        /* '<S5>/Unit Delay' */
} DW_input_transmitter_warning_system_T;

/* Parameters for system: '<Root>/input_transmitter' */
struct P_input_transmitter_warning_system_T_ {
  real_T Constant1_Value[3];           /* Expression: [8 32 128]
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S5>/Constant'
                                        */
  uint8_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S5>/Unit Delay'
                                */
};

extern void warning_system_input_transmitter_Init
  (DW_input_transmitter_warning_system_T *localDW,
   P_input_transmitter_warning_system_T *localP);
extern void warning_system_input_transmitter(VSP *rty_FOREIGN_GPS, boolean_T
  *rty_Status, DW_input_transmitter_warning_system_T *localDW,
  P_input_transmitter_warning_system_T *localP);
extern void warning_system_input_transmitter_Term
  (DW_input_transmitter_warning_system_T *localDW);

#endif                                 /* input_transmitter_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

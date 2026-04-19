/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: warning_system_data.c
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

#include "warning_system.h"

/* Block parameters (default storage) */
P_warning_system_T warning_system_P = {
  /* Variable: THRESHOLD_CAUTION
   * Referenced by: '<Root>/core_logic'
   */
  0.6,

  /* Variable: THRESHOLD_CRASHED
   * Referenced by: '<Root>/core_logic'
   */
  0.8,

  /* Variable: THRESHOLD_LANE_CHANGE
   * Referenced by: '<Root>/core_logic'
   */
  0.2,

  /* Variable: THRESHOLD_REST
   * Referenced by: '<Root>/core_logic'
   */
  0.2,

  /* Variable: TS_GPS
   * Referenced by: '<Root>/input_gps'
   */
  0.05,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<Root>/Constant1'
   */
  { 0U },

  /* Start of '<Root>/output_transmitter' */
  {
    /* Computed Parameter: Status_Y0
     * Referenced by: '<S6>/Status'
     */
    NO_ACKNOWLEDGE
  }
  ,

  /* End of '<Root>/output_transmitter' */

  /* Start of '<Root>/input_transmitter' */
  {
    /* Expression: [8 32 128]
     * Referenced by: '<S5>/Constant1'
     */
    { 8.0, 32.0, 128.0 },

    /* Expression: 0
     * Referenced by: '<S5>/Constant'
     */
    0.0,

    /* Computed Parameter: UnitDelay_InitialCondition
     * Referenced by: '<S5>/Unit Delay'
     */
    0U
  }
  ,

  /* End of '<Root>/input_transmitter' */

  /* Start of '<Root>/input_mpu6050' */
  {
    /* Computed Parameter: datar_Y0
     * Referenced by: '<S13>/datar'
     */
    0
  }
  ,

  /* End of '<Root>/input_mpu6050' */

  /* Start of '<Root>/core_logic' */
  {
    /* Mask Parameter: Difference_ICPrevInput
     * Referenced by: '<S10>/UD'
     */
    0.0,

    /* Mask Parameter: Difference1_ICPrevInput
     * Referenced by: '<S11>/UD'
     */
    0.0,

    /* Mask Parameter: Difference2_ICPrevInput
     * Referenced by: '<S12>/UD'
     */
    0.0,

    /* Computed Parameter: delta_Y0
     * Referenced by: '<S9>/delta'
     */
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },

    /* Computed Parameter: offset_Y0
     * Referenced by: '<S8>/offset'
     */
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },

    /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
     * Referenced by: '<Root>/core_logic'
     */
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },

    /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
     * Referenced by: '<Root>/core_logic'
     */
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },

    /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
     * Referenced by: '<Root>/core_logic'
     */
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },

    /* Expression: 0.0
     * Referenced by: '<S9>/Delay'
     */
    0.0,

    /* Expression: 0.1
     * Referenced by: '<S9>/Quantizer'
     */
    0.1,

    /* Expression: 0.0
     * Referenced by: '<S9>/Delay1'
     */
    0.0,

    /* Expression: 0.1
     * Referenced by: '<S9>/Quantizer1'
     */
    0.1,

    /* Expression: 0.0
     * Referenced by: '<S9>/Delay2'
     */
    0.0,

    /* Expression: 0.1
     * Referenced by: '<S9>/Quantizer2'
     */
    0.1
  }
  /* End of '<Root>/core_logic' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

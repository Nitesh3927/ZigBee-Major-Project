/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: core_logic.h
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

#ifndef core_logic_h_
#define core_logic_h_
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

/* Block signals for system '<S8>/Moving Average' */
typedef struct {
  real_T X;                            /* '<S8>/Moving Average' */
} B_MovingAverage_warning_system_T;

/* Block states (default storage) for system '<S8>/Moving Average' */
typedef struct {
  dsp_simulink_MovingAverage_warning_system_T obj;/* '<S8>/Moving Average' */
  boolean_T objisempty;                /* '<S8>/Moving Average' */
} DW_MovingAverage_warning_system_T;

/* Block signals for system '<Root>/core_logic' */
typedef struct {
  accel SignalConversion_BusCreator1;  /* '<S8>/Signal Conversion' */
  accel SignalConversion1_BusCreator1; /* '<S9>/Signal Conversion1' */
  B_MovingAverage_warning_system_T MovingAverage2;/* '<S8>/Moving Average' */
  B_MovingAverage_warning_system_T MovingAverage1;/* '<S8>/Moving Average' */
  B_MovingAverage_warning_system_T MovingAverage;/* '<S8>/Moving Average' */
} B_core_logic_warning_system_T;

/* Block states (default storage) for system '<Root>/core_logic' */
typedef struct {
  real_T Delay_DSTATE[2];              /* '<S9>/Delay' */
  real_T UD_DSTATE;                    /* '<S10>/UD' */
  real_T Delay1_DSTATE[2];             /* '<S9>/Delay1' */
  real_T UD_DSTATE_c;                  /* '<S11>/UD' */
  real_T Delay2_DSTATE[2];             /* '<S9>/Delay2' */
  real_T UD_DSTATE_a;                  /* '<S12>/UD' */
  uint32_T temporalCounter_i1;         /* '<Root>/core_logic' */
  uint8_T COUNT_CALIBRATION;           /* '<Root>/core_logic' */
  uint8_T COUNT_CRASHED;               /* '<Root>/core_logic' */
  uint8_T COUNT_NEARBY_CRASHED;        /* '<Root>/core_logic' */
  uint8_T COUNT_CAUTION;               /* '<Root>/core_logic' */
  uint8_T is_active_c6_warning_system; /* '<Root>/core_logic' */
  uint8_T is_c6_warning_system;        /* '<Root>/core_logic' */
  uint8_T tp_CAUTION;                  /* '<Root>/core_logic' */
  uint8_T tp_CRASHED;                  /* '<Root>/core_logic' */
  uint8_T tp_Init;                     /* '<Root>/core_logic' */
  uint8_T tp_NEARBY_CRASH;             /* '<Root>/core_logic' */
  uint8_T tp_NORMAL;                   /* '<Root>/core_logic' */
  uint8_T tp_caliberation;             /* '<Root>/core_logic' */
  uint8_T tp_mpu_running;              /* '<Root>/core_logic' */
  uint8_T is_mpu_running;              /* '<Root>/core_logic' */
  uint8_T tp_delta_computation;        /* '<Root>/core_logic' */
  uint8_T tp_extracting_acc;           /* '<Root>/core_logic' */
  DW_MovingAverage_warning_system_T MovingAverage2;/* '<S8>/Moving Average' */
  DW_MovingAverage_warning_system_T MovingAverage1;/* '<S8>/Moving Average' */
  DW_MovingAverage_warning_system_T MovingAverage;/* '<S8>/Moving Average' */
} DW_core_logic_warning_system_T;

/* Parameters for system: '<Root>/core_logic' */
struct P_core_logic_warning_system_T_ {
  real_T Difference_ICPrevInput;       /* Mask Parameter: Difference_ICPrevInput
                                        * Referenced by: '<S10>/UD'
                                        */
  real_T Difference1_ICPrevInput;     /* Mask Parameter: Difference1_ICPrevInput
                                       * Referenced by: '<S11>/UD'
                                       */
  real_T Difference2_ICPrevInput;     /* Mask Parameter: Difference2_ICPrevInput
                                       * Referenced by: '<S12>/UD'
                                       */
  accel delta_Y0;                      /* Computed Parameter: delta_Y0
                                        * Referenced by: '<S9>/delta'
                                        */
  accel offset_Y0;                     /* Computed Parameter: offset_Y0
                                        * Referenced by: '<S8>/offset'
                                        */
  accel core_logic_delta;          /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
                                    * Referenced by: '<Root>/core_logic'
                                    */
  accel core_logic_acc_offset;     /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
                                    * Referenced by: '<Root>/core_logic'
                                    */
  accel core_logic_acc_calibrated; /* Expression: struct('X', 0, 'Y', 0, 'Z', 0)
                                    * Referenced by: '<Root>/core_logic'
                                    */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S9>/Delay'
                                        */
  real_T Quantizer_Interval;           /* Expression: 0.1
                                        * Referenced by: '<S9>/Quantizer'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S9>/Delay1'
                                        */
  real_T Quantizer1_Interval;          /* Expression: 0.1
                                        * Referenced by: '<S9>/Quantizer1'
                                        */
  real_T Delay2_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S9>/Delay2'
                                        */
  real_T Quantizer2_Interval;          /* Expression: 0.1
                                        * Referenced by: '<S9>/Quantizer2'
                                        */
};

extern void warning_system_MovingAverage_Init(DW_MovingAverage_warning_system_T *
  localDW);
extern void warning_system_MovingAverage(real_T rtu_0,
  B_MovingAverage_warning_system_T *localB, DW_MovingAverage_warning_system_T
  *localDW);
extern void warning_system_core_logic_Init(uint8_T *rty_transmit, accel
  *rty_delta, accel *rty_acc_offset, accel *rty_acc_calibrated, real_T
  *rty_VEHICLE_STATUS, B_core_logic_warning_system_T *localB,
  DW_core_logic_warning_system_T *localDW, P_core_logic_warning_system_T *localP);
extern void warning_system_core_logic(boolean_T rtu_reciving, const accel
  *rtu_acc_raw, uint8_T *rty_transmit, accel *rty_delta, accel *rty_acc_offset,
  accel *rty_acc_calibrated, real_T *rty_VEHICLE_STATUS,
  B_core_logic_warning_system_T *localB, DW_core_logic_warning_system_T *localDW,
  P_core_logic_warning_system_T *localP);
extern void warning_system_MovingAverage_Term(DW_MovingAverage_warning_system_T *
  localDW);
extern void warning_system_core_logic_Term(DW_core_logic_warning_system_T
  *localDW);

#endif                                 /* core_logic_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

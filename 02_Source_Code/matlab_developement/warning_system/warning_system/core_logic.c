/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: core_logic.c
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

#include "core_logic.h"
#include "rtwtypes.h"
#include "warning_system_types.h"
#include "warning_system_private.h"
#include "warning_system.h"
#include <math.h>

/* Named constants for Chart: '<Root>/core_logic' */
#define warning_system_IN_CAUTION      ((uint8_T)1U)
#define warning_system_IN_CRASHED      ((uint8_T)2U)
#define warning_system_IN_Init         ((uint8_T)3U)
#define warning_system_IN_NEARBY_CRASH ((uint8_T)4U)
#define warning_system_IN_NORMAL       ((uint8_T)5U)
#define warning_system_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define warning_system_IN_caliberation ((uint8_T)6U)
#define warning_system_IN_delta_computation ((uint8_T)1U)
#define warning_system_IN_extracting_acc ((uint8_T)2U)
#define warning_system_IN_mpu_running  ((uint8_T)7U)

/* Forward declaration for local functions */
static void warning_system_SystemCore_setup
  (dsp_simulink_MovingAverage_warning_system_T *obj);

/* Forward declaration for local functions */
static boolean_T warning_system_is_rest(accel *rty_delta);
static boolean_T warning_system_is_crashed(accel *rty_delta);
static uint8_T warning_system_offset_mismatch(uint8_T COUNT_CALIBRATION, const
  accel *rtu_acc_raw, accel *rty_acc_offset);
static boolean_T warning_system_is_caution(accel *rty_delta);
static real_T warning_system_lane_changed(accel *rty_acc_calibrated);
static void warning_system_SystemCore_setup
  (dsp_simulink_MovingAverage_warning_system_T *obj)
{
  obj->isInitialized = 1;

  /* Start for MATLABSystem: '<S8>/Moving Average' */
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->pCumSum = 0.0;
  obj->pCumSumRev[0] = 0.0;
  obj->pCumSumRev[1] = 0.0;
  obj->pCumSumRev[2] = 0.0;
  obj->pCumRevIndex = 1.0;
  obj->pModValueRev = 0.0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* System initialize for atomic system: */
void warning_system_MovingAverage_Init(DW_MovingAverage_warning_system_T
  *localDW)
{
  /* Start for MATLABSystem: '<S8>/Moving Average' */
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  warning_system_SystemCore_setup(&localDW->obj);

  /* InitializeConditions for MATLABSystem: '<S8>/Moving Average' */
  localDW->obj.pCumSum = 0.0;
  localDW->obj.pCumSumRev[0] = 0.0;
  localDW->obj.pCumSumRev[1] = 0.0;
  localDW->obj.pCumSumRev[2] = 0.0;
  localDW->obj.pCumRevIndex = 1.0;
  localDW->obj.pModValueRev = 0.0;
}

/* Output and update for atomic system: */
void warning_system_MovingAverage(real_T rtu_0, B_MovingAverage_warning_system_T
  *localB, DW_MovingAverage_warning_system_T *localDW)
{
  real_T csum;
  real_T cumRevIndex;
  real_T z;

  /* MATLABSystem: '<S8>/Moving Average' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  z = 0.0;

  /* MATLABSystem: '<S8>/Moving Average' */
  localB->X = 0.0;

  /* MATLABSystem: '<S8>/Moving Average' */
  csum = localDW->obj.pCumSum + rtu_0;
  if (localDW->obj.pModValueRev == 0.0) {
    z = localDW->obj.pCumSumRev[(int32_T)localDW->obj.pCumRevIndex - 1] + csum;
  }

  localDW->obj.pCumSumRev[(int32_T)localDW->obj.pCumRevIndex - 1] = rtu_0;
  if (localDW->obj.pCumRevIndex != 3.0) {
    cumRevIndex = localDW->obj.pCumRevIndex + 1.0;
  } else {
    cumRevIndex = 1.0;
    csum = 0.0;
    localDW->obj.pCumSumRev[1] += localDW->obj.pCumSumRev[2];
    localDW->obj.pCumSumRev[0] += localDW->obj.pCumSumRev[1];
  }

  if (localDW->obj.pModValueRev == 0.0) {
    /* MATLABSystem: '<S8>/Moving Average' */
    localB->X = z / 4.0;
  }

  localDW->obj.pCumSum = csum;
  localDW->obj.pCumRevIndex = cumRevIndex;
  if (localDW->obj.pModValueRev > 0.0) {
    localDW->obj.pModValueRev--;
  } else {
    localDW->obj.pModValueRev = 0.0;
  }
}

/* Termination for atomic system: */
void warning_system_MovingAverage_Term(DW_MovingAverage_warning_system_T
  *localDW)
{
  /* Terminate for MATLABSystem: '<S8>/Moving Average' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S8>/Moving Average' */
}

/* Function for Chart: '<Root>/core_logic' */
static boolean_T warning_system_is_rest(accel *rty_delta)
{
  return (fabs(rty_delta->X) >= warning_system_P.THRESHOLD_REST) && ((fabs
    (rty_delta->Y) >= warning_system_P.THRESHOLD_REST) && (fabs(rty_delta->Z) >=
    warning_system_P.THRESHOLD_REST));
}

/* Function for Chart: '<Root>/core_logic' */
static boolean_T warning_system_is_crashed(accel *rty_delta)
{
  return fabs(rty_delta->Y) >= warning_system_P.THRESHOLD_CRASHED;
}

/* Function for Chart: '<Root>/core_logic' */
static uint8_T warning_system_offset_mismatch(uint8_T COUNT_CALIBRATION, const
  accel *rtu_acc_raw, accel *rty_acc_offset)
{
  int32_T tmp;
  uint8_T count;
  count = COUNT_CALIBRATION;
  if ((fabs(rtu_acc_raw->X - rty_acc_offset->X) > 0.01) && (fabs(rtu_acc_raw->Y
        - rty_acc_offset->Y) > 0.01) && (fabs(rtu_acc_raw->Z - rty_acc_offset->Z)
       > 0.01)) {
    tmp = (int32_T)(COUNT_CALIBRATION + 1U);
    if (COUNT_CALIBRATION + 1U > 255U) {
      tmp = 255;
    }

    count = (uint8_T)tmp;
  }

  return count;
}

/* Function for Chart: '<Root>/core_logic' */
static boolean_T warning_system_is_caution(accel *rty_delta)
{
  return fabs(rty_delta->Y) >= warning_system_P.THRESHOLD_CAUTION;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<Root>/core_logic' */
static real_T warning_system_lane_changed(accel *rty_acc_calibrated)
{
  real_T y;
  y = 0.0;
  if (rty_acc_calibrated->X > warning_system_P.THRESHOLD_LANE_CHANGE) {
    y = 1.0;
  } else if (rty_acc_calibrated->X < -warning_system_P.THRESHOLD_LANE_CHANGE) {
    y = -1.0;
  }

  return y;
}

/* System initialize for atomic system: '<Root>/core_logic' */
void warning_system_core_logic_Init(uint8_T *rty_transmit, accel *rty_delta,
  accel *rty_acc_offset, accel *rty_acc_calibrated, real_T *rty_VEHICLE_STATUS,
  B_core_logic_warning_system_T *localB, DW_core_logic_warning_system_T *localDW,
  P_core_logic_warning_system_T *localP)
{
  *rty_transmit = 0U;
  *rty_delta = localP->core_logic_delta;
  *rty_acc_offset = localP->core_logic_acc_offset;
  *rty_acc_calibrated = localP->core_logic_acc_calibrated;
  *rty_VEHICLE_STATUS = 0.0;

  /* SystemInitialize for Function Call SubSystem: '<S3>/check_jerk' */
  /* InitializeConditions for UnitDelay: '<S10>/UD'
   *
   * Block description for '<S10>/UD':
   *
   *  Store in Global RAM
   */
  localDW->UD_DSTATE = localP->Difference_ICPrevInput;

  /* InitializeConditions for UnitDelay: '<S11>/UD'
   *
   * Block description for '<S11>/UD':
   *
   *  Store in Global RAM
   */
  localDW->UD_DSTATE_c = localP->Difference1_ICPrevInput;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  localDW->Delay_DSTATE[0] = localP->Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay1' */
  localDW->Delay1_DSTATE[0] = localP->Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay2' */
  localDW->Delay2_DSTATE[0] = localP->Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  localDW->Delay_DSTATE[1] = localP->Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay1' */
  localDW->Delay1_DSTATE[1] = localP->Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay2' */
  localDW->Delay2_DSTATE[1] = localP->Delay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/UD'
   *
   * Block description for '<S12>/UD':
   *
   *  Store in Global RAM
   */
  localDW->UD_DSTATE_a = localP->Difference2_ICPrevInput;

  /* SystemInitialize for BusCreator generated from: '<S9>/Signal Conversion1' incorporates:
   *  Outport: '<S9>/delta'
   */
  localB->SignalConversion1_BusCreator1 = localP->delta_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/check_jerk' */

  /* SystemInitialize for Function Call SubSystem: '<S3>/calibrate' */
  warning_system_MovingAverage_Init(&localDW->MovingAverage);
  warning_system_MovingAverage_Init(&localDW->MovingAverage1);
  warning_system_MovingAverage_Init(&localDW->MovingAverage2);

  /* SystemInitialize for BusCreator generated from: '<S8>/Signal Conversion' incorporates:
   *  Outport: '<S8>/offset'
   */
  localB->SignalConversion_BusCreator1 = localP->offset_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/calibrate' */
}

/* Output and update for atomic system: '<Root>/core_logic' */
void warning_system_core_logic(boolean_T rtu_reciving, const accel *rtu_acc_raw,
  uint8_T *rty_transmit, accel *rty_delta, accel *rty_acc_offset, accel
  *rty_acc_calibrated, real_T *rty_VEHICLE_STATUS, B_core_logic_warning_system_T
  *localB, DW_core_logic_warning_system_T *localDW,
  P_core_logic_warning_system_T *localP)
{
  real_T rtb_Delay;
  real_T rtb_Delay1;
  real_T rtb_Delay2;
  int32_T qY;
  uint32_T qY_0;
  boolean_T guard1;
  boolean_T guard2;
  boolean_T guard3;
  boolean_T guard4;
  boolean_T out;
  if (localDW->temporalCounter_i1 < MAX_uint32_T) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<Root>/core_logic' */
  if (localDW->is_active_c6_warning_system == 0) {
    localDW->is_active_c6_warning_system = 1U;
    localDW->tp_Init = 1U;
    localDW->is_c6_warning_system = warning_system_IN_Init;
    localDW->COUNT_CALIBRATION = 10U;
    *rty_VEHICLE_STATUS = 8.0;
    localDW->COUNT_CRASHED = 0U;
    localDW->COUNT_NEARBY_CRASHED = 0U;
    localDW->COUNT_CAUTION = 0U;
    *rty_transmit = 0U;
  } else {
    guard1 = false;
    guard2 = false;
    guard3 = false;
    guard4 = false;
    switch (localDW->is_c6_warning_system) {
     case warning_system_IN_CAUTION:
      qY_0 = localDW->COUNT_CAUTION - 1U;
      if (localDW->COUNT_CAUTION - 1U > localDW->COUNT_CAUTION) {
        qY_0 = 0U;
      }

      localDW->COUNT_CAUTION = (uint8_T)qY_0;
      *rty_transmit = localDW->COUNT_CAUTION;
      localDW->tp_CAUTION = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     case warning_system_IN_CRASHED:
      qY_0 = localDW->COUNT_CRASHED - 1U;
      if (localDW->COUNT_CRASHED - 1U > localDW->COUNT_CRASHED) {
        qY_0 = 0U;
      }

      localDW->COUNT_CRASHED = (uint8_T)qY_0;
      *rty_transmit = localDW->COUNT_CRASHED;
      localDW->tp_CRASHED = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     case warning_system_IN_Init:
      localDW->tp_Init = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     case warning_system_IN_NEARBY_CRASH:
      qY_0 = localDW->COUNT_NEARBY_CRASHED - 1U;
      if (localDW->COUNT_NEARBY_CRASHED - 1U > localDW->COUNT_NEARBY_CRASHED) {
        qY_0 = 0U;
      }

      localDW->COUNT_NEARBY_CRASHED = (uint8_T)qY_0;
      *rty_transmit = localDW->COUNT_NEARBY_CRASHED;
      localDW->tp_NEARBY_CRASH = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     case warning_system_IN_NORMAL:
      localDW->tp_NORMAL = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     case warning_system_IN_caliberation:
      localDW->tp_caliberation = 0U;
      localDW->tp_mpu_running = 1U;
      localDW->is_c6_warning_system = warning_system_IN_mpu_running;
      localDW->temporalCounter_i1 = 0U;
      localDW->tp_extracting_acc = 1U;
      localDW->is_mpu_running = warning_system_IN_extracting_acc;
      break;

     default:
      /* case IN_mpu_running: */
      switch (localDW->is_mpu_running) {
       case warning_system_IN_delta_computation:
        if (rtu_reciving) {
          localDW->COUNT_NEARBY_CRASHED = 8U;
          guard2 = true;
        } else if (warning_system_is_crashed(rty_delta)) {
          localDW->COUNT_CRASHED = 15U;
          guard3 = true;
        } else if (localDW->COUNT_CRASHED > 4) {
          guard3 = true;
        } else if (localDW->COUNT_NEARBY_CRASHED > 10) {
          guard2 = true;
        } else if (warning_system_is_caution(rty_delta)) {
          localDW->COUNT_CRASHED = 7U;
          guard4 = true;
        } else if (localDW->COUNT_CAUTION > 5) {
          guard4 = true;
        } else {
          localDW->tp_delta_computation = 0U;
          localDW->is_mpu_running = warning_system_IN_NO_ACTIVE_CHILD;
          localDW->tp_mpu_running = 0U;
          localDW->tp_NORMAL = 1U;
          localDW->is_c6_warning_system = warning_system_IN_NORMAL;
          *rty_VEHICLE_STATUS = 4.0;
          if (*rty_transmit > 0) {
            qY_0 = *rty_transmit - 1U;
            if (*rty_transmit - 1U > *rty_transmit) {
              qY_0 = 0U;
            }

            *rty_transmit = (uint8_T)qY_0;
          }

          if (warning_system_lane_changed(rty_acc_calibrated) == 1.0) {
            *rty_VEHICLE_STATUS = 8.0;
            *rty_transmit = 8U;
          } else if (warning_system_lane_changed(rty_acc_calibrated) == -1.0) {
            *rty_VEHICLE_STATUS = 16.0;
            *rty_transmit = 8U;
          }
        }
        break;

       default:
        /* case IN_extracting_acc: */
        if (warning_system_is_rest(rty_delta)) {
          out = (warning_system_offset_mismatch(localDW->COUNT_CALIBRATION,
                  rtu_acc_raw, rty_acc_offset) != 0);
        } else {
          out = false;
        }

        if (out) {
          guard1 = true;
        } else if (localDW->COUNT_CALIBRATION > 0) {
          qY = (int32_T)(localDW->COUNT_CALIBRATION - 1U);
          if ((int32_T)(localDW->COUNT_CALIBRATION - 1U) >
              localDW->COUNT_CALIBRATION) {
            qY = 0;
          }

          localDW->COUNT_CALIBRATION = (uint8_T)qY;
          guard1 = true;
        } else if (localDW->temporalCounter_i1 > 1U) {
          localDW->tp_extracting_acc = 0U;
          localDW->tp_delta_computation = 1U;
          localDW->is_mpu_running = warning_system_IN_delta_computation;

          /* Outputs for Function Call SubSystem: '<S3>/check_jerk' */
          /* Delay: '<S9>/Delay' */
          rtb_Delay = localDW->Delay_DSTATE[0];

          /* Delay: '<S9>/Delay1' */
          rtb_Delay1 = localDW->Delay1_DSTATE[0];

          /* Delay: '<S9>/Delay2' */
          rtb_Delay2 = localDW->Delay2_DSTATE[0];

          /* BusCreator generated from: '<S9>/Signal Conversion1' incorporates:
           *  Delay: '<S9>/Delay'
           *  Delay: '<S9>/Delay1'
           *  Delay: '<S9>/Delay2'
           *  Quantizer: '<S9>/Quantizer'
           *  Quantizer: '<S9>/Quantizer1'
           *  Quantizer: '<S9>/Quantizer2'
           *  Sum: '<S10>/Diff'
           *  Sum: '<S11>/Diff'
           *  Sum: '<S12>/Diff'
           *  UnitDelay: '<S10>/UD'
           *  UnitDelay: '<S11>/UD'
           *  UnitDelay: '<S12>/UD'
           *
           * Block description for '<S10>/Diff':
           *
           *  Add in CPU
           *
           * Block description for '<S11>/Diff':
           *
           *  Add in CPU
           *
           * Block description for '<S12>/Diff':
           *
           *  Add in CPU
           *
           * Block description for '<S10>/UD':
           *
           *  Store in Global RAM
           *
           * Block description for '<S11>/UD':
           *
           *  Store in Global RAM
           *
           * Block description for '<S12>/UD':
           *
           *  Store in Global RAM
           */
          localB->SignalConversion1_BusCreator1.X = rt_roundd_snf
            ((localDW->Delay_DSTATE[0] - localDW->UD_DSTATE) /
             localP->Quantizer_Interval) * localP->Quantizer_Interval;
          localB->SignalConversion1_BusCreator1.Y = rt_roundd_snf
            ((localDW->Delay1_DSTATE[0] - localDW->UD_DSTATE_c) /
             localP->Quantizer1_Interval) * localP->Quantizer1_Interval;
          localB->SignalConversion1_BusCreator1.Z = rt_roundd_snf
            ((localDW->Delay2_DSTATE[0] - localDW->UD_DSTATE_a) /
             localP->Quantizer2_Interval) * localP->Quantizer2_Interval;

          /* Update for Delay: '<S9>/Delay' */
          localDW->Delay_DSTATE[0] = localDW->Delay_DSTATE[1];
          localDW->Delay_DSTATE[1] = rty_acc_calibrated->X;

          /* Update for UnitDelay: '<S10>/UD'
           *
           * Block description for '<S10>/UD':
           *
           *  Store in Global RAM
           */
          localDW->UD_DSTATE = rtb_Delay;

          /* Update for Delay: '<S9>/Delay1' */
          localDW->Delay1_DSTATE[0] = localDW->Delay1_DSTATE[1];
          localDW->Delay1_DSTATE[1] = rty_acc_calibrated->Y;

          /* Update for UnitDelay: '<S11>/UD'
           *
           * Block description for '<S11>/UD':
           *
           *  Store in Global RAM
           */
          localDW->UD_DSTATE_c = rtb_Delay1;

          /* Update for Delay: '<S9>/Delay2' */
          localDW->Delay2_DSTATE[0] = localDW->Delay2_DSTATE[1];
          localDW->Delay2_DSTATE[1] = rty_acc_calibrated->Z;

          /* Update for UnitDelay: '<S12>/UD'
           *
           * Block description for '<S12>/UD':
           *
           *  Store in Global RAM
           */
          localDW->UD_DSTATE_a = rtb_Delay2;

          /* End of Outputs for SubSystem: '<S3>/check_jerk' */
          *rty_delta = localB->SignalConversion1_BusCreator1;
        } else {
          rty_acc_calibrated->X = rtu_acc_raw->X - rty_acc_offset->X;
          rty_acc_calibrated->Y = rtu_acc_raw->Y - rty_acc_offset->Y;
          rty_acc_calibrated->Z = rtu_acc_raw->Z - rty_acc_offset->Z;
        }
        break;
      }
      break;
    }

    if (guard4) {
      localDW->tp_delta_computation = 0U;
      localDW->is_mpu_running = warning_system_IN_NO_ACTIVE_CHILD;
      localDW->tp_mpu_running = 0U;
      localDW->tp_CAUTION = 1U;
      localDW->is_c6_warning_system = warning_system_IN_CAUTION;
      *rty_VEHICLE_STATUS = 100.0;
    }

    if (guard3) {
      localDW->tp_delta_computation = 0U;
      localDW->is_mpu_running = warning_system_IN_NO_ACTIVE_CHILD;
      localDW->tp_mpu_running = 0U;
      localDW->tp_CRASHED = 1U;
      localDW->is_c6_warning_system = warning_system_IN_CRASHED;
      *rty_VEHICLE_STATUS = 128.0;
    }

    if (guard2) {
      localDW->tp_delta_computation = 0U;
      localDW->is_mpu_running = warning_system_IN_NO_ACTIVE_CHILD;
      localDW->tp_mpu_running = 0U;
      localDW->tp_NEARBY_CRASH = 1U;
      localDW->is_c6_warning_system = warning_system_IN_NEARBY_CRASH;
      *rty_VEHICLE_STATUS = 32.0;
    }

    if (guard1) {
      localDW->tp_extracting_acc = 0U;
      localDW->is_mpu_running = warning_system_IN_NO_ACTIVE_CHILD;
      localDW->tp_mpu_running = 0U;
      localDW->tp_caliberation = 1U;
      localDW->is_c6_warning_system = warning_system_IN_caliberation;

      /* Outputs for Function Call SubSystem: '<S3>/calibrate' */
      warning_system_MovingAverage(rtu_acc_raw->X, &localB->MovingAverage,
        &localDW->MovingAverage);
      warning_system_MovingAverage(rtu_acc_raw->Y, &localB->MovingAverage1,
        &localDW->MovingAverage1);
      warning_system_MovingAverage(rtu_acc_raw->Z, &localB->MovingAverage2,
        &localDW->MovingAverage2);

      /* BusCreator generated from: '<S8>/Signal Conversion' */
      localB->SignalConversion_BusCreator1.X = localB->MovingAverage.X;
      localB->SignalConversion_BusCreator1.Y = localB->MovingAverage1.X;
      localB->SignalConversion_BusCreator1.Z = localB->MovingAverage2.X;

      /* End of Outputs for SubSystem: '<S3>/calibrate' */
      *rty_acc_offset = localB->SignalConversion_BusCreator1;
    }
  }

  /* End of Chart: '<Root>/core_logic' */
}

/* Termination for atomic system: '<Root>/core_logic' */
void warning_system_core_logic_Term(DW_core_logic_warning_system_T *localDW)
{
  /* Terminate for Function Call SubSystem: '<S3>/calibrate' */
  warning_system_MovingAverage_Term(&localDW->MovingAverage);
  warning_system_MovingAverage_Term(&localDW->MovingAverage1);
  warning_system_MovingAverage_Term(&localDW->MovingAverage2);

  /* End of Terminate for SubSystem: '<S3>/calibrate' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

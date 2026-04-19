/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: output_transmitter.c
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

#include "warning_system_types.h"
#include "output_transmitter.h"
#include "rtwtypes.h"
#include "half_type.h"
#include <string.h>
#include "warning_system_private.h"
#include <stddef.h>
#include "warning_system.h"
#include <math.h>

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* System initialize for enable system: '<Root>/output_transmitter' */
void warning_system_output_transmitter_Init(ITC_status *rty_Status,
  DW_output_transmitter_warning_system_T *localDW,
  P_output_transmitter_warning_system_T *localP)
{
  /* Start for MATLABSystem: '<S6>/I2C Write' */
  localDW->obj.DefaultMaximumBusSpeedInHz = 400000.0;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  localDW->obj.BusSpeed = 100000U;
  MW_I2C_SetBusSpeed(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 100000U);
  localDW->obj.isSetupComplete = true;

  /* SystemInitialize for Outport: '<S6>/Status' */
  *rty_Status = localP->Status_Y0;
}

/* Disable for enable system: '<Root>/output_transmitter' */
void warning_system_output_transmitter_Disable
  (DW_output_transmitter_warning_system_T *localDW)
{
  localDW->output_transmitter_MODE = false;
}

/* Output and update for enable system: '<Root>/output_transmitter' */
void warning_system_output_transmitter(RT_MODEL_warning_system_T * const
  warning_system_M, boolean_T rtu_Enable, real_T rtu_local_gps, real_T
  rtu_local_gps_g, real_T rtu_local_gps_p, real_T rtu_status, real16_T
  rtu_zigbeeAddress, ITC_status *rty_Status,
  DW_output_transmitter_warning_system_T *localDW)
{
  real_T tmp;
  real32_T x;
  uint16_T d_x;
  uint8_T rtb_packet_bytes[15];
  uint8_T lat_bytes[4];
  uint8_T lon_bytes[4];
  uint8_T speed_bytes[4];
  uint8_T zigbee_bytes[2];
  uint8_T status;

  /* Outputs for Enabled SubSystem: '<Root>/output_transmitter' incorporates:
   *  EnablePort: '<S6>/Enable'
   */
  if (rtu_Enable) {
    localDW->output_transmitter_MODE = true;
    if (warning_system_M->Timing.TaskCounters.TID[1] == 0) {
      /* MATLAB Function: '<S6>/MATLAB Function' */
      x = (real32_T)rtu_local_gps;
      memcpy((void *)&lat_bytes[0], (void *)&x, (size_t)4 * sizeof(uint8_T));
      x = (real32_T)rtu_local_gps_g;
      memcpy((void *)&lon_bytes[0], (void *)&x, (size_t)4 * sizeof(uint8_T));
      x = (real32_T)rtu_local_gps_p;
      memcpy((void *)&speed_bytes[0], (void *)&x, (size_t)4 * sizeof(uint8_T));
      x = rt_roundf_snf(halfToFloat(rtu_zigbeeAddress));
      if (x < 65536.0F) {
        if (x >= 0.0F) {
          d_x = (uint16_T)x;
        } else {
          d_x = 0U;
        }
      } else {
        d_x = MAX_uint16_T;
      }

      memcpy((void *)&zigbee_bytes[0], (void *)&d_x, (size_t)2 * sizeof(uint8_T));
      rtb_packet_bytes[0] = lat_bytes[0];
      rtb_packet_bytes[4] = lon_bytes[0];
      rtb_packet_bytes[8] = speed_bytes[0];
      rtb_packet_bytes[1] = lat_bytes[1];
      rtb_packet_bytes[5] = lon_bytes[1];
      rtb_packet_bytes[9] = speed_bytes[1];
      rtb_packet_bytes[2] = lat_bytes[2];
      rtb_packet_bytes[6] = lon_bytes[2];
      rtb_packet_bytes[10] = speed_bytes[2];
      rtb_packet_bytes[3] = lat_bytes[3];
      rtb_packet_bytes[7] = lon_bytes[3];
      rtb_packet_bytes[11] = speed_bytes[3];
      rtb_packet_bytes[12] = zigbee_bytes[0];
      rtb_packet_bytes[13] = zigbee_bytes[1];
      tmp = rt_roundd_snf(rtu_status);
      if (tmp < 256.0) {
        if (tmp >= 0.0) {
          rtb_packet_bytes[14] = (uint8_T)tmp;
        } else {
          rtb_packet_bytes[14] = 0U;
        }
      } else {
        rtb_packet_bytes[14] = MAX_uint8_T;
      }

      /* End of MATLAB Function: '<S6>/MATLAB Function' */

      /* MATLABSystem: '<S6>/I2C Write' */
      status = MW_I2C_MasterWrite(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 60U,
        &rtb_packet_bytes[0], 15U, false, false);

      /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
       *  MATLABSystem: '<S6>/I2C Write'
       * */
      *rty_Status = status;
    }
  } else if (localDW->output_transmitter_MODE) {
    warning_system_output_transmitter_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<Root>/output_transmitter' */
}

/* Termination for enable system: '<Root>/output_transmitter' */
void warning_system_output_transmitter_Term
  (DW_output_transmitter_warning_system_T *localDW)
{
  /* Terminate for MATLABSystem: '<S6>/I2C Write' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      MW_I2C_Close(localDW->obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/I2C Write' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

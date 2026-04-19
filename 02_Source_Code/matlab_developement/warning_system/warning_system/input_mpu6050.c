/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_mpu6050.c
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

#include "input_mpu6050.h"
#include "rtwtypes.h"
#include <string.h>
#include <stddef.h>
#include "warning_system.h"

/* Named constants for Chart: '<Root>/input_mpu6050' */
#define warning_system_IN_Accelerometer_Configuration ((uint8_T)1U)
#define warning_system_IN_Gyro_Configuration ((uint8_T)2U)
#define warning_system_IN_Initialisation ((uint8_T)3U)
#define warning_system_IN_MPU_Running  ((uint8_T)4U)

/* System initialize for function-call system: '<S4>/i2cWr' */
void warning_system_i2cWr_Init(DW_i2cWr_warning_system_T *localDW)
{
  /* Start for MATLABSystem: '<S14>/Ecriture I2C' */
  localDW->obj.DefaultMaximumBusSpeedInHz = 400000.0;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  localDW->obj.BusSpeed = 100000U;
  MW_I2C_SetBusSpeed(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 100000U);
  localDW->obj.isSetupComplete = true;
}

/* Output and update for function-call system: '<S4>/i2cWr' */
void warning_system_i2cWr(uint16_T rtu_dataw, DW_i2cWr_warning_system_T *localDW)
{
  uint16_T b_x;
  uint8_T SwappedDataBytes[2];
  uint8_T b_x_0[2];

  /* MATLABSystem: '<S14>/Ecriture I2C' */
  memcpy((void *)&SwappedDataBytes[0], (void *)&rtu_dataw, (size_t)2 * sizeof
         (uint8_T));
  b_x_0[0] = SwappedDataBytes[1];
  b_x_0[1] = SwappedDataBytes[0];
  memcpy((void *)&b_x, (void *)&b_x_0[0], (size_t)1 * sizeof(uint16_T));
  memcpy((void *)&SwappedDataBytes[0], (void *)&b_x, (size_t)2 * sizeof(uint8_T));
  MW_I2C_MasterWrite(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 104U,
                     &SwappedDataBytes[0], 2U, false, false);
}

/* Termination for function-call system: '<S4>/i2cWr' */
void warning_system_i2cWr_Term(DW_i2cWr_warning_system_T *localDW)
{
  /* Terminate for MATLABSystem: '<S14>/Ecriture I2C' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      MW_I2C_Close(localDW->obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S14>/Ecriture I2C' */
}

/* System initialize for atomic system: '<Root>/input_mpu6050' */
void warning_system_input_mpu6050_Init(real_T *rty_acc_x, real_T *rty_acc_z,
  real_T *rty_acc_y, real_T *rty_gyro_x, real_T *rty_gyro_y, real_T *rty_gyro_z,
  DW_input_mpu6050_warning_system_T *localDW)
{
  *rty_acc_x = 0.0;
  *rty_acc_z = 0.0;
  *rty_acc_y = 0.0;
  *rty_gyro_x = 0.0;
  *rty_gyro_y = 0.0;
  *rty_gyro_z = 0.0;

  /* SystemInitialize for Function Call SubSystem: '<S4>/i2cRd' */
  /* Start for MATLABSystem: '<S13>/I2C Read' */
  localDW->obj.DefaultMaximumBusSpeedInHz = 400000.0;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  localDW->obj.BusSpeed = 100000U;
  MW_I2C_SetBusSpeed(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 100000U);
  localDW->obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<S4>/i2cRd' */

  /* SystemInitialize for Function Call SubSystem: '<S4>/i2cWr' */
  warning_system_i2cWr_Init(&localDW->i2cWr);

  /* End of SystemInitialize for SubSystem: '<S4>/i2cWr' */
}

/* Output and update for atomic system: '<Root>/input_mpu6050' */
void warning_system_input_mpu6050(real_T *rty_acc_x, real_T *rty_acc_z, real_T
  *rty_acc_y, real_T *rty_gyro_x, real_T *rty_gyro_y, real_T *rty_gyro_z,
  DW_input_mpu6050_warning_system_T *localDW)
{
  int32_T i;
  int16_T val_data[7];
  uint16_T rtb_I2CRead_0[7];
  uint16_T y_0;
  uint8_T output_raw[14];
  uint8_T b_x[2];
  uint8_T y[2];
  uint8_T status;

  /* Chart: '<Root>/input_mpu6050' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion'
   *  MATLABSystem: '<S13>/I2C Read'
   */
  if (localDW->is_active_c1_warning_system == 0) {
    localDW->is_active_c1_warning_system = 1U;
    localDW->is_c1_warning_system = warning_system_IN_Initialisation;

    /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
    warning_system_i2cWr(27392, &localDW->i2cWr);

    /* End of Outputs for SubSystem: '<S4>/i2cWr' */
    if (!ENABLE_GYRO) {
      /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
      warning_system_i2cWr(27655, &localDW->i2cWr);

      /* End of Outputs for SubSystem: '<S4>/i2cWr' */
    } else {
      /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
      warning_system_i2cWr(27648, &localDW->i2cWr);

      /* End of Outputs for SubSystem: '<S4>/i2cWr' */
    }

    if (DLPF_SETTING <= 6) {
      /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
      warning_system_i2cWr((uint16_T)(DLPF_SETTING + 6656U), &localDW->i2cWr);

      /* End of Outputs for SubSystem: '<S4>/i2cWr' */
    }
  } else {
    switch (localDW->is_c1_warning_system) {
     case warning_system_IN_Accelerometer_Configuration:
      localDW->is_c1_warning_system = warning_system_IN_Gyro_Configuration;
      switch (GYRO_RANGE) {
       case 250U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(6912, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->gyro_scale_factor = 131.0;
        break;

       case 500U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(6920, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->gyro_scale_factor = 65.5;
        break;

       case 1000U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(6928, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->gyro_scale_factor = 32.2;
        break;

       case 2000U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(6936, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->gyro_scale_factor = 16.4;
        break;
      }
      break;

     case warning_system_IN_Gyro_Configuration:
      localDW->is_c1_warning_system = warning_system_IN_MPU_Running;
      break;

     case warning_system_IN_Initialisation:
      localDW->is_c1_warning_system =
        warning_system_IN_Accelerometer_Configuration;
      switch (ACCEL_RANGE) {
       case 2U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(7168, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->acc_scale_factor = 16384.0;
        break;

       case 4U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(7176, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->acc_scale_factor = 8192.0;
        break;

       case 8U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(7184, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->acc_scale_factor = 4096.0;
        break;

       case 16U:
        /* Outputs for Function Call SubSystem: '<S4>/i2cWr' */
        warning_system_i2cWr(7192, &localDW->i2cWr);

        /* End of Outputs for SubSystem: '<S4>/i2cWr' */
        localDW->acc_scale_factor = 2048.0;
        break;
      }
      break;

     default:
      /* Outputs for Function Call SubSystem: '<S4>/i2cRd' */
      /* MATLABSystem: '<S13>/I2C Read' */
      /* case IN_MPU_Running: */
      status = 59U;
      status = MW_I2C_MasterWrite(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 104U,
        &status, 1U, true, false);
      if (status == 0) {
        MW_I2C_MasterRead(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 104U,
                          &output_raw[0], 14U, false, true);
        memcpy((void *)&rtb_I2CRead_0[0], (void *)&output_raw[0], (size_t)7 *
               sizeof(uint16_T));
        for (i = 0; i < 7; i++) {
          memcpy((void *)&y[0], (void *)&rtb_I2CRead_0[i], (size_t)2 * sizeof
                 (uint8_T));
          b_x[0] = y[1];
          b_x[1] = y[0];
          memcpy((void *)&y_0, (void *)&b_x[0], (size_t)1 * sizeof(uint16_T));
          rtb_I2CRead_0[i] = y_0;
        }
      } else {
        for (i = 0; i < 7; i++) {
          rtb_I2CRead_0[i] = 0U;
        }
      }

      /* End of Outputs for SubSystem: '<S4>/i2cRd' */
      localDW->val_sizes = 7;
      for (i = 0; i < 7; i++) {
        /* Outputs for Function Call SubSystem: '<S4>/i2cRd' */
        val_data[i] = (int16_T)rtb_I2CRead_0[i];

        /* End of Outputs for SubSystem: '<S4>/i2cRd' */
      }

      *rty_acc_x = (real_T)val_data[0] / localDW->acc_scale_factor;
      *rty_acc_y = (real_T)val_data[1] / localDW->acc_scale_factor;
      *rty_acc_z = (real_T)val_data[2] / localDW->acc_scale_factor;
      *rty_gyro_x = (real_T)val_data[4] / localDW->gyro_scale_factor;
      *rty_gyro_y = (real_T)val_data[5] / localDW->gyro_scale_factor;
      *rty_gyro_z = (real_T)val_data[6] / localDW->gyro_scale_factor;
      break;
    }
  }

  /* End of Chart: '<Root>/input_mpu6050' */
}

/* Termination for atomic system: '<Root>/input_mpu6050' */
void warning_system_input_mpu6050_Term(DW_input_mpu6050_warning_system_T
  *localDW)
{
  /* Terminate for Function Call SubSystem: '<S4>/i2cRd' */
  /* Terminate for MATLABSystem: '<S13>/I2C Read' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      MW_I2C_Close(localDW->obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S13>/I2C Read' */
  /* End of Terminate for SubSystem: '<S4>/i2cRd' */

  /* Terminate for Function Call SubSystem: '<S4>/i2cWr' */
  warning_system_i2cWr_Term(&localDW->i2cWr);

  /* End of Terminate for SubSystem: '<S4>/i2cWr' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

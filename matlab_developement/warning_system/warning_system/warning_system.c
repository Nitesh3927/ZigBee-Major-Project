/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: warning_system.c
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
#include "warning_system_types.h"
#include "rtwtypes.h"
#include "input_transmitter.h"
#include "input_mpu6050.h"
#include "core_logic.h"
#include "output_transmitter.h"
#include "warning_system_private.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_nonfinite.h"

/* Exported block parameters */
uint16_T GYRO_RANGE = 250U;            /* Variable: GYRO_RANGE
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
boolean_T ENABLE_GYRO = true;          /* Variable: ENABLE_GYRO
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
uint8_T ACCEL_RANGE = 4U;              /* Variable: ACCEL_RANGE
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */
uint8_T DLPF_SETTING = 6U;             /* Variable: DLPF_SETTING
                                        * Referenced by: '<Root>/input_mpu6050'
                                        */

/* Block signals (default storage) */
B_warning_system_T warning_system_B;

/* Block states (default storage) */
DW_warning_system_T warning_system_DW;

/* Real-time model */
static RT_MODEL_warning_system_T warning_system_M_;
RT_MODEL_warning_system_T *const warning_system_M = &warning_system_M_;

/* Forward declaration for local functions */
static void warning_system_emxInit_char_T(emxArray_char_T_warning_system_T
  **pEmxArray, int32_T numDimensions);
static void warning_system_emxEnsureCapacity_char_T
  (emxArray_char_T_warning_system_T *emxArray, int32_T oldNumel);
static void warning_system_emxFree_char_T(emxArray_char_T_warning_system_T
  **pEmxArray);
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (warning_system_M->Timing.TaskCounters.TID[1])++;
  if ((warning_system_M->Timing.TaskCounters.TID[1]) > 3) {/* Sample time: [0.2s, 0.0s] */
    warning_system_M->Timing.TaskCounters.TID[1] = 0;
  }
}

static void warning_system_emxInit_char_T(emxArray_char_T_warning_system_T
  **pEmxArray, int32_T numDimensions)
{
  emxArray_char_T_warning_system_T *emxArray;
  *pEmxArray = (emxArray_char_T_warning_system_T *)malloc(sizeof
    (emxArray_char_T_warning_system_T));
  emxArray = *pEmxArray;
  emxArray->data = (char_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)malloc(sizeof(int32_T) * (uint32_T)numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (warning_system_B.i_c = 0; warning_system_B.i_c < numDimensions;
       warning_system_B.i_c++) {
    emxArray->size[warning_system_B.i_c] = 0;
  }
}

static void warning_system_emxEnsureCapacity_char_T
  (emxArray_char_T_warning_system_T *emxArray, int32_T oldNumel)
{
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  warning_system_B.newNumel = 1;
  for (warning_system_B.i = 0; warning_system_B.i < emxArray->numDimensions;
       warning_system_B.i++) {
    warning_system_B.newNumel *= emxArray->size[warning_system_B.i];
  }

  if (warning_system_B.newNumel > emxArray->allocatedSize) {
    warning_system_B.i = emxArray->allocatedSize;
    if (warning_system_B.i < 16) {
      warning_system_B.i = 16;
    }

    while (warning_system_B.i < warning_system_B.newNumel) {
      if (warning_system_B.i > 1073741823) {
        warning_system_B.i = MAX_int32_T;
      } else {
        warning_system_B.i <<= 1;
      }
    }

    newData = malloc((uint32_T)warning_system_B.i * sizeof(char_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(char_T) * (uint32_T)oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = (char_T *)newData;
    emxArray->allocatedSize = warning_system_B.i;
    emxArray->canFreeData = true;
  }
}

static void warning_system_emxFree_char_T(emxArray_char_T_warning_system_T
  **pEmxArray)
{
  if (*pEmxArray != (emxArray_char_T_warning_system_T *)NULL) {
    if (((*pEmxArray)->data != (char_T *)NULL) && (*pEmxArray)->canFreeData) {
      free((*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_char_T_warning_system_T *)NULL;
  }
}

/* Model step function */
void warning_system_step(void)
{
  emxArray_char_T_warning_system_T *b_str;
  static const char_T e[7] = { 'U', 'N', 'K', 'N', 'O', 'W', 'N' };

  static const char_T f[7] = { 'I', 'N', 'V', 'A', 'L', 'I', 'D' };

  static const char_T g[6] = { 'N', 'O', 'R', 'M', 'A', 'L' };

  static const char_T h[17] = { 'L', 'A', 'N', 'E', '_', 'C', 'H', 'A', 'N', 'G',
    'E', '_', 'R', 'I', 'G', 'H', 'T' };

  static const char_T i[16] = { 'L', 'A', 'N', 'E', '_', 'C', 'H', 'A', 'N', 'G',
    'E', '_', 'L', 'E', 'F', 'T' };

  static const char_T j[12] = { 'N', 'E', 'A', 'R', 'B', 'Y', '_', 'C', 'R', 'A',
    'S', 'H' };

  static const char_T k[5] = { 'C', 'R', 'A', 'S', 'H' };

  static const char_T l[7] = { 'C', 'A', 'U', 'T', 'I', 'O', 'N' };

  warning_system_B.b = (warning_system_M->Timing.TaskCounters.TID[1] == 0);
  if (warning_system_B.b) {
    /* Outputs for Atomic SubSystem: '<Root>/input_transmitter' */
    warning_system_input_transmitter
      (&warning_system_B.SignalConversion_BusCreator1_m,
       &warning_system_B.reciving_flag, &warning_system_DW.input_transmitter,
       &warning_system_P.input_transmitter);

    /* End of Outputs for SubSystem: '<Root>/input_transmitter' */
  }

  /* Chart: '<Root>/input_mpu6050' */
  warning_system_input_mpu6050(&warning_system_B.SignalConversion_BusCreator1.X,
    &warning_system_B.SignalConversion_BusCreator1.Z,
    &warning_system_B.SignalConversion_BusCreator1.Y, &warning_system_B.gyro_x,
    &warning_system_B.gyro_y, &warning_system_B.gyro_z,
    &warning_system_DW.sf_input_mpu6050);

  /* Chart: '<Root>/core_logic' */
  warning_system_core_logic(warning_system_B.reciving_flag,
    &warning_system_B.SignalConversion_BusCreator1, &warning_system_B.transmit,
    &warning_system_B.delta, &warning_system_B.acc_offset,
    &warning_system_B.acc_calibrated, &warning_system_B.VEHICLE_STATUS,
    &warning_system_B.sf_core_logic, &warning_system_DW.sf_core_logic,
    &warning_system_P.sf_core_logic);

  /* MATLABSystem: '<Root>/input_gps' */
  if (warning_system_DW.obj_f.SampleTime != warning_system_P.TS_GPS) {
    warning_system_DW.obj_f.SampleTime = warning_system_P.TS_GPS;
  }

  /*         %% Define output properties */
  warning_system_B.gyro_x = 0.0;
  warning_system_B.gyro_y = 0.0;
  warning_system_B.gyro_z = 0.0;
  stepFunctionGPS_Parser(&warning_system_B.gyro_x, 1.0, &warning_system_B.gyro_y,
    1.0, &warning_system_B.gyro_z, 1.0);
  if (warning_system_B.b) {
    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  BusCreator generated from: '<S5>/Signal Conversion'
     *  MATLABSystem: '<Root>/input_gps'
     * */
    for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 130;
         warning_system_B.loop_ub++) {
      warning_system_B.str[warning_system_B.loop_ub] = ' ';
    }

    warning_system_B.d = rt_roundd_snf(warning_system_B.VEHICLE_STATUS);
    if (warning_system_B.d < 2.147483648E+9) {
      if (warning_system_B.d >= -2.147483648E+9) {
        warning_system_B.vehicle_status = (int32_T)warning_system_B.d;
      } else {
        warning_system_B.vehicle_status = MIN_int32_T;
      }
    } else {
      warning_system_B.vehicle_status = MAX_int32_T;
    }

    switch (warning_system_B.vehicle_status) {
     case 0:
      warning_system_B.nbytes = 7;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 7;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          f[warning_system_B.loop_ub];
      }
      break;

     case 4:
      warning_system_B.nbytes = 6;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 6;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          g[warning_system_B.loop_ub];
      }
      break;

     case 8:
      warning_system_B.nbytes = 17;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 17;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          h[warning_system_B.loop_ub];
      }
      break;

     case 16:
      warning_system_B.nbytes = 16;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 16;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          i[warning_system_B.loop_ub];
      }
      break;

     case 32:
      warning_system_B.nbytes = 12;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 12;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          j[warning_system_B.loop_ub];
      }
      break;

     case 128:
      warning_system_B.nbytes = 5;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 5;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          k[warning_system_B.loop_ub];
      }
      break;

     case 100:
      warning_system_B.nbytes = 7;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 7;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          l[warning_system_B.loop_ub];
      }
      break;

     default:
      warning_system_B.nbytes = 7;
      for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 7;
           warning_system_B.loop_ub++) {
        warning_system_B.varargin_1_data[warning_system_B.loop_ub] =
          e[warning_system_B.loop_ub];
      }
      break;
    }

    warning_system_B.loop_ub_tmp = warning_system_B.nbytes + 1;
    memcpy(&warning_system_B.validatedHoleFilling_f1_data[0],
           &warning_system_B.varargin_1_data[0], (uint32_T)
           warning_system_B.nbytes * sizeof(char_T));
    warning_system_B.validatedHoleFilling_f1_data[warning_system_B.nbytes] =
      '\x00';
    memcpy(&warning_system_B.b_varargin_1_data[0],
           &warning_system_B.validatedHoleFilling_f1_data[0], (uint32_T)
           warning_system_B.loop_ub_tmp * sizeof(char_T));
    warning_system_B.nbytes = snprintf(NULL, 0,
      "\n<%17s (%3d) || TRANSMIT: %2d || (%.7f, %.7f, %.3f) || RECEIVING: %d || (%.7f, %.7f, %.3f)>",
      &warning_system_B.b_varargin_1_data[0], warning_system_B.vehicle_status,
      (int32_T)warning_system_B.transmit, warning_system_B.gyro_x,
      warning_system_B.gyro_y, warning_system_B.gyro_z, (int32_T)
      warning_system_B.reciving_flag,
      warning_system_B.SignalConversion_BusCreator1_m.lat,
      warning_system_B.SignalConversion_BusCreator1_m.lng,
      warning_system_B.SignalConversion_BusCreator1_m.speed);
    warning_system_emxInit_char_T(&b_str, 2);

    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  BusCreator generated from: '<S5>/Signal Conversion'
     *  MATLABSystem: '<Root>/input_gps'
     * */
    warning_system_B.loop_ub = b_str->size[0] * b_str->size[1];
    b_str->size[0] = 1;
    b_str->size[1] = warning_system_B.nbytes + 1;
    warning_system_emxEnsureCapacity_char_T(b_str, warning_system_B.loop_ub);
    memcpy(&warning_system_B.b_varargin_1_data[0],
           &warning_system_B.validatedHoleFilling_f1_data[0], (uint32_T)
           warning_system_B.loop_ub_tmp * sizeof(char_T));
    snprintf(&b_str->data[0], (size_t)(warning_system_B.nbytes + 1),
             "\n<%17s (%3d) || TRANSMIT: %2d || (%.7f, %.7f, %.3f) || RECEIVING: %d || (%.7f, %.7f, %.3f)>",
             &warning_system_B.b_varargin_1_data[0],
             warning_system_B.vehicle_status, (int32_T)warning_system_B.transmit,
             warning_system_B.gyro_x, warning_system_B.gyro_y,
             warning_system_B.gyro_z, (int32_T)warning_system_B.reciving_flag,
             warning_system_B.SignalConversion_BusCreator1_m.lat,
             warning_system_B.SignalConversion_BusCreator1_m.lng,
             warning_system_B.SignalConversion_BusCreator1_m.speed);
    if (warning_system_B.nbytes < 1) {
      warning_system_B.nbytes = 0;
    }

    if (warning_system_B.nbytes > 130) {
      warning_system_B.nbytes = 130;
    }

    if (warning_system_B.nbytes < 1) {
      warning_system_B.loop_ub = -1;
    } else {
      warning_system_B.loop_ub = warning_system_B.nbytes - 1;
    }

    if (warning_system_B.loop_ub >= 0) {
      memcpy(&warning_system_B.str[0], &b_str->data[0], (uint32_T)
             (warning_system_B.loop_ub + 1) * sizeof(char_T));
    }

    warning_system_emxFree_char_T(&b_str);

    /* MATLABSystem: '<S1>/Serial Transmit' incorporates:
     *  MATLAB Function: '<S1>/MATLAB Function'
     */
    for (warning_system_B.loop_ub = 0; warning_system_B.loop_ub < 130;
         warning_system_B.loop_ub++) {
      warning_system_B.dataIn[warning_system_B.loop_ub] = (uint8_T)
        warning_system_B.str[warning_system_B.loop_ub];
    }

    MW_Serial_write(warning_system_DW.obj.port, &warning_system_B.dataIn[0],
                    130.0, warning_system_DW.obj.dataSizeInBytes,
                    warning_system_DW.obj.sendModeEnum,
                    warning_system_DW.obj.dataType,
                    warning_system_DW.obj.sendFormatEnum, 2.0, '\x00', NULL, 0.0,
                    NULL, 0.0);

    /* End of MATLABSystem: '<S1>/Serial Transmit' */
  }

  /* Outputs for Enabled SubSystem: '<Root>/output_transmitter' */
  /* DataTypeConversion: '<Root>/Cast To Boolean' incorporates:
   *  Constant: '<Root>/Constant1'
   *  MATLABSystem: '<Root>/input_gps'
   * */
  warning_system_output_transmitter(warning_system_M, (warning_system_B.transmit
    != 0), warning_system_B.gyro_x, warning_system_B.gyro_y,
    warning_system_B.gyro_z, warning_system_B.VEHICLE_STATUS,
    warning_system_P.Constant1_Value, &warning_system_B.rtb_writing_flag_k,
    &warning_system_DW.output_transmitter);

  /* End of Outputs for SubSystem: '<Root>/output_transmitter' */
  rate_scheduler();
}

/* Model initialize function */
void warning_system_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    real_T gyro_x;
    real_T gyro_y;
    real_T gyro_z;
    ITC_status rtb_writing_flag;

    /* SystemInitialize for Atomic SubSystem: '<Root>/input_transmitter' */
    warning_system_input_transmitter_Init(&warning_system_DW.input_transmitter,
      &warning_system_P.input_transmitter);

    /* End of SystemInitialize for SubSystem: '<Root>/input_transmitter' */

    /* SystemInitialize for Chart: '<Root>/input_mpu6050' */
    warning_system_input_mpu6050_Init
      (&warning_system_B.SignalConversion_BusCreator1.X,
       &warning_system_B.SignalConversion_BusCreator1.Z,
       &warning_system_B.SignalConversion_BusCreator1.Y, &gyro_x, &gyro_y,
       &gyro_z, &warning_system_DW.sf_input_mpu6050);

    /* SystemInitialize for Chart: '<Root>/core_logic' */
    warning_system_core_logic_Init(&warning_system_B.transmit,
      &warning_system_B.delta, &warning_system_B.acc_offset,
      &warning_system_B.acc_calibrated, &warning_system_B.VEHICLE_STATUS,
      &warning_system_B.sf_core_logic, &warning_system_DW.sf_core_logic,
      &warning_system_P.sf_core_logic);

    /* SystemInitialize for Enabled SubSystem: '<Root>/output_transmitter' */
    warning_system_output_transmitter_Init(&rtb_writing_flag,
      &warning_system_DW.output_transmitter,
      &warning_system_P.output_transmitter);

    /* End of SystemInitialize for SubSystem: '<Root>/output_transmitter' */

    /* Start for MATLABSystem: '<Root>/input_gps' */
    /*  Constructor */
    warning_system_DW.obj_f.matlabCodegenIsDeleted = false;
    warning_system_DW.obj_f.SampleTime = warning_system_P.TS_GPS;
    warning_system_DW.obj_f.isInitialized = 1;

    /*         %% Define output properties */
    /*   Check the input size */
    setupFunctionGPS_Parser();
    warning_system_DW.obj_f.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Serial Transmit' */
    warning_system_DW.obj.matlabCodegenIsDeleted = false;
    warning_system_DW.obj.isInitialized = 1;
    warning_system_DW.obj.port = 0.0;
    warning_system_DW.obj.dataSizeInBytes = 1.0;
    warning_system_DW.obj.dataType = 0.0;
    warning_system_DW.obj.sendModeEnum = 0.0;
    warning_system_DW.obj.sendFormatEnum = 0.0;
    MW_SCI_Open(0);
    warning_system_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void warning_system_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/input_transmitter' */
  warning_system_input_transmitter_Term(&warning_system_DW.input_transmitter);

  /* End of Terminate for SubSystem: '<Root>/input_transmitter' */

  /* Terminate for Chart: '<Root>/input_mpu6050' */
  warning_system_input_mpu6050_Term(&warning_system_DW.sf_input_mpu6050);

  /* Terminate for Chart: '<Root>/core_logic' */
  warning_system_core_logic_Term(&warning_system_DW.sf_core_logic);

  /* Terminate for MATLABSystem: '<Root>/input_gps' */
  if (!warning_system_DW.obj_f.matlabCodegenIsDeleted) {
    warning_system_DW.obj_f.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/input_gps' */

  /* Terminate for MATLABSystem: '<S1>/Serial Transmit' */
  if (!warning_system_DW.obj.matlabCodegenIsDeleted) {
    warning_system_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Serial Transmit' */

  /* Terminate for Enabled SubSystem: '<Root>/output_transmitter' */
  warning_system_output_transmitter_Term(&warning_system_DW.output_transmitter);

  /* End of Terminate for SubSystem: '<Root>/output_transmitter' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

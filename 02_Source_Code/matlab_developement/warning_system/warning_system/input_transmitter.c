/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_transmitter.c
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

#include "input_transmitter.h"
#include "warning_system_types.h"
#include "rtwtypes.h"
#include <string.h>
#include "rt_nonfinite.h"
#include <stddef.h>

/* System initialize for atomic system: '<Root>/input_transmitter' */
void warning_system_input_transmitter_Init(DW_input_transmitter_warning_system_T
  *localDW, P_input_transmitter_warning_system_T *localP)
{
  int32_T i;

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
  for (i = 0; i < 15; i++) {
    localDW->UnitDelay_DSTATE[i] = localP->UnitDelay_InitialCondition;
  }

  /* End of InitializeConditions for UnitDelay: '<S5>/Unit Delay' */

  /* Start for MATLABSystem: '<S5>/I2C Read' */
  localDW->obj.DefaultMaximumBusSpeedInHz = 400000.0;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  localDW->obj.BusSpeed = 100000U;
  MW_I2C_SetBusSpeed(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 100000U);
  localDW->obj.isSetupComplete = true;
}

/* Output and update for atomic system: '<Root>/input_transmitter' */
void warning_system_input_transmitter(VSP *rty_FOREIGN_GPS, boolean_T
  *rty_Status, DW_input_transmitter_warning_system_T *localDW,
  P_input_transmitter_warning_system_T *localP)
{
  real32_T rtb_latitude;
  real32_T rtb_longitude;
  real32_T rtb_speed_o;
  uint16_T rtb_zigbeeAddress;
  uint8_T output_raw[15];

  /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
   *  UnitDelay: '<S5>/Unit Delay'
   */
  memcpy((void *)&rtb_latitude, (void *)&localDW->UnitDelay_DSTATE[0], (size_t)1
         * sizeof(real32_T));
  memcpy((void *)&rtb_longitude, (void *)&localDW->UnitDelay_DSTATE[4], (size_t)
         1 * sizeof(real32_T));
  memcpy((void *)&rtb_speed_o, (void *)&localDW->UnitDelay_DSTATE[8], (size_t)1 *
         sizeof(real32_T));
  memcpy((void *)&rtb_zigbeeAddress, (void *)&localDW->UnitDelay_DSTATE[12],
         (size_t)1 * sizeof(uint16_T));

  /* DataTypeConversion: '<S5>/Cast To Boolean' incorporates:
   *  Constant: '<S5>/Constant1'
   *  MATLAB Function: '<S5>/MATLAB Function'
   *  RelationalOperator: '<S5>/Relational Operator'
   *  Sum: '<S5>/Sum of Elements'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  *rty_Status = (((uint32_T)(localP->Constant1_Value[0] ==
    localDW->UnitDelay_DSTATE[14]) + (uint32_T)(localP->Constant1_Value[1] ==
    localDW->UnitDelay_DSTATE[14])) + (uint32_T)(localP->Constant1_Value[2] ==
    localDW->UnitDelay_DSTATE[14]) != 0U);

  /* Switch: '<S5>/Switch' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion2'
   *  RelationalOperator: '<S5>/IsNaN'
   */
  if (rtIsNaN(rtb_latitude)) {
    /* BusCreator generated from: '<S5>/Signal Conversion' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rty_FOREIGN_GPS->lat = localP->Constant_Value;
  } else {
    /* BusCreator generated from: '<S5>/Signal Conversion' */
    rty_FOREIGN_GPS->lat = rtb_latitude;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Switch: '<S5>/Switch1' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion3'
   *  RelationalOperator: '<S5>/IsNaN1'
   */
  if (rtIsNaN(rtb_longitude)) {
    /* BusCreator generated from: '<S5>/Signal Conversion' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rty_FOREIGN_GPS->lng = localP->Constant_Value;
  } else {
    /* BusCreator generated from: '<S5>/Signal Conversion' */
    rty_FOREIGN_GPS->lng = rtb_longitude;
  }

  /* End of Switch: '<S5>/Switch1' */

  /* Switch: '<S5>/Switch2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion4'
   *  RelationalOperator: '<S5>/IsNaN2'
   */
  if (rtIsNaN(rtb_speed_o)) {
    /* BusCreator generated from: '<S5>/Signal Conversion' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rty_FOREIGN_GPS->speed = localP->Constant_Value;
  } else {
    /* BusCreator generated from: '<S5>/Signal Conversion' */
    rty_FOREIGN_GPS->speed = rtb_speed_o;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* BusCreator generated from: '<S5>/Signal Conversion' incorporates:
   *  MATLAB Function: '<S5>/MATLAB Function'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  rty_FOREIGN_GPS->address = rtb_zigbeeAddress;
  rty_FOREIGN_GPS->status = localDW->UnitDelay_DSTATE[14];

  /* MATLABSystem: '<S5>/I2C Read' incorporates:
   *  UnitDelay: '<S5>/Unit Delay'
   */
  MW_I2C_MasterRead(localDW->obj.I2CDriverObj.MW_I2C_HANDLE, 60U, &output_raw[0],
                    15U, false, false);
  memcpy((void *)&localDW->UnitDelay_DSTATE[0], (void *)&output_raw[0], (size_t)
         15 * sizeof(uint8_T));
}

/* Termination for atomic system: '<Root>/input_transmitter' */
void warning_system_input_transmitter_Term(DW_input_transmitter_warning_system_T
  *localDW)
{
  /* Terminate for MATLABSystem: '<S5>/I2C Read' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      MW_I2C_Close(localDW->obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/I2C Read' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

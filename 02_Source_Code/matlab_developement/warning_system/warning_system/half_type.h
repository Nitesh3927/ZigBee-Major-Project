/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: half_type.h
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

#ifndef HALF_TYPE_H
#define HALF_TYPE_H
#include "rtwtypes.h"

/* Utility function */
uint32_T getBitfieldFromFloat(real32_T a);
real32_T getFloatFromBitfield(uint32_T a);

/* C type definition */
typedef struct {
  uint16_T bitPattern;
} half_t;

typedef half_t real16_T;

/* Complex type definition for half_t */
typedef struct {
  real16_T re;
  real16_T im;
} creal16_T;

/* Utility function for half and bit pattern conversion */
uint16_T getBitfieldFromHalf(real16_T a);
real16_T getHalfFromBitfield(uint16_T a);

/* Data Type Conversion */
real32_T halfToFloat(real16_T a);
real_T halfToDouble(real16_T a);
real16_T floatToHalf(real32_T a);
real16_T doubleToHalf(real_T a);

#endif                                 /* HALF_TYPE_H */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

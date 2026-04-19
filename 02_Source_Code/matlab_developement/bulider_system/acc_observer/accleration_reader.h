/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void stepFunctionaccleration_reader(double * acc_x,int size_vector_1,double * acc_y,int size_vector_2,double * acc_z,int size_vector_3);
    void setupFunctionaccleration_reader(uint8_T  ACCEL_RANGE,int size_vector__1,boolean_T  ENABLE_GYRO,int size_vector__2,uint8_T  DLPF_SETTING,int size_vector__3);
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif
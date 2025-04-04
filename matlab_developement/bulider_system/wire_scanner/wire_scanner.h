/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void stepFunctionwire_scanner(uint32_T * i2c_slaves,int size_vector_1);
    void setupFunctionwire_scanner();
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif
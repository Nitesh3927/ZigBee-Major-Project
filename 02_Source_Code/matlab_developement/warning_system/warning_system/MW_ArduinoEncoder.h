/* Copyright 2021 The MathWorks, Inc. */
#ifndef _MW_ARDUINO_ENCODER_H_
#define _MW_ARDUINO_ENCODER_H_
#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
//FOR Rapid accel
#else
#include <stdlib.h>
#include <stdio.h>
#endif
#include <inttypes.h>
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C"
{
#endif

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
//For Rapid accel -- do nothing
#define MW_EncoderSetup(InputA, InputB, Index) 0
#define MW_EncoderRead(Index, duration) 0
#define MW_EncoderReset(Index) 0
#define MW_EncoderRelease() 0  
    
#else
// C-code interface
int MW_EncoderSetup(uint8_T InputA, uint8_T InputB, uint8_T* Index);
int MW_EncoderRead(uint8_T Index, int32_T *duration);
int MW_EncoderReset(uint8_T Index);
int MW_EncoderRelease();    
#endif

#ifdef __cplusplus
}
#endif
#endif 

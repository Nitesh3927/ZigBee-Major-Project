/* Copyright 2023 The MathWorks, Inc. */
#ifndef _MW_NEOPIXEL_H_
#define _MW_NEOPIXEL_H_
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
    #endif
    #if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
    /* This will be run in Rapid Accelerator Mode */
    #define NeoPixel_Init(a,b,c,d)         (0)
    #define NeoPixel_Step(a,b,c,d,e,f,g)        (0)
    #define NeoPixel_reset(a)       (0)
    #else
    void NeoPixel_Init(uint16_T numPixels,uint8_T pin,uint16_T pixelType,uint8_T *index);
    void NeoPixel_Step(uint8_T index,uint16_T numPixels,uint8_T numLeds,uint8_T brightness,uint8_T *RGBColor,uint8_T *ledNum,uint8_T length);
    void NeoPixel_reset(uint8_T index);
    #endif
    #ifdef __cplusplus
}
#endif
#endif //_MW_NEOPIXEL_H_
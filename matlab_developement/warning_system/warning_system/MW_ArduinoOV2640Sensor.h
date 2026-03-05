/*
 *
/* Copyright 2023 The MathWorks, Inc. */
#ifndef _MW_ARDUINOOV2640SENSOR_H
#define _MW_ARDUINOOV2640SENSOR_H
#include <inttypes.h>
#include "rtwtypes.h"

    #ifdef __cplusplus
    extern "C" {
    #endif

    #if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
    /* This will be run in Rapid Accelerator Mode */
    #define MW_ArduinoOV2640Sensor_Init(a,b) (0)
    #define MW_ArduinoOV2640Sensor_Step(a, b, c, d, e, f)  (0)
    #else
    void MW_ArduinoOV2640Sensor_Init(uint8_t pid, uint8_t jpegres);
    void MW_ArduinoOV2640Sensor_Step(uint8_t captureTrigger, uint16_t captureTimeout,  uint32_t maxBuffLength, uint8_t *imgdata, uint32_t *imgdatalength, uint8_t *status);
    #endif
    #ifdef __cplusplus
}
#endif
#endif //_MW__ARDUINOOV2640SENSOR_H
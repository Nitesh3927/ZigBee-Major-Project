/*
 *
/* Copyright 2023-2024 The MathWorks, Inc. */
#ifndef _MW_ARDUINOONBOARDEEPROM_H
#define _MW_ARDUINOONBOARDEEPROM_H
#include <inttypes.h>
#include <stddef.h> /* for size_t */
#include "rtwtypes.h"

    #ifdef __cplusplus
    extern "C" {
    #endif

    #if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
    /* This will be run in Rapid Accelerator Mode */
    #define MW_EEPROMRead(a, b, c, d) (0)
    #define MW_EEPROMWrite(a, b, c) (0)
    #else
    void MW_EEPROMRead(uint16_t address, const uint8_t dataTypeEnum, const uint32_t DataLength, void *dataRef);
    void MW_EEPROMWrite(uint16_t address, uint8_t *dataInput, uint16_t s);
    #endif
    #ifdef __cplusplus
}
#endif
#endif //_MW_ARDUINOONBOARDEEPROM_H
/* Copyright 2023 The MathWorks, Inc. */
#ifndef _MW_SAMDADCREAD_H
#define _MW_SAMDADCREAD_H
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
#define initADC(a)               (0)
#define enableADCEOCInterrupt()  (0)
#define mw_readADC(a)            (0)

#else
void initADC(uint8_T *pins);
void enableADCEOCInterrupt(void);
void mw_readADC(uint16_T *result);
#endif

#ifdef __cplusplus
}
#endif
#endif //_MW_SAMDADCREAD_H
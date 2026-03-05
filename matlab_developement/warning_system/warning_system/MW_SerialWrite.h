/* Copyright 2015-2023 The MathWorks, Inc. */

#ifndef _MW_SERIALWRITE_H_
#define _MW_SERIALWRITE_H_
#include <inttypes.h>
#include "rtwtypes.h"
#include <stddef.h> /* for size_t */

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
 #define MW_Serial_write(a, b, c, d, e, f, g, h, i, j, k, l, m)  (0)
 #define MW_SCI_Open(a) (0)
#else
    void MW_SCI_Open(const uint8_T port);
    //void MW_Serial_write(const uint8_T port, void *dataInput, size_t s,const uint8_T dataSizeInBytes, const uint8_T sendModeEnum, const uint8_T dataType);
    void MW_Serial_write(const uint8_T port, void *dataInput, size_t s,const uint8_T dataSizeInBytes, \
                                const uint8_T sendModeEnum, const uint8_T dataType, const uint8_T sendFormatEnum, \
                                const uint8_T floatprecision, char* label, char* packageTerminator, uint8_T terminatorLength, \
                                char* packageHeader, uint8_T headerLength);
#endif
#ifdef __cplusplus
}
#endif
#endif //_MW_SERIALWRITE_H_

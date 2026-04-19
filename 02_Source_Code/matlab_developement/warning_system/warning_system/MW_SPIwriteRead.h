/*
 * Wrappers to make SPI functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2015-2023 The MathWorks, Inc. */

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
/* This will be run in Rapid Accelerator Mode */
    
    #define MW_SSpinSetup(x) (0)
    #define MW_SPIwriteReadSetup() (0)
    #define MW_SPIwriteReadLoop(a, b, c, d, e, f) (0)
#else

    #ifndef _MW_SPIWRITEREAD_H
    #define _MW_SPIWRITEREAD_H
    #include <inttypes.h>
    #include "rtwtypes.h"
   
    #ifdef __cplusplus
    extern "C" {
    #endif
    
    void MW_SSpinSetup(uint8_T slaveSelectPin);
    void MW_SPIwriteReadSetup(void);
    void MW_SPIwriteReadLoop(uint8_T spiModule, uint8_T slaveSelectPin, void *input, uint8_T datalength, uint8_T dataType,void *output);

    #ifdef __cplusplus
    }
    #endif
    #endif //_MW_SPIWRITEREAD_H
#endif
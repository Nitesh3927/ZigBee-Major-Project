/* Copyright 2023 The MathWorks, Inc. */
#ifndef _MW_ARDUINOONBOARDCAN_H_
#define _MW_ARDUINOONBOARDCAN_H_
#include <inttypes.h>
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
 #define MW_initializeOnboardCAN(a)                         (0)
 #define MW_transmitCANMessage(a,b,c,d,e,f)                 (0)
 #define MW_readCANMessage(a,b,c,d)                         (0)
 #define MW_assignCANIdAndLength(a,b,c,d)                   (0)
 #define MW_ReadLatestCANMessage(a,b,c,d,e,f,g,h)           (0)
 #define MW_terminateOnboardCAN()                           (0)
#else    
    void MW_initializeOnboardCAN(uint8_T module);
    uint8_T MW_transmitCANMessage(uint8_T module, uint32_T id, uint8_T isExtended, uint8_T dataLength, uint8_T* data, uint8_T isRemote);
    void MW_readCANMessage(uint8_T module, uint32_T id, uint8_T* data, uint8_T* status);
    void MW_assignCANIdAndLength(uint8_T module, uint32_T id,uint8_T extended,uint8_T msgLength);
    void MW_ReadLatestCANMessage(uint8_T module, uint32_T* id,uint8_T* data, uint8_T* dataLength, uint8_T* status, uint8_T* extended, uint8_T* remote, uint8_T* error);
    void MW_terminateOnboardCAN(void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_MW_ARDUINOONBOARDCAN_H_
/* Copyright 2015-2023 The MathWorks, Inc. */

#ifndef _MW_SERIALREAD_H_
#define _MW_SERIALREAD_H_
#include <inttypes.h>
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
 #define getNumbytesAvailable(a) (0)
 #define MW_Serial_read(a,b,c,d,e,f,g,h)  (0)
 #define MW_Serial_readVariableLength(a,b,c,d,e,f,g,h,i,j) (0)
 #define getCurrentTime() (0)
#else   
	int getNumbytesAvailable(const uint8_T port);
    void MW_Serial_read(const uint8_T port,const uint16_t DataSizeInBytes, char *data,uint8_T *status,\
                              char* packageTerminator, uint8_T terminatorLength, char* packageHeader, uint8_T headerLength);
    void MW_Serial_readVariableLength(const uint8_T port,const uint16_t DataSizeInBytes, char *data,uint8_T *status,\
                              char* packageTerminator, uint8_T terminatorLength, char* packageHeader, uint8_T headerLength, \
                              const uint16_T timeout, uint8_T dataTypeWidth);
	uint32_t getCurrentTime();
#endif

#ifdef __cplusplus
}
#endif
#endif //_MW_SERIALREAD_H_

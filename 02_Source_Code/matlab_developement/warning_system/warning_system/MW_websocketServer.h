/* 
 * Wrappers to make websocket server api calls with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2020 The MathWorks, Inc. */
#ifndef _MW_WEBSOCKETSERVER_H_
#define _MW_WEBSOCKETSERVER_H_

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include "rtwtypes.h"

#define DATA_SEND_RECEIVE_CLIENT     ((uint8_T)0)
#define NOT_CONNECTED_TO_CLIENT      ((uint8_T)1)

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
    #define MW_websocketServerInit()     (0)
    #define MW_websocketServerSend(a)    (0)
	#define MW_doubleToString(a,b,c)         (0)
	#define MW_unsignedToString(a,b,c)       (0)
	#define MW_signedToString(a,b,c)         (0)
    #define MW_websocketServerReceive()  (0)
    #define MW_getPortData(a,b,c)          (0)
    #define MW_websocketConnClose()      (0)
#else
    void MW_websocketServerInit();
    void MW_websocketServerSend(const char* data);
	void MW_doubleToString(char_T *chr, uint8_T *len, double val);
	void MW_unsignedToString(char_T *chr, uint8_T *len, uint32_T val);
	void MW_signedToString(char_T *chr, uint8_T *len, int32_T val);
    uint8_t MW_websocketServerReceive();
    uint8_t MW_getPortData(double *data, uint8_t sigNum, uint8_t dataSize);
    void MW_websocketConnClose();
#endif
#ifdef __cplusplus
}
#endif
#endif //_MW_WEBSOCKETSERVER_H

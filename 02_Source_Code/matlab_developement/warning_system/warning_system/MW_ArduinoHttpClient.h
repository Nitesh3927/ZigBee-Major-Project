/*
 *
/* Copyright 2022-2024 The MathWorks, Inc. */
#ifndef _MW_ARDUINOHTTPCLIENT_H
#define _MW_ARDUINOHTTPCLIENT_H
    #if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
    /* This will be run in Rapid Accelerator Mode */
        #define MW_HTTPClientSetup() (0)
        #define MW_HTTPClientStep(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,q,r) (0)
        #define MW_getCurrentTimeInMillisHttp() (0)
    #else

        #include "peripheralIncludes.h"

        #include <inttypes.h>
        #include "rtwtypes.h"
        #ifdef __cplusplus
        extern "C" {
        #endif

        void MW_HTTPClientSetup();
        uint8_t MW_HTTPClientStep(char* httpMethod, char* uri, uint8_t doInput, uint8_t doOutput, char* payload, char* contentType, char* accept, \
                                         uint32_t responseStringMaxLength, char* response, uint32_t *responseSize, uint8_t numCustomHeaders, \
                                         char* header1Key, char* header1Value, \
                                         char* header2Key, char* header2Value, \
                                         char* header3Key, char* header3Value);
        uint32_T MW_getCurrentTimeInMillisHttp();
        #ifdef __cplusplus
        }
        #endif

     #endif
#endif //_MW_ARDUINOHTTPCLIENT_H
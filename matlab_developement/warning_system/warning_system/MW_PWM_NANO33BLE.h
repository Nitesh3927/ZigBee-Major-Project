//Header file for Arduino NANO 33 BLE PWM 
//Copyrights 2020 The MathWorks, Inc.

#ifndef _MW_PWM_NANO33BLE_H_
#define _MW_PWM_NANO33BLE_H_
#include <inttypes.h>
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
/* This will be run in Rapid Accelerator Mode */

    #define MW_NANO33BLE_analogWrite_1(pin,val,period) (0)
    #define MW_NANO33BLE_PWM_Handler() (0)
    #define MW_NANO33BLE_PWM_Setup() (0)
#else
  
   void MW_NANO33BLE_analogWrite_1(pin_size_t pin, uint32_t val, uint16_t period);
   void MW_NANO33BLE_PWM_Handler();
   void MW_NANO33BLE_PWM_Setup();

    #ifdef __cplusplus
    }
    #endif
    #endif //_MW_PWM_NANO33BLE_H_
 #endif
/* NRF52 TIMER4 based  scheduler
 * 
 * Copyright 2020 The MathWorks, Inc.
 */

#ifndef _ARDUINOARMM4MBEDSCHEDULER_H_
#define _ARDUINOARMM4MBEDSCHEDULER_H_
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
void rt_OneStep(void);
void TIMER4_IRQHandler_v(void);
void configureArduinoARMTimer(float ModelSampleTime);
void TIMER4Config(float TickTime);
boolean disable_rt_OneStep(void);
void enable_rt_OneStep(void);
boolean MW_Arduino_Loop(void);

#ifdef __cplusplus
}
#endif


#endif

/* Arduino ARM Bareboard scheduler
 * 
 * Copyright 2024 The MathWorks, Inc. 
 */ 
	
#ifndef _ARDUINOARMM4SCHEDULER_H_
#define _ARDUINOARMM4SCHEDULER_H_
	
#include "Arduino.h"
	
#ifdef _MSC_VER
#define __INLINE inline
#define __STATIC_INLINE static inline
#define __DSB()
#endif
	
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __INLINE
#endif
		
 #define DISABLE_SCHEDULER_INT()    (noInterrupts())
 #define ENABLE_SCHEDULER_INT()     (interrupts())

	
#ifdef __cplusplus
extern "C" {
#endif
	
void configureArduinoARMTimer(void);    
void Setup_SchedulerTimer(IRQn_Type irqn, uint32_t tickcounter);
boolean MW_Arduino_Loop(void);
void SysTick_Handler(void);
void rt_OneStep(void);
boolean disable_rt_OneStep(void);
void enable_rt_OneStep(void);
	
#ifdef __cplusplus
}
#endif
	
#endif // _ARDUINOARMSCHEDULER_H_
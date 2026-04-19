/* Arduino ARM M0+ Bareboard RP2040 scheduler
 * 
 * Copyright 2024 The MathWorks, Inc. 
 */ 

#ifndef _ARDUINOARM_M0PLUS_RP2040_SCHEDULER_H_
#define _ARDUINOARM_M0PLUS_RP2040_SCHEDULER_H_

#include "Arduino.h"
#include <hardware/timer.h>
#include <hardware/irq.h>

#ifdef _MSC_VER
#define __INLINE inline
#define __STATIC_INLINE static inline
#define __DSB()
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __INLINE
#endif


#if defined(_ARDUINO_RP2040_ALARM_1_)
	#define ID_FOR_ALARM1 1    
    #define TIMER_ID_FOR_ALARM1 TIMER_IRQ_1
	#if (defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_RASPBERRY_PI_PICO))
    #define IRQn_FOR_ALARM1 TIMER_IRQ_1_IRQn
    #else
    #define IRQn_FOR_ALARM1  TIMER_IRQ_1n
    #endif
	#define HANDLER_FOR_ALARM1  ALARM1_Handler
#endif

 #define DISABLE_SCHEDULER_INT()    (noInterrupts())
 #define ENABLE_SCHEDULER_INT()     (interrupts())


#ifdef __cplusplus
extern "C" {
#endif

void configureArduinoARM_M0plus_RP2040_Alarm(void);    
void Setup_SchedulerAlarm(uint8_t alarmId, int timerIdforAlarm, IRQn_Type irqn, uint32_t alarmResolution);
void arm_alarm(uint8_t alarmId,uint32_t alarmResolution);
boolean MW_Arduino_Loop(void);
void rt_OneStep(void);
boolean disable_rt_OneStep(void);
void enable_rt_OneStep(void);
__attribute__ ((naked,aligned(4))) void SVC_Handler(void);
#ifdef __cplusplus
}
#endif

#endif // _ARDUINOARM_M0PLUS_RP2040_SCHEDULER_H_

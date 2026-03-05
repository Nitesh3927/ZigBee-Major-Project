/* Arduino ARM Bareboard scheduler
 * 
 * Copyright 2023-2024 The MathWorks, Inc. 
 */ 

#ifndef _ARDUINOARMM7SCHEDULER_H_
#define _ARDUINOARMM7SCHEDULER_H_
//#include <stdint.h>
#include "Arduino.h"

typedef uint32_t IRQn_Type; 

#define MW_ASM    __asm volatile
#define MW_STATIC_INLINE  static inline
#define MW_NAKED_ATTRIBUTE  __attribute__ ((naked))
#define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
__STATIC_FORCEINLINE void __set_BASEPRI(uint32_t basePri)
{
  MW_ASM ("MSR basepri, %0" : : "r" (basePri) : "memory");
}
__STATIC_FORCEINLINE void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}
__STATIC_FORCEINLINE void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}

MW_STATIC_INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return ((uint32_t)(NVIC_GET_PRIORITY(IRQn)));
  }
  else
  {
    return(((uint32_t)((volatile uint8_t*)&(SCB_SHPR1))[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}

#if (defined(MW_TIMERID) && (MW_TIMERID == 60))
#define _ARDUINO_TEENSY_GPT_
#endif



#if defined(_ARDUINO_TEENSY_GPT_)
	#define TC_FOR_GPT       IMXRT_GPT2
	#define IRQn_FOR_GPT     IRQ_GPT2
#endif


 #define DISABLE_SCHEDULER_INT()    cli()
 #define ENABLE_SCHEDULER_INT()     sei()


#ifdef __cplusplus
extern "C" {
#endif

void configureArduinoARMTimer(void);    
void Setup_SchedulerTimer(uint32_t irqn, uint32_t tickcounter);
boolean MW_Arduino_Loop(void);
void rt_OneStep(void);
void disable_rt_OneStep(void);
void enable_rt_OneStep(void);

#ifdef __cplusplus
}
#endif

#endif // _ARDUINOARMSCHEDULER_H_

/* Copyright 2024 The MathWorks, Inc. */

#include "IRQManager.h"
#include "FspTimer.h"
extern "C" {
       #include "cm_backtrace/cm_backtrace.h"
    }
    
/* TODO: make me configurable by the variant */
extern const uint32_t __StackTop;
const uint32_t APPLICATION_VECTOR_TABLE_ADDRESS_RAM = (uint32_t)&__StackTop;

void _init() {
   R_BSP_PinAccessEnable();
}

volatile uint32_t *irq_vector_table;
//void startAgt(void);

extern uint32_t __ROM_Start;
extern const fsp_vector_t __VECTOR_TABLE[];
extern const fsp_vector_t g_vector_table[];


#if FSP_PRIV_TZ_USE_SECURE_REGS

#define BSP_PRV_BITS_PER_WORD    (32)

void unsecure_registers() {

    /* Unprotect security registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

 #if !BSP_TZ_SECURE_BUILD
    /* Set the DMAC channels to secure access. */
    R_CPSCU->ICUSARC = ~R_CPSCU_ICUSARC_SADMACn_Msk;
 #endif

    /* Place all vectors in non-secure state unless they are used in the secure project. */
    uint32_t interrupt_security_state[BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD];
    memset(&interrupt_security_state, UINT8_MAX, sizeof(interrupt_security_state));

    for (size_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES; i++)
    {
         /* This is a secure vector. Clear the associated bit. */
         uint32_t index = i / BSP_PRV_BITS_PER_WORD;
         uint32_t bit   = i % BSP_PRV_BITS_PER_WORD;
         interrupt_security_state[index] &= ~(1U << bit);
    }

    /* The Secure Attribute managed within the ARM CPU NVIC must match the security attribution of IELSEn
     * (Reference section 13.2.9 in the RA6M4 manual R01UH0890EJ0050). */
    uint32_t volatile * p_icusarg = &R_CPSCU->ICUSARG;
    for (size_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD; i++)
    {
        p_icusarg[i]  = interrupt_security_state[i];
        NVIC->ITNS[i] = interrupt_security_state[i];
    }

    /* Protect security registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
}
#endif

#define stringify(s) str(s)
#define str(s) #s

extern "C" void Stacktrace_Handler(void);

#ifdef BACKTRACE_SUPPORT
/* for printf compatibility */
extern "C" __attribute__((weak)) int _write (int fhdl, const void *buf, size_t count) {
  (void)fhdl;
  return Serial.write_raw((uint8_t*)buf, count);
}
#endif
//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) {
   (void)func;
   return 0;
}

namespace __gnu_cxx {
   void __verbose_terminate_handler() { }
}
extern "C" __attribute__((weak)) void __cxa_pure_virtual(void);
extern "C" __attribute__((weak)) void __cxa_pure_virtual(void)
{
   exit(1);
}


// this file implements the following public funcions: delay, delayMicroseconds, yield, millis, micros

__attribute__((weak)) void delay(uint32_t ms) {
	R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
}

void delayMicroseconds(unsigned int us) {
	R_BSP_SoftwareDelay(us, BSP_DELAY_UNITS_MICROSECONDS);
}

__attribute__((weak)) void yield() {
}

static FspTimer   agt_timer;
volatile uint32_t agt_time_ms = 0;

static void timer_micros_callback(timer_callback_args_t __attribute((unused))* p_args) {
	agt_time_ms += 1;
}

void startAgt() {
	// configure AGT timer 0 to generate an underflow interrupt every 1 ms
	// a clock divider 8 works for both the Uno R4 and Portenta C33 because number of clock ticks 
	// in 1 ms (period) is an integer number and below the 16-bit counter limit
	// on the Uno R4 the AGT clock is 24 MHz / 8 -> 3000 ticks per ms
	// on the Portenta C33 the AGT clock is 50 Mhz / 8 -> 6250 ticks per ms
	const uint32_t clock_freq_Hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
	const uint32_t period = clock_freq_Hz / ((1 << TIMER_SOURCE_DIV_8) * 1000UL);
	agt_timer.begin(/* mode */ TIMER_MODE_PERIODIC,
                  /* type */ AGT_TIMER,
                  /* channel */ 0,
                  period,
                  /* pulse */ 1,
                  TIMER_SOURCE_DIV_8,
                  timer_micros_callback);;
	agt_timer.setup_overflow_irq(8);
	agt_timer.open();
	agt_timer.start(); // bug in R4 1.0.2: calling start() is not necessary: open() starts the counter already !?
}

unsigned long millis()
{
#ifdef AZURE_RTOS_THREADX
	return tx_time_get();
#else
	return agt_time_ms;
#endif
}

unsigned long micros() {
	// Return time in us
	const timer_cfg_t* cfg = agt_timer.get_cfg();
	NVIC_DisableIRQ(cfg->cycle_end_irq);
	uint32_t ms = agt_time_ms;
	// read from the R_AGT0 registers directly for performance reasons
	uint32_t const down_counts = R_AGT0->AGT; // get the counter value
	if (R_AGT0->AGTCR_b.TUNDF && (down_counts > (cfg->period_counts / 2))) {
		// if the TUNDF (underflow) bit is set, the counter wrapped around 
		// just before down_counts was read and agt_time_ms was not yet updated
		++ms;
	}
	NVIC_EnableIRQ(cfg->cycle_end_irq);
	uint32_t const up_counts = (cfg->period_counts - 1) - down_counts;
	return  (ms * 1000) + ((up_counts * 1000) / cfg->period_counts);
}

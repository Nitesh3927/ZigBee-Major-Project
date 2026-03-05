/* Copyright 2016-2022 The MathWorks, Inc. */
#ifndef __FREERTOS_INIT_H__
#define __FREERTOS_INIT_H__

#include <stdio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "portable.h"
#include "portmacro.h"

#include "mw_thread.h"
#include "mw_semaphore.h"
#include "mw_timer.h"

/* ---------------------------- */
/* Required Coder Target header */
/* ---------------------------- */
#include "MW_custom_RTOS_header.h"
#include "MW_target_hardware_resources.h"

#define CHECK_STATUS(status, expStatus, fcn)  		configASSERT((status)==(expStatus))
#define CHECK_STATUS_NOT(status, errStatus, fcn)	configASSERT((status)!=(expStatus))
    
#define getStackDepth(x) ((x/sizeof(portSTACK_TYPE))>=configMINIMAL_STACK_SIZE ? (x/sizeof(portSTACK_TYPE)) : configMINIMAL_STACK_SIZE)

void mw_WaitForThisEvent(int sigNo);
void mw_AddBlockForThisEvent(int sigNo);
void mw_AddHandlerForThisEvent(int sigNo, int sigToBlock[], int numSigToBlock, void *sigHandler);
void mw_RestoreHandlerForThisEvent(int sigNo);

#ifdef MW_HAS_COMM_SERVICE
void terminateCommService();
extern void runCommService();
#endif
    
#if !defined(MW_FREERTOS) && (configUSE_TRACE_FACILITY == 1)
/* The user trace event posted to the trace recording on each tick interrupt.
Note tick events will not appear in the trace recording with regular period
because this project runs in a Windows simulator, and does not therefore
exhibit deterministic behaviour. */
traceLabel xTickTraceUserEvent;
static portBASE_TYPE xTraceRunning = pdTRUE;
#endif

extern void mw_RTOSInit(float baseRatePeriod, int numSubrates);

#endif //__FREERTOS_INIT_H__

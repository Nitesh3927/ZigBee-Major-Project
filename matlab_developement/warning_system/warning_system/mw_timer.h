/* Copyright 2016 The MathWorks, Inc. */
#ifndef __MW_TIMER__H__
#define __MW_TIMER__H__
#include "FreeRTOS.h"
#include "timers.h"

typedef struct _mw_timer_t {
	TimerHandle_t   handle;
    TickType_t      period;
	UBaseType_t     autoreload;
    void *          id;
    char            name[configMAX_TASK_NAME_LEN];
} mw_timer_t;

/* Create timer */
int  mw_osTimerCreate (mw_timer_t * timer_def, TimerCallbackFunction_t funcptr);
/* Start timer */
int  mw_osTimerStart (mw_timer_t * timer_def, TickType_t xBlockTime);
/* Stop timer */
int  mw_osTimerStop (mw_timer_t * timer_def);
/* Delete timer */
int  mw_osTimerDelete (mw_timer_t * timer_def);

#endif /* __MW_TIMER__H__ */

/* Copyright 2016 The MathWorks, Inc. */
#include "mw_timer.h"

/*------------------------------------------------------------------------------------------------------*/
/*----------------------------- Timer Wrapper functions ------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
int mw_osTimerCreate(mw_timer_t * timer_def, TimerCallbackFunction_t funcptr)
{
    timer_def->handle = xTimerCreate(timer_def->name, timer_def->period, timer_def->autoreload, timer_def->id, funcptr);
    if (timer_def->handle != NULL)
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

int mw_osTimerStart(mw_timer_t * timer_def, TickType_t xBlockTime )
{
	if (timer_def!=NULL && timer_def->handle!=NULL)
    {
        return (xTimerStart(timer_def->handle, xBlockTime)!=pdPASS);
    }
    else
    {
        return 1;
    }
}

int mw_osTimerStop(mw_timer_t * timer_def)
{
	if (timer_def!=NULL && timer_def->handle!=NULL)
    {
        return (xTimerStop(timer_def->handle, 500000)!=pdPASS);
    }
    else
    {
        return 1;
    }
}

int mw_osTimerDelete(mw_timer_t * timer_def)
{
	if (timer_def!=NULL && timer_def->handle!=NULL)
    {
        return (xTimerDelete(timer_def->handle, 500000)!=pdPASS);
    }
    else
    {
        return 1;
    }
}

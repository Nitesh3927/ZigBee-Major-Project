/* Copyright 2016 The MathWorks, Inc. */
#include "mw_thread.h"

#define _unused(x) ((void)(x))

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------- Thread functions -----------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/* Create a thread and add it to Active Threads and set it to state READY. */
int mw_osThreadCreate(mw_thread_t * aThread, TaskFunction_t aTaskFunction, void *aFcnParamter)
{
	if( aThread==NULL )
    {
        return 1;
    }
    else
    {
        BaseType_t out = xTaskCreate(aTaskFunction, aThread->name, aThread->stackdepth, aFcnParamter, aThread->priority, &(aThread->taskhandle));	
        configASSERT( aThread->taskhandle );
        return (out!=pdPASS);
    }
}

/* Return the thread handle of the current running thread.  */
TaskHandle_t mw_osThreadGetId   (void)
{
#if ( INCLUDE_xTaskGetCurrentTaskHandle == 1 )
	return xTaskGetCurrentTaskHandle();
#else
    return NULL;
#endif
}

/* Terminate execution of a thread and remove it from Active Threads. */
void   mw_osThreadTerminate 	(mw_thread_t * thread_def)
{
	if (thread_def!=NULL)
    {
        vTaskDelete(thread_def->taskhandle);
    }
}

/* Change priority of an active thread. */
void  mw_osThreadSetPriority 	(mw_thread_t * thread_def, UBaseType_t  priority)
{
	if (thread_def!=NULL)
    {
        vTaskPrioritySet(thread_def->taskhandle, priority);
        thread_def->priority = priority;
    }
}

/* Get current priority of an active thread. */
UBaseType_t mw_osThreadGetPriority 	(mw_thread_t * thread_def)
{
#if INCLUDE_vTaskPriorityGet==1
    if (thread_def!=NULL)
    {
        return uxTaskPriorityGet(thread_def->taskhandle);
    }
    else
    {
        return thread_def->priority;
    }
#else
    return thread_def->priority;
#endif
}

/* Pass control to next thread that is in state READY. */
void   mw_osThreadYield 		(void)
{
	taskYIELD();
}

void   mw_osThreadExit 	(void * value_ptr)
{
    _unused(value_ptr);
#if INCLUDE_vTaskDelete /* vTaskDelete() enabled */
      vTaskDelete(NULL);
#endif
}

int   mw_osThreadJoin 	(mw_thread_t thread_def, void ** value_ptr)
{
    _unused(value_ptr);
    _unused(thread_def);
#if INCLUDE_vTaskDelete /* vTaskDelete() enabled */
      vTaskDelete(thread_def.taskhandle);
      return 0;
#else
      return 1; /* vTaskDelete() not available */
#endif
}

void   mw_osThreadSleep 	(const long msToDelay )
{
	vTaskDelay( (TickType_t) msToDelay/portTICK_PERIOD_MS );
}

/* Copyright 2016 The MathWorks, Inc. */
#ifndef __MW_THREAD__H__
#define __MW_THREAD__H__

#include "FreeRTOS.h"
#include "task.h"

#ifndef INCLUDE_vTaskPriorityGet 
#define INCLUDE_vTaskPriorityGet 1
#endif

typedef struct _mw_thread_t{
	char            name[configMAX_TASK_NAME_LEN];
    UBaseType_t     priority;
	unsigned short  stackdepth;
	TaskHandle_t    taskhandle;
} mw_thread_t;


/* Create a thread and add it to Active Threads and set it to state READY. */
int    mw_osThreadCreate        (mw_thread_t * aTaskHandle, TaskFunction_t aTaskFunction, void *aFcnParamter);
/* Return the thread ID of the current running thread.  */
TaskHandle_t  mw_osThreadGetId 	(void);
/* Terminate execution of a thread and remove it from Active Threads. */
void   mw_osThreadTerminate 	(mw_thread_t * thread_def);
/* Change priority of an active thread. */
void   mw_osThreadSetPriority 	(mw_thread_t * thread_def, UBaseType_t priority);
/* Get current priority of an active thread. */
UBaseType_t mw_osThreadGetPriority 	(mw_thread_t * thread_def);
/* Pass control to next thread that is in state READY. */
void   mw_osThreadYield 		(void);
/* Exit from thread */
void   mw_osThreadExit          (void * value_ptr);
/* Join */
int    mw_osThreadJoin          (mw_thread_t thread_def, void ** value_ptr);
/* Delay a thread for a certain no of milliseconds */
void   mw_osThreadSleep         (const long msToDelay);
#endif /* __MW_THREAD__H__ */

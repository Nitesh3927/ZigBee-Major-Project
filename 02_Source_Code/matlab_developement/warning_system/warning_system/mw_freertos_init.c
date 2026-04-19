/* Copyright 2016-2022 The MathWorks, Inc. */


/* ---------------------------- */
/* RTOS-specific headers        */
/* Note: must be included first */
/* ---------------------------- */
#include "mw_freertos.h"

/* ---------------------------- */
/* Other headers                */
/* ---------------------------- */
#include <string.h>

/* ---------------------------- */
/* RTOS-specific declarations   */
/* ---------------------------- */

/* Other declarations */
#define _unused(x) ((void)(x))

/* Note: stdint.h is included in FreeRTOS.h
 * If stdint.h cannot be located then:
 *   + If using GCC ensure the -nostdint options is *not* being used.
 *   + Ensure the project's include path includes the directory in which your
 *     compiler stores stdint.h.
 *   + Set any compiler options necessary for it to support C99, as technically
 *     stdint.h is only mandatory with C99 (FreeRTOS does not require C99 in any
 *     other way).
 *   + The FreeRTOS download includes a simple stdint.h definition that can be
 *     used in cases where none is provided by the compiler.  The files only
 *     contains the typedefs required to build FreeRTOS.  Read the instructions
 *     in FreeRTOS/source/stdint.readme for more information.
 */

/* Scheduler timer */
mw_timer_t mw_scheduler_timer_def;
int32_t mw_timer_id;

#ifndef MW_EXTMODE_STACKSIZE
#define MW_EXTMODE_STACKSIZE 10240
#endif

/* Scheduler task move base rate task from wait state to ready state */
void schedulerTask(TimerHandle_t arg)
{
    _unused(arg);
#ifdef DETECT_OVERRUNS
    testForRateOverrun(0);
#endif
    /* Release base rate semaphore to move base rate task from wait state to ready state */
    mw_osSemaphoreRelease(&baserateTaskSem);
}

/* ---------------------------- */
/* Externally visible functions */
/* ---------------------------- */
void mw_WaitForThisEvent(int sigNo)
{
    _unused(sigNo);
}

void mw_AddBlockForThisEvent(int sigNo)
{
    _unused(sigNo);
}

void mw_AddHandlerForThisEvent(int sigNo, int sigToBlock[], int numSigToBlock, void *sigHandler)
{
    _unused(sigNo);
    _unused(sigToBlock);
    _unused(numSigToBlock);
    _unused(sigHandler);
}

void mw_RestoreHandlerForThisEvent(int sigNo)
{
}

void baseRateTaskWrapper(void *arg)
{
    baseRateTask(arg);
}
#ifdef MW_HAS_MULTIPLE_RATES
void subrateTaskWrapper(void *arg)
{
    subrateTask(arg);
}
#endif

void mw_RTOSInit(float baseRatePeriod, int numSubrates)
{
    int32_t status;
#ifdef MW_HAS_MULTIPLE_RATES
    int i;
#endif
/* MW_FREERTOS is only defined for STM32 CubeMX target. Remove the guard MW_FREERTOS after the Trace source code is shipped for STM32 CubeMX target*/  
#if  !defined(MW_FREERTOS) && ( configUSE_TRACE_FACILITY == 1 )
    /* Initialise the trace recorder and create the label used to post user
     events to the trace recording on each tick interrupt. */
    vTraceInitTraceData();
    xTickTraceUserEvent = xTraceOpenLabel( "tick" );
    /* Start the trace recording */
    uiTraceStart();
#endif
    
    /* Create semaphore for base rate task */
    status = mw_osSemaphoreCreate(&baserateTaskSem, 0);
    CHECK_STATUS(status, 0, "mw_osSemaphoreCreate:baserateTaskSem");
    /* Create semaphore for stop task */
    status = mw_osSemaphoreCreate(&stopSem, 0);
    CHECK_STATUS(status, 0, "mw_osSemaphoreCreate:stopSem");
    
    /* Create baseRateTask thread */
    baseRateThread.priority = ( MW_BASERATE_PRIORITY );
    baseRateThread.taskhandle = NULL;
    baseRateThread.stackdepth = getStackDepth(OS_STKSIZE);
    strcpy(baseRateThread.name,"Baserate");
    status = mw_osThreadCreate(&baseRateThread, &baseRateTaskWrapper, NULL);
    CHECK_STATUS(status, 0, "mw_osThreadCreate");
    
#ifdef MW_HAS_MULTIPLE_RATES
    for (i = 0; i < MW_NUMBER_SUBRATES; i++) {
        taskId[i] = i;
        status = mw_osSemaphoreCreate(&subrateTaskSem[i], 0);
        CHECK_STATUS(status, 0,"mw_osSemaphoreCreate");
        /* Initialize thread structure */
        subRateThread[i].priority = MW_BASERATE_PRIORITY - (i+1);
#ifdef MW_NEEDS_BACKGROUND_TASK
        CHECK_STATUS(subRateThread[i].priority>(tskIDLE_PRIORITY+1), 1, "Too many rates");
#else
        CHECK_STATUS(subRateThread[i].priority>tskIDLE_PRIORITY, 1, "Too many rates");
#endif
        subRateThread[i].taskhandle = NULL;
        subRateThread[i].stackdepth = getStackDepth(OS_STKSIZE);
        status = mw_osThreadCreate(&subRateThread[i], &subrateTaskWrapper, (void *)&taskId[i]);
        
        CHECK_STATUS(status, 0, "mw_osThreadCreate");
#ifdef DETECT_OVERRUNS
        status = mw_osBinarySemaphoreCreate(&rateTaskFcnRunningMutex[i+1]);
        CHECK_STATUS(status, 0, "mw_osBinarySemaphoreCreate");
#endif
    }
#endif
    
    /* Set the SysTick priority */
#ifdef MW_SCHEDULER_PRIORITY
    NVIC_SetPriority((IRQn_Type)(-1), MW_SCHEDULER_PRIORITY);
#endif
    
#ifdef MW_NEEDS_BACKGROUND_TASK
    /* Create backgroundTask thread */
    backgroundThread.priority = tskIDLE_PRIORITY;
    backgroundThread.taskhandle = NULL;
    backgroundThread.stackdepth = getStackDepth(MW_EXTMODE_STACKSIZE);
    strcpy(backgroundThread.name,"Background");
    status = mw_osThreadCreate(&backgroundThread, backgroundTask, NULL);
    CHECK_STATUS(status, 0 ,"mw_osThreadCreate");
#endif
#ifdef DETECT_OVERRUNS
    status = mw_osBinarySemaphoreCreate(&rateTaskFcnRunningMutex[0]);
    CHECK_STATUS(status, 0, "mw_osBinarySemaphoreCreate");
#endif    

#ifdef MW_STANDALONE_EXECUTION_PROFILER_ON
    status = mw_osBinarySemaphoreCreate(&profilingDataStoreMutex);
    CHECK_STATUS(status, 0, "mw_osBinarySemaphoreCreate");
#endif
    
    /* Create timer to call scheduler task */
    mw_timer_id = 0;
    mw_scheduler_timer_def.handle = NULL;
    mw_scheduler_timer_def.period = (TickType_t)(baseRatePeriod*1000/portTICK_PERIOD_MS);
    mw_scheduler_timer_def.autoreload = pdTRUE;
    mw_scheduler_timer_def.id = (void *)mw_timer_id;
    strcpy(mw_scheduler_timer_def.name, "Timer1");
    status = mw_osTimerCreate(&mw_scheduler_timer_def, &schedulerTask);
    CHECK_STATUS(status, 0,"mw_osTimerCreate");
    /* Start the timer */
    status = mw_osTimerStart(&mw_scheduler_timer_def, (TickType_t )1000);
    CHECK_STATUS(status, 0,"mw_osTimerCreate");
    /* Start the real time scheduler */
    #ifndef MW_DONOTSTART_SCHEDULER
    vTaskStartScheduler();
    #endif
}

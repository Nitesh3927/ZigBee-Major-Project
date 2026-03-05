/* Copyright 2014-2016 The MathWorks, Inc. */
#ifndef __MW_SEMAPHORE__H__
#define __MW_SEMAPHORE__H__
#include "FreeRTOS.h"
#include "semphr.h"

#define SEMAPHORE_MAX_COUNT 10
#ifndef  INCLUDE_vTaskSuspend
#define  INCLUDE_vTaskSuspend 1
#endif

typedef SemaphoreHandle_t mw_semaphore_t;

/* Create and Initialize a Semaphore object used for managing resources. */
int mw_osSemaphoreCreate 	(mw_semaphore_t * semaphore_def, int32_t count);
/* Wait until a Semaphore token becomes available. */
int mw_osSemaphoreWait 	    (mw_semaphore_t * semaphore_def, uint32_t millisec);
/* Wait until a Semaphore token becomes available. */
int mw_osSemaphoreWaitEver	(mw_semaphore_t * semaphore_def);
/* Release a Semaphore token. */
int mw_osSemaphoreRelease    (mw_semaphore_t * semaphore_def);
/* Delete a Semaphore that was created by osSemaphoreCreate. */
int mw_osSemaphoreDelete 	(mw_semaphore_t * semaphore_def);

/* The functions below contain the declarations for the binary semaphore */

/* Create and Initialize a Binary Semaphore  object used for managing resources. */
int  mw_osBinarySemaphoreCreate 	(mw_semaphore_t * semaphore_def);
/* Try Wait to check if the Binary Semaphore token is available. */
int  mw_osBinarySemaphoreTryLock	(mw_semaphore_t * semaphore_def);

#endif /* __MW_SEMAPHORE__H__ */

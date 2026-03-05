/* Copyright 2016 The MathWorks, Inc. */
#include "mw_semaphore.h"

/* Create and Initialize a Semaphore object used for managing resources. */
int  mw_osSemaphoreCreate 	(mw_semaphore_t * semaphore_def, int32_t count)
{
    *semaphore_def = xSemaphoreCreateCounting( SEMAPHORE_MAX_COUNT, count);
    if (semaphore_def!=NULL)
        return 0;
    else
        return 1;
}
/* Wait until a Semaphore token becomes available. */
int  mw_osSemaphoreWait 	(mw_semaphore_t * semaphore_def, uint32_t millisec)
{
    if (semaphore_def==NULL || *semaphore_def==NULL)
        return 1;
    else
        return (xSemaphoreTake(*semaphore_def, millisec)!=pdTRUE);
}
/* Wait until a Semaphore token becomes available. */
int  mw_osSemaphoreWaitEver	(mw_semaphore_t * semaphore_def)
{
    if (semaphore_def==NULL || *semaphore_def==NULL)
        return 1;
    else
        return (xSemaphoreTake(*semaphore_def, portMAX_DELAY)!=pdTRUE);
}
/* Release a Semaphore token. */
int mw_osSemaphoreRelease  (mw_semaphore_t * semaphore_def)
{
    if (semaphore_def==NULL || *semaphore_def==NULL)
        return 1;
    else
        return (xSemaphoreGive(*semaphore_def)!=pdTRUE);
}
/* Delete a Semaphore that was created by osSemaphoreCreate. */
int mw_osSemaphoreDelete 	(mw_semaphore_t * semaphore_def)
{
    if (semaphore_def!=NULL)
    {
        vSemaphoreDelete(*semaphore_def);
        return 0;
    }
    else
    {
        return 1;
    }
}

/* The functions below contain the definitions for the binary semaphore */
/* Create and Initialize a Binary Semaphore  object used for managing resources. */
int  mw_osBinarySemaphoreCreate 	(mw_semaphore_t * semaphore_def)
{
    *semaphore_def = xSemaphoreCreateBinary();
    if (semaphore_def!=NULL)
    {
        /* The semaphore can now be used. Its handle is stored in the
        semaphore_def variable.  Calling xSemaphoreTake() on the semaphore here
        will fail until the semaphore has first been given. */
        return mw_osSemaphoreRelease (semaphore_def);
    }
    else
    { 
        /* There was insufficient OpenRTOS heap available for the semaphore to
        be created successfully. */
        return 1;
    }
}

/* Try Wait to check if the Binary Semaphore token is available. */
int  mw_osBinarySemaphoreTryLock	(mw_semaphore_t * semaphore_def)
{
    if (semaphore_def==NULL || *semaphore_def==NULL)
    {
        return 1;
    }
    else
    {
        /* See if we can obtain the semaphore.  If the semaphore is not
        available do not wait. Non-blocking with 0 ticks */
        return (xSemaphoreTake(*semaphore_def, ( TickType_t ) 0)!=pdTRUE);
    }
}

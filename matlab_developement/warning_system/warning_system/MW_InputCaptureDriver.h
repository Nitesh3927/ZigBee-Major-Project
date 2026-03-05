#ifndef _MW_INPUTCAPTUREDRIVER_H_
#define _MW_INPUTCAPTUREDRIVER_H_
#include <inttypes.h>
#include "rtwtypes.h"

#include "peripheralIncludes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
 /* This will be run in Rapid Accelerator Mode */
 #define setupInputCapture(a)                        (0)
 #define computeFrequencyAndDutycycle(a,b,c)         (0)
 #define teardownInputCapture(a)        (0)
#else

 void setupInputCapture(uint8_t icpPinNumber);
 void computeFrequencyAndDutycycle(uint8_t p, uint32_t *f, uint8_t *d);
 void teardownInputCapture(uint8_T icpPinNumber);

#endif

#ifdef __cplusplus
}
#endif
#endif //_MW_INPUTCAPTUREDRIVER_H_

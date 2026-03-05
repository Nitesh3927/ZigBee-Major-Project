/* Arduino Bareboard scheduler
 * 
 * Copyright 2013-2022 The MathWorks, Inc.
 */

#ifndef _MW_ARDUINOHWINIT_H_
#define _MW_ARDUINOHWINIT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
void MW_Arduino_Init(void);
void MW_Arduino_Terminate(void);
void MW_Modbus_Slave_Poll(void);
void onOverrunDetect(int id);
#ifdef __cplusplus
}
#endif

#endif // _MW_ARDUINOHWINIT_H_

/* LocalWords:  Bareboard
 */

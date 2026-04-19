#ifndef ARDUINO_EXTINT_LCT_H
#define ARDUINO_EXTINT_LCT_H

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
/* This will be compiled by MATLAB to create the Simulink block */
/* and for rapid accelerator mode as well */
#define attachInterrupt(a,b,c) (0)

#else

#if defined(ARDUINO_ARCH_MBED) && !defined(USE_MBEDRTOS)
// MBED core has the pinMode as a C++ construct 
// which needs to be called in a C function for c codegen
// Hence using a wrapper defined in io_wrappers.cpp
#include "io_wrappers.h"
#else
#include "Arduino.h"
#endif // ARDUINO_ARCH_MBED

#endif // ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
#endif /*arduino_extint_lct.h*/

/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void stepFunctionmaster_writer(boolean_T * WRITING_ACK,int size_vector_1,double local_lat,int size_vector_a,boolean_T local_lat_isValid,int size_vector_b,double local_lng,int size_vector_c,boolean_T local_lng_inValid,int size_vector_d,double local_speed,int size_vector_e,boolean_T local_speed_isValid,int size_vector_f,boolean_T TRANSMITTING,int size_vector_g);
    void setupFunctionmaster_writer(uint16_T  slave_address,int size_vector__1,uint_T  bus_frequency,int size_vector__2);
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif
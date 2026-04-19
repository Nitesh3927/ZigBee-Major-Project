/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void stepFunctiongps_reader(double * hdop,int size_vector_1,boolean_T * hdop_isValid,int size_vector_2,uint8_T * satellite,int size_vector_3,boolean_T * satellite_isValid,int size_vector_4,uint8_T * time_hours,int size_vector_5,uint8_T * time_mins,int size_vector_6,uint8_T * time_sec,int size_vector_7,boolean_T * time_isValid,int size_vector_8,uint8_T * date_day,int size_vector_9,uint8_T * date_month,int size_vector_10,uint16_T * date_year,int size_vector_11,boolean_T * date_isValid,int size_vector_12,double * speed,int size_vector_13,boolean_T * speed_isValid,int size_vector_14,double * lat,int size_vector_15,boolean_T * lat_isValid,int size_vector_16,double * lng,int size_vector_17,boolean_T * lng_isValid,int size_vector_18);
    void setupFunctiongps_reader();
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif
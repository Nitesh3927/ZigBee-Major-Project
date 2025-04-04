#ifndef _GPS_PARSER_H_
#define _GPS_PARSER_H_
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    // Read the data from the input port and process
    void readData(uint8_T* buffer
            , uint8_T dataLength
            , const uint8_T startChar
            , const uint8_T endChar
            , const uint8_T separator
            , const uint8_T checkChar
            , uint8_T *yout
            , const uint8_T bufferSize
            , int8_T *status);
    
    // Allocate the buffer
    void initialSetup(uint8_T bufferSize);
    
    // Free the buffer
    void releaseBuffer();
    // Find the checksum from the NMEA string
    uint8_T fetchChecksum(uint8_T *pointToCheckChar, uint8_T endChar, int8_T *status);
    
    void parseData(uint8_T *rawStream
            , uint32_T *time
            , float *latitude
            , float *longitude
            , uint8_T *noSat
            , double *hdop
            , double *alti
            , double *msl
            , double *speed
            , double *tckAngle
            , uint32_T *date
            , uint8_T bufferSize
            , uint8_T separator
            , int8_T *status);
    
#ifdef __cplusplus
}
#endif
#endif //_GPS_PARSER_H_
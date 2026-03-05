#ifndef _MW_ARDUINOBLE_RX_H_
#define _MW_ARDUINOBLE_RX_H_
#include <inttypes.h>
#include "rtwtypes.h"

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
/* This will be run in Rapid Accelerator Mode */

#define INIT_BLE_RECECIVE_PERI(id,  seruuid, charuuid) (0)
#define INIT_BLE_RECECIVE(id, bleAddress, name, seruuid, charuuid) (0)
#define RECEIVE_BLE_DATA(id, out, size) (0)
#define RECEIVE_BLE_DATA_PERI(id, out, size) (0)
#define SEND_CLIENT_DATA(id, out, size) (0)
#define SEND_SERVER_DATA(id, out, size) (0)
#else

/* This will be called in Normal/External modes */
#ifdef __cplusplus
extern "C" {
#endif
void initializeBLEPeripheralRole(uint8_t *id, char* seruuid,char* charuuid);
void initializeBLECentralRole(uint8_t *id, char* bleAddress, char* name, char* seruuid,char* charuuid);
int receiveBLEDataInCentralRole(uint8_t id, int8_t* out,uint8_t size);
int receiveBLEDataInPeripheralRole(uint8_t id, int8_t* out,uint8_t size);
void sendBLEDataInCentralRole(uint8_t id, void* out,uint8_t size);
void sendBLEDataInPeripheralRole(uint8_t id, void* out,uint8_t size);
#ifdef __cplusplus
}
#endif
#define INIT_BLE_RECECIVE_PERI(id,  seruuid, charuuid) initializeBLEPeripheralRole(id, seruuid, charuuid)
#define INIT_BLE_RECECIVE(id, bleAddress,name, seruuid, charuuid) initializeBLECentralRole(id, bleAddress, name, seruuid, charuuid)
#define RECEIVE_BLE_DATA(id, out, size) receiveBLEDataInCentralRole(id, out, size)
#define RECEIVE_BLE_DATA_PERI(id, out, size) receiveBLEDataInPeripheralRole(id, out, size)
#define SEND_CLIENT_DATA(id, out, size) sendBLEDataInCentralRole(id, out, size)
#define SEND_SERVER_DATA(id, out, size) sendBLEDataInPeripheralRole(id, out, size)
#endif
#endif //_MW_ARDUINOBLE_RX_H_
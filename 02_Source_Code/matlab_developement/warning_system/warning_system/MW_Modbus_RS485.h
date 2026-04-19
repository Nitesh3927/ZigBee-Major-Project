/*
 * Wrappers to make Modbus functions available with C linkage.
 * This allows C++ methods to be called from C code.
 *
 * /* Copyright 2018-2020 The MathWorks, Inc. */
#ifndef _MW_ARDUINO_MODBUS_RS485_H_
#define _MW_ARDUINO_MODBUS_RS485_H_
#include <inttypes.h>
#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
    /* This will be run in Rapid Accelerator Mode */
#define MW_Modbus_Slave_Poll() (0)
#define MW_Modbus_Master_readCoil(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_readInput(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_readInputRegister(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_readHoldingRegister(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_readMultipleCoils(slaveID,Address,numElements,data,status) (0)
#define MW_Modbus_Master_readMultipleInputs(slaveID,Address,numElements,data,status) (0)
#define MW_Modbus_Master_readMultipleInputRegister(slaveID,Address,numElements,data,  status) (0)
#define MW_Modbus_Master_readMultipleHoldingRegister(slaveID,Address,numElements,data,  status) (0)
#define MW_Modbus_Master_writeCoil(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_writeHoldingRegister(slaveID,Address,data,status) (0)
#define MW_Modbus_Master_WriteMultipleCoils(slaveID,Address,numElements,data,status) (0)
#define MW_Modbus_Master_writeMultipleHoldingRegister(slaveID,Address,numElements,data,status) (0)
#define MW_Modbus_Slave_readCoil(Address,data,status) (0)
#define MW_Modbus_Slave_readInput(Address,data,status) (0)
#define MW_Modbus_Slave_readInputRegister(Address,data,status) (0)
#define MW_Modbus_Slave_readHoldingRegister(Address,data,status) (0)
#define MW_Modbus_Slave_writeCoil(Address,data,status) (0)
#define MW_Modbus_Slave_writeInput(Address,data,status) (0)
#define MW_Modbus_Slave_WriteHoldingReg(Address,data,status) (0)
#define MW_Modbus_Slave_writeInputReg(Address,data,status) (0)
#else
    void MW_Modbus_Slave_Poll();
    void MW_Modbus_Master_readInput(uint8_t slaveID, uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Master_readInputRegister(uint8_t slaveID, uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Master_readHoldingRegister(uint8_t slaveID, uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Master_readMultipleCoils(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint8_t* data, int8_t* status);
    void MW_Modbus_Master_readMultipleInputs(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint8_t* data, int8_t* status);
    void MW_Modbus_Master_readMultipleInputRegister(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint16_t* data, int8_t* status);
    void MW_Modbus_Master_readMultipleHoldingRegister(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint16_t* data, int8_t* status);
    void MW_Modbus_Master_writeCoil(uint8_t slaveID, uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Master_writeHoldingRegister(uint8_t slaveID, uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Master_WriteMultipleCoils(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint8_t* data, int8_t* status);
    void MW_Modbus_Master_writeMultipleHoldingRegister(uint8_t slaveID, uint16_t Address, uint8_t numElements, uint16_t* data, int8_t* status);
    void MW_Modbus_Slave_readCoil(uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Slave_readInput(uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Slave_readInputRegister(uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Slave_readHoldingRegister(uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Slave_writeCoil(uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Slave_writeInput(uint16_t Address, uint8_t* data, int8_t* status);
    void MW_Modbus_Slave_WriteHoldingReg(uint16_t Address, uint16_t* data, int8_t* status);
    void MW_Modbus_Slave_writeInputReg(uint16_t Address, uint16_t* data, int8_t* status);
#endif
    
#ifdef __cplusplus
}
#endif
#endif //_MW_ARDUINO_MODBUS_RS485_H_

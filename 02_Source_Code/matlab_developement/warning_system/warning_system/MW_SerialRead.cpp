/* Copyright 2015-2023 The MathWorks, Inc. */
#include <inttypes.h>
#include "Arduino.h"
#include "MW_SerialRead.h"
#include "io_wrappers.h"


extern "C" {
    void __cxa_pure_virtual(void);
}

extern "C" {
    uint32_t getCurrentTime(){
        return millis();
    }
}

// Serial Read functions
extern "C" void MW_Serial0_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial0_read_byte()
{
    return Serial.read();
}

extern "C" int MW_Serial0_available()
{
    int BufferSize;
    BufferSize = Serial.available();
    return(BufferSize);
}

#if defined(ARDUINO_NUM_SERIAL_PORTS)
#if(ARDUINO_NUM_SERIAL_PORTS >= 2)
extern "C" void MW_Serial1_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial1.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial1_read_byte()
{
    return Serial1.read();
}

extern "C" int MW_Serial1_available()
{
    int BufferSize;
    BufferSize = Serial1.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 2)
extern "C" void MW_Serial2_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial2.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial2_read_byte()
{
    return Serial2.read();
}

extern "C" int MW_Serial2_available()
{
    int BufferSize;
    BufferSize = Serial2.available();
    return(BufferSize);
}
#endif

#if(ARDUINO_NUM_SERIAL_PORTS > 3)
extern "C" void MW_Serial3_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial3.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial3_read_byte()
{
    return Serial3.read();
}

extern "C" int MW_Serial3_available()
{
    int BufferSize;
    BufferSize = Serial3.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 4)
extern "C" void MW_Serial4_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial4.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial4_read_byte()
{
    return Serial4.read();
}

extern "C" int MW_Serial4_available()
{
    int BufferSize;
    BufferSize = Serial4.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 5)
extern "C" void MW_Serial5_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial5.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial5_read_byte()
{
    return Serial5.read();
}

extern "C" int MW_Serial5_available()
{
    int BufferSize;
    BufferSize = Serial5.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 6)
extern "C" void MW_Serial6_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial6.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial6_read_byte()
{
    return Serial6.read();
}

extern "C" int MW_Serial6_available()
{
    int BufferSize;
    BufferSize = Serial6.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 7)
extern "C" void MW_Serial7_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial7.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial7_read_byte()
{
    return Serial7.read();
}

extern "C" int MW_Serial7_available()
{
    int BufferSize;
    BufferSize = Serial7.available();
    return(BufferSize);
}
#endif
#if(ARDUINO_NUM_SERIAL_PORTS > 8)
extern "C" void MW_Serial8_read(char *bufferData,const uint16_t DataSizeInBytes)
{
    Serial8.readBytes(bufferData,DataSizeInBytes);
}

int MW_Serial8_read_byte()
{
    return Serial8.read();
}

extern "C" int MW_Serial8_available()
{
    int BufferSize;
    BufferSize = Serial8.available();
    return(BufferSize);
}
#endif
#endif

#if defined(ARDUINO_NUM_SERIAL_PORTS)
extern "C" int getNumbytesAvailable(const uint8_T port){
    /* This function is used only during code generation from MATLAB IO API. */
    if(port == 0){
        return MW_Serial0_available();
    }
    #if(ARDUINO_NUM_SERIAL_PORTS >= 2)
    if (port == 1){
        return MW_Serial1_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 2)
    if (port == 2){
        return MW_Serial2_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 3)
    if (port == 3){
        return MW_Serial3_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 4)
    if (port == 4){
        return MW_Serial4_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 5)
    if (port == 5){
        return MW_Serial5_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 6)
    if (port == 6){
        return MW_Serial6_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 7)
    if (port == 7){
        return MW_Serial7_available();
    }
    #endif
    #if(ARDUINO_NUM_SERIAL_PORTS > 8)
    if (port == 8){
        return MW_Serial8_available();
    }
        #endif
        return 0;
    }
    #endif

    #if defined(ARDUINO_NUM_SERIAL_PORTS)
    #if(ARDUINO_NUM_SERIAL_PORTS > 8)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read,MW_Serial4_read, MW_Serial5_read, MW_Serial6_read, MW_Serial7_read, MW_Serial8_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte, MW_Serial4_read_byte, MW_Serial5_read_byte, MW_Serial6_read_byte, MW_Serial7_read_byte, MW_Serial8_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available,MW_Serial4_available, MW_Serial5_available, MW_Serial6_available, MW_Serial7_available, MW_Serial8_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 7)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read,MW_Serial4_read, MW_Serial5_read, MW_Serial6_read, MW_Serial7_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte, MW_Serial4_read_byte, MW_Serial5_read_byte, MW_Serial6_read_byte, MW_Serial7_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available,MW_Serial4_available, MW_Serial5_available, MW_Serial6_available, MW_Serial7_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 6)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read,MW_Serial4_read, MW_Serial5_read, MW_Serial6_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte, MW_Serial4_read_byte, MW_Serial5_read_byte, MW_Serial6_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available,MW_Serial4_available, MW_Serial5_available, MW_Serial6_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 5)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read,MW_Serial4_read, MW_Serial5_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte, MW_Serial4_read_byte, MW_Serial5_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available,MW_Serial4_available, MW_Serial5_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 4)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read,MW_Serial4_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte,MW_Serial4_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available,MW_Serial4_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 3)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read, MW_Serial3_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte, MW_Serial3_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available,MW_Serial3_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS > 2)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read, MW_Serial2_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte, MW_Serial2_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available,MW_Serial2_available};
    #elif(ARDUINO_NUM_SERIAL_PORTS == 2)
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read, MW_Serial1_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte, MW_Serial1_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available,MW_Serial1_available};
    #else
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read};
    int (*read_byte_func_ptr[])() = {MW_Serial0_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available};
    #endif
    #else
    void (*read_func_ptr[])(char *, uint16_t) = {MW_Serial0_read};
    uint8_t (*read_byte_func_ptr[])() = {MW_Serial0_read_byte};
    int (*available_func_ptr[])() = {MW_Serial0_available};
    #endif



    extern "C" void fillDataBuffer(const uint8_T port,const uint16_t DataSizeInBytes,char *data,uint8_T *status)
    {
        char databuffer[2*DataSizeInBytes];
        (*read_func_ptr[port])(databuffer,DataSizeInBytes);
        for(int ii=0;ii< DataSizeInBytes;ii++)
        {
            *data++ = databuffer[ii];
        }
        *status = 1;
    }



    extern "C" void MW_Serial_read(const uint8_T port,const uint16_t DataSizeInBytes, char *data,uint8_T *status,\
                                   char* packageTerminator, uint8_T terminatorLength, char* packageHeader, uint8_T headerLength)
    {
        int dataSizeinBuffer;
        char tempdatabuffer[ARDUINO_SERIAL_RECEIVE_BUFFER_SIZE];

        uint8_t hasHeader = (packageHeader!=NULL);
        uint8_t hasTerminator = (packageTerminator!=NULL);

        char* dataCopy=data;

        int requiredDataLength = DataSizeInBytes + (headerLength * hasHeader) + (terminatorLength * hasTerminator);

        /* Read the size of data available in the Arduino Serial buffer */
        dataSizeinBuffer = (*available_func_ptr[port])();
        if (dataSizeinBuffer < requiredDataLength){
            /* If no data is available, data=0's  and status =0 */
            for(int ii=0;ii< DataSizeInBytes;ii++)
            {
                *data++ = 0;
            }
            *status = 0;
            return;
        }
        if(hasHeader){
            for(int i=0;i<headerLength;i++){
                if((*available_func_ptr[port])()==0)    //No available bytes to read. return
                {
                    for(int ii=0;ii< DataSizeInBytes;ii++)
                    {
                        *data++ = 0;
                    }
                    *status = 0;
                    return;
                }
                char rxByte = (*read_byte_func_ptr[port])();
                if(packageHeader[i] != rxByte){ //Header mismatch, start comparing from start
                    if(packageHeader[0] == rxByte){
                        i=0;    // Start comparing again from second byte(i++)
                    }else{
                        i=-1;   // Start comparing again from first byte
                    }
                }
            }
        }
        requiredDataLength = DataSizeInBytes + (terminatorLength * hasTerminator);
        dataSizeinBuffer = (*available_func_ptr[port])();
        if (dataSizeinBuffer < requiredDataLength){
            /* If no data is available, data=0's  and status =0 */
            for(int ii=0;ii< DataSizeInBytes;ii++)
            {
                *data++ = 0;
            }
            *status = 0;
            return;
        }
        fillDataBuffer(port,DataSizeInBytes,data,status);
        if(hasTerminator){
            for(int i=0;i<terminatorLength;i++){
                if((*available_func_ptr[port])()==0)    //No available bytes to read. return
                {
                    for(int ii=0;ii< DataSizeInBytes;ii++)
                    {
                        *data++ = 0;
                    }
                    *status = 0;
                    return;
                }
                char rxByte = (*read_byte_func_ptr[port])();
                if(packageTerminator[i] != rxByte){ //Terminator mismatch
                    /* If no data is available, data=0's  and status =0 */
                    for(int ii=0;ii< DataSizeInBytes;ii++)
                    {
                        *data++ = 0;
                    }
                    *status = 0;
                    return;
                }
            }
        }
    }


    extern "C" void MW_Serial_readVariableLength(const uint8_T port,const uint16_t DataSizeInBytes, char *data,uint8_T *status,\
                                                 char* packageTerminator, uint8_T terminatorLength, char* packageHeader, uint8_T headerLength, \
                                                 const uint16_T timeout, uint8_T dataTypeWidth)
    {
        uint8_T rxLen;
        int dataSizeinBuffer;
        char tempdatabuffer[ARDUINO_SERIAL_RECEIVE_BUFFER_SIZE];

        uint8_t hasHeader = (packageHeader!=NULL);
        uint8_t hasTerminator = (packageTerminator!=NULL);

        char* dataCopy=data;

        int requiredDataLength = uint16_t(1) + (headerLength * hasHeader) + (terminatorLength * hasTerminator);

        /* Read the size of data available in the Arduino Serial buffer */
        dataSizeinBuffer = (*available_func_ptr[port])();
        if (dataSizeinBuffer < requiredDataLength){
            /* If no data is available, data=0's  and status =0 */
            for(int ii=0;ii< DataSizeInBytes;ii++)
            {
                *data++ = 0;
            }
            *status = 0;
            return;
        }
        if(hasHeader){
            for(int i=0;i<headerLength;i++){
                if((*available_func_ptr[port])()==0)    //No available bytes to read. return
                {
                    for(int ii=0;ii< DataSizeInBytes;ii++)
                    {
                        *data++ = 0;
                    }
                    *status = 0;
                    return;
                }
                char rxByte = (*read_byte_func_ptr[port])();
                if(packageHeader[i] != rxByte){ //Header mismatch, start comparing from start
                    if(packageHeader[0] == rxByte){
                        i=0;    // Start comparing again from second byte(i++)
                    }else{
                        i=-1;   // Start comparing again from first byte
                    }
                }
            }
        }
        requiredDataLength = 1 + (terminatorLength * hasTerminator);
        dataSizeinBuffer = (*available_func_ptr[port])();
        if (dataSizeinBuffer < requiredDataLength){
            /* If no data is available, data=0's  and status =0 */
            for(int ii=0;ii< DataSizeInBytes;ii++)
            {
                *data++ = 0;
            }
            *status = 0;
            return;
        }

        uint8_t end=0;
        uint8_t terminatorCount = 0;
        uint8_t rxCounter=0;
        if(hasTerminator){
            while(!end){
                uint32_t previousTimestamp, currentTimestamp;
                int rxByte=(*read_byte_func_ptr[port])();
                if(rxByte!=-1){
                    previousTimestamp=millis();
                    if(packageTerminator[terminatorCount] == rxByte){
                        terminatorCount++;
                        if(terminatorCount == terminatorLength){
                            end = 1;
                        }
                    }else{
                        for(int ii=0;ii<terminatorCount;ii++){
                            //Terminator mismatch, copy the partial terminator
                            data[rxCounter++] = packageTerminator[ii];
                        }
                        if(packageTerminator[0] == rxByte){
                            //Check if this is new terminator
                            terminatorCount = 1;
                        }else{
                            terminatorCount=0;
                            data[rxCounter++] = rxByte;
                        }
                    }
                }else{
                    //no data received
                    currentTimestamp = millis();
                    if(currentTimestamp - previousTimestamp > timeout){
                        //Timeout condition.
                        *status = 0;
                        return;
                    }
                }
            }
        }else{  //No terminator
            while(!end){
                uint32_t previousTimestamp, currentTimestamp;
                int rxByte=(*read_byte_func_ptr[port])();
                if(rxByte!=-1){
                    previousTimestamp=millis();
                    data[rxCounter++] = rxByte;
                }else{
                    //no data received
                    currentTimestamp = millis();
                    if(currentTimestamp - previousTimestamp > timeout){
                        //Timeout condition.
                        end = 1;
                    }
                }
            }
        }
    for(int ii=rxCounter;ii<DataSizeInBytes;ii++){
        data[ii]=0;
    }
    //Received correct data
    if(rxCounter<DataSizeInBytes){
        *status = rxCounter/dataTypeWidth; //If length of partial data is also required, use ceil((float)rxCounter/dataTypeWidth)
    }else{
        *status = DataSizeInBytes/dataTypeWidth;
    }
    }

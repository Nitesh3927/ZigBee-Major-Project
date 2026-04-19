/* Copyright 2015-2023 The MathWorks, Inc. */

#include <inttypes.h>
#include "Arduino.h"
#include "MW_SerialWrite.h"
#include "io_wrappers.h"

// Define a template function to handle different data types
//
template <typename SerialTemp>
void printData(void* dataInput, uint8_t counter, int sendModeEnum, int base, HardwareSerial* serialPtr)
{
    SerialTemp* ptr =  (SerialTemp* )dataInput;
    while (counter--)
    {
        if (sendModeEnum == 1)
        {
            serialPtr->print(*(ptr++), base);
        } else
        {
            serialPtr->println(*(ptr++), base);
        }
    }
}

template <typename Serial0Temp>
void printData0(void* dataInput, uint8_t counter, int sendModeEnum, int base)
{
    Serial0Temp* ptr =  (Serial0Temp* )dataInput;
    while (counter--)
    {
        if (sendModeEnum == 1)
        {
            Serial.print(*(ptr++), base);
        } else
        {
            Serial.println(*(ptr++), base);
        }
    }
}

extern "C" {
    void __cxa_pure_virtual(void);
}

// One-time initialization
extern "C" void MW_SCI_Open(const uint8_T port){
    if (port==0){
        #if(defined(ESP_PLATFORM))
        static uint8_t esp32_serial0_init_f=0;
        if(esp32_serial0_init_f==0){
            Serial_begin(0, _RTT_BAUDRATE_SERIAL0_, _RTT_CONFIG_SERIAL0_);
            esp32_serial0_init_f=1;
        }
        #endif
        // Module 0 is by default initialized by MW_Arduino_Init function
        return;
    }
    switch(port){
        case 1:
            #if defined(_RTT_BAUDRATE_SERIAL1_)
            Serial_begin(1, _RTT_BAUDRATE_SERIAL1_, _RTT_CONFIG_SERIAL1_);
            #endif
            break;
        case 2:
            #if defined(_RTT_BAUDRATE_SERIAL2_)
            Serial_begin(2, _RTT_BAUDRATE_SERIAL2_, _RTT_CONFIG_SERIAL2_);
            #endif
            break;
        case 3:
            #if defined(_RTT_BAUDRATE_SERIAL3_)
            Serial_begin(3, _RTT_BAUDRATE_SERIAL3_, _RTT_CONFIG_SERIAL3_);
            #endif
            break;
        case 4:
            #if defined(_RTT_BAUDRATE_SERIAL4_)
            Serial_begin(4, _RTT_BAUDRATE_SERIAL4_, _RTT_CONFIG_SERIAL4_);
            #endif
            break;
        case 5:
            #if defined(_RTT_BAUDRATE_SERIAL5_)
            Serial_begin(5, _RTT_BAUDRATE_SERIAL5_, _RTT_CONFIG_SERIAL5_);
            #endif
            break;
        case 6:
            #if defined(_RTT_BAUDRATE_SERIAL6_)
            Serial_begin(6, _RTT_BAUDRATE_SERIAL6_, _RTT_CONFIG_SERIAL6_);
            #endif
            break;
        case 7:
            #if defined(_RTT_BAUDRATE_SERIAL7_)
            Serial_begin(7, _RTT_BAUDRATE_SERIAL7_, _RTT_CONFIG_SERIAL7_);
            #endif
            break;
        case 8:
            #if defined(_RTT_BAUDRATE_SERIAL8_)
            Serial_begin(8, _RTT_BAUDRATE_SERIAL8_, _RTT_CONFIG_SERIAL8_);
            #endif
            break;
        default:
            break;
    }
}
extern "C" void MW_Serial_write(const uint8_T port, void *dataInput, size_t s,const uint8_T dataSizeInBytes, \
                                const uint8_T sendModeEnum, const uint8_T dataType, const uint8_T sendFormatEnum, \
                                const uint8_T floatprecision, char* label, char* packageTerminator, uint8_T terminatorLength, \
                                char* packageHeader, uint8_T headerLength)
{
    int dataSize=dataSizeInBytes;
    unsigned int counter = s;
    int base;
    if(port >=ARDUINO_NUM_SERIAL_PORTS)
    {
        return; // Selected port doesn't exist on board hence returning
    }
    HardwareSerial* serialPtr;
    switch(port){
        case 1:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 2)
            serialPtr = &Serial1;
            #endif
            break;
        case 2:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 3)
            serialPtr = &Serial2;
            #endif
            break;
        case 3:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 4)
            serialPtr = &Serial3;
            #endif
            break;
        case 4:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 5)
            serialPtr = &Serial4;
            #endif
            break;
        case 5:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 6)
            serialPtr = &Serial5;
            #endif
            break;
        case 6:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 7)
            serialPtr = &Serial6;
            #endif
            break;
        case 7:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 8)
            serialPtr = &Serial7;
            #endif
            break;
        case 8:
            #if(ARDUINO_NUM_SERIAL_PORTS >= 9)
            serialPtr = &Serial8;
            #endif
            break;
        default:
            break;
    }


    #if (defined(ARDUINO_ARCH_AVR))
    if (dataSize==8){
        dataSize=4;
    }
    #endif

    dataSize = dataSize * s;

    if (sendFormatEnum == 0) { //DEC
        base=DEC;
    }
    else if(sendFormatEnum == 1) { //HEX
        base=HEX;
    }
    else if(sendFormatEnum == 2) { //OCT
        base=OCT;
    }
    else { //BIN
        base=BIN;
    }

    if(port==0) {
        if (sendModeEnum == 0)
        {
            if(packageHeader!=NULL){
                Serial.write((uint8_t *)packageHeader,headerLength);
            }
            Serial.write((uint8_t *)dataInput,(dataSize));
            if(packageTerminator!=NULL){
                Serial.write((uint8_t *)packageTerminator,terminatorLength);
            }
        }
        else
        {
            Serial.print(label);

            switch (dataType) {
                case 0:
                    printData0<uint8_t>(dataInput, counter, sendModeEnum,base);
                    break;
                case 1:
                    printData0<uint16_t>(dataInput, counter, sendModeEnum, base);
                    break;
                case 2:
                    printData0<uint32_t>(dataInput, counter, sendModeEnum, base);
                    break;
                case 3:
                    printData0<int8_t>(dataInput, counter, sendModeEnum, base);
                    break;
                case 4:
                    printData0<int16_t>(dataInput, counter, sendModeEnum, base);
                    break;
                case 5:
                    printData0<int32_t>(dataInput, counter, sendModeEnum, base);
                    break;
                case 6:
                    //printData<double>(reinterpret_cast<double*>(dataInput), counter, sendModeEnum, base, serialPtr, floatprecision);
                    double * ptr = (double *) dataInput;
                    while(counter--)
                    {
                        if (sendModeEnum == 1)
                        {
                            Serial.print(*(ptr++),floatprecision); // for double and single, DE is the only supported mode
                        }
                        else
                        {
                            Serial.println(*(ptr++),floatprecision);   // for double and single, DE is the only supported mode
                        }
                    }
                            break;
            } //double, single
        } //print and println
    }
    else{
        #if defined(ARDUINO_NUM_SERIAL_PORTS)
        #if(ARDUINO_NUM_SERIAL_PORTS >= 2)
        if (sendModeEnum == 0)
        {
            if(packageHeader!=NULL){
                serialPtr->write((uint8_t *)packageHeader,headerLength);
            }
            serialPtr->write((uint8_t *)dataInput,(dataSize));
            if(packageTerminator!=NULL){
                serialPtr->write((uint8_t *)packageTerminator,terminatorLength);
            }
        }
        else
        {
            serialPtr->print(label);
            // Use the template function based on the dataType value
            switch (dataType) {
                case 0:
                    printData<uint8_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 1:
                    printData<uint16_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 2:
                    printData<uint32_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 3:
                    printData<int8_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 4:
                    printData<int16_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 5:
                    printData<int32_t>(dataInput, counter, sendModeEnum, base, serialPtr);
                    break;
                case 6:
                    //printData<double>(reinterpret_cast<double*>(dataInput), counter, sendModeEnum, base, serialPtr, floatprecision);
                    double * ptr = (double *) dataInput;
                    while(counter--)
                    {
                        if (sendModeEnum == 1)
                        {
                            serialPtr->print(*(ptr++),floatprecision); // for double and single, DE is the only supported mode
                        }
                        else
                        {
                            serialPtr->println(*(ptr++),floatprecision);   // for double and single, DE is the only supported mode
                        }
                    }
                            break;
            }
        } //print and println
        #endif
        #endif
    } //Port
}

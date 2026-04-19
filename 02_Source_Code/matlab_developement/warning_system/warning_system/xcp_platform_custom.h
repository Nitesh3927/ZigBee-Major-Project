/*
* Copyright 2018-2024 The MathWorks, Inc.
*
* File: xcp_platform_custom.h
* Designed for Arduino boards
* Abstract:
*   Implementation of XCP Platform Abstraction Layer interface
*   for Arduino boards
*/

#ifndef XCP_PLATFORM_CUSTOM_H
#define XCP_PLATFORM_CUSTOM_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#if !(defined(USE_MBEDRTOS))
#include <Arduino.h>
#endif

#define XCP_PRINTF(...)

#define PRAGMA(n)   _Pragma(#n)
#define XCP_PRAGMA_PACK_BEGIN(n)     PRAGMA(pack(push, n))
#define XCP_PRAGMA_PACK_END()        PRAGMA(pack(pop))
#define XCP_ATTRIBUTE_ALIGNED(n)
#define XCP_ATTRIBUTE_PACKED

#if (defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(_ROTH_LEONARDO_))
	
    #define XCP_MUTEX_DEFINE(lock)
    #define XCP_MUTEX_INIT(lock)
    #define XCP_MUTEX_LOCK(lock) cli()
    #define XCP_MUTEX_UNLOCK(lock) sei()
    
    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4


#elif (defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_ADK))
	
    #define XCP_MUTEX_DEFINE(lock)
    #define XCP_MUTEX_INIT(lock)
    #define XCP_MUTEX_LOCK(lock) cli()
    #define XCP_MUTEX_UNLOCK(lock) sei()

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif
    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )
    #define XCP_MEM_ALIGNMENT 4

#elif defined(__SAMD21G18A__) || defined(ARDUINO_NANO_RP2040_CONNECT)

    #define XCP_MUTEX_DEFINE(lock)          uint32_t lock 
    #define XCP_MUTEX_INIT(lock)            lock = 0
    #define XCP_MUTEX_LOCK(lock)            lock = sys_arch_protect()
    #define XCP_MUTEX_UNLOCK(lock)          sys_arch_unprotect(lock)

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif
    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4

    /* 32K RAM */

#elif defined(ARDUINO_ARCH_SAM)

    #define XCP_MUTEX_DEFINE(lock)          uint32_t lock 
    #define XCP_MUTEX_INIT(lock)            lock = 0
    #define XCP_MUTEX_LOCK(lock)            lock = sys_arch_protect()
    #define XCP_MUTEX_UNLOCK(lock)          sys_arch_unprotect(lock)

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4

    /* 96K RAM */

#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    
    #define XCP_MUTEX_DEFINE(lock)          uint32_t lock 
    #define XCP_MUTEX_INIT(lock)            lock = 0
    #define XCP_MUTEX_LOCK(lock)            lock = sys_arch_protect()
    #define XCP_MUTEX_UNLOCK(lock)          sys_arch_unprotect(lock)
    
    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif
    
    #define XCP_TIMESTAMP_GET         xcpGetTimestamp

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )
    
    #define XCP_MEM_ALIGNMENT 4

    /* 256k RAM */
#elif defined(ARDUINO_ARCH_ESP32)

    #define XCP_MUTEX_DEFINE(lock)          portMUX_TYPE lock
    #define XCP_MUTEX_INIT(lock)            lock.owner = portMUX_FREE_VAL; lock.count = 0;
    #define XCP_MUTEX_LOCK(lock)            portENTER_CRITICAL(&lock)
    #define XCP_MUTEX_UNLOCK(lock)          portEXIT_CRITICAL(&lock)

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4

#elif defined(__IMXRT1062__)
    #define XCP_MUTEX_DEFINE(lock)
    #define XCP_MUTEX_INIT(lock)
    #define XCP_MUTEX_LOCK(lock) cli()
    #define XCP_MUTEX_UNLOCK(lock) sei()

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4
#elif defined(ARDUINO_UNOR4_WIFI)  || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_RASPBERRY_PI_PICO)
    #define XCP_MUTEX_DEFINE(lock)
    #define XCP_MUTEX_INIT(lock)
    #define XCP_MUTEX_LOCK(lock) noInterrupts()
    #define XCP_MUTEX_UNLOCK(lock) interrupts()

    #define XCP_ADDRESS_GET(addressExtension, address)  (uint8_T*) ((uintptr_t) address)
    
    #ifndef XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME
        uint32_T getCurrentTimestamp(void);
        #define XCP_TIMESTAMP_GET()             getCurrentTimestamp()
        #define XCP_TIMESTAMP_UNIT              XCP_TIMESTAMP_UNIT_1US
    #endif

    #define XCP_SLEEP(s, us) delay(1000*(s) + (us)/1000 )

    #define XCP_MEM_ALIGNMENT 4

            
#endif

#endif

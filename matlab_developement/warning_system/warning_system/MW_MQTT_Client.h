/* Copyright 2021 - 2024 The MathWorks, Inc. */

#ifndef _MW_MQTT_CLIENT_H_
#define _MW_MQTT_CLIENT_H_
//#include <inttypes.h>
#include <string.h>
#include "rtwtypes.h"
#include <stdint.h>

#include "peripheralIncludes.h"

#ifndef IO_AUTOGEN_WIFIMQTT
#ifdef __MW_TARGET_USE_HARDWARE_RESOURCES_H__
#include "MW_target_hardware_resources.h"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
 /* This will be run in Rapid Accelerator Mode */
 #define MW_getCurrentTimeInMillisMQTT()                         (0)
 #define MW_MQTT_publish_setup()                                 (0)
 #define MW_MQTT_publish_step(a,b,c,d,e,f,g)                     (0)                     
 #define MW_MQTT_publish_terminate()                             (0)
 #define MW_MQTT_subscribe_setup(a,b)                            (0)
 #define MW_MQTT_subscribe_step(a,b,c,d,e,f)                     (0)
 #define MW_MQTT_subscribe_terminate(a)                          (0)
 #ifdef IO_AUTOGEN_WIFIMQTT
 #define updateMQTTBrokerAddress(a)                              (0)
 #define updateMQTTBrokerPort(a)                                 (0)
 #define updateMQTTClientID(a)                                   (0)
 #define updateMQTTUsername(a)                                   (0)
 #define updateMQTTPassword(a)                                   (0)
 #endif
#else    

 uint32_T MW_getCurrentTimeInMillisMQTT();
 void MW_MQTT_publish_setup();
 void MW_MQTT_publish_step(char* topicString , uint8_t type, void* dataIn, uint8_t dataLength, uint8_t service, uint8_t retainMsg, uint8_t* status);
 void MW_MQTT_publish_terminate();
 void MW_MQTT_subscribe_setup(char* topicString, uint8_t* subID);
 void MW_MQTT_subscribe_step(uint8_t subID, uint8_t* isNew, char* Message, uint8_t length, char* OutTopic, uint8_t topicLength);
 void MW_MQTT_subscribe_terminate(uint8_t subID);
 #ifdef IO_AUTOGEN_WIFIMQTT
 void updateMQTTBrokerAddress(char* value);
 void updateMQTTBrokerPort(uint8_T* value);
 void updateMQTTClientID(char* value);
 void updateMQTTUsername(char* value);
 void updateMQTTPassword(char* value);
 #endif //IO_AUTOGEN_WIFIMQTT

#endif

#ifdef __cplusplus
}
#endif
#endif //_MW_MQTT_CLIENT_H_

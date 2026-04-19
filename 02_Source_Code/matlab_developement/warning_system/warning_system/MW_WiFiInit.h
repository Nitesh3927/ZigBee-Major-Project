/*
 * Wrappers to make WiFi TCP Send functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2023 The MathWorks, Inc. */

#include <inttypes.h>
#include "rtwtypes.h"
#include <stdio.h> /* for size_t */

#include "peripheralIncludes.h"

#ifdef __cplusplus
extern "C" {
#endif

void updateSSID(char *ssid_bytes);
void updateWPAPASS(char *wpapass_bytes);
void updateWPA2username(char *wpa2username);
void updateWPA2password(char *wpa2password);
void updateKeyIndexAndKey(char *wepkey,int key);
uint8_t wifi_wpa2_init(char *ipBytes);
uint8_t wifi_wep_init(char *ipBytes);
uint8_t wifi_wpa_init(char *ipBytes);
uint8_t wifi_none_init(char *ipBytes);
uint8_t wifi_configureStatus();
void wifi_disconnect(void);

#ifdef __cplusplus
}
#endif
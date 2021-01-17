/****************************************************************************************************************************
   defines.h for DHT11ESP8266_Debug.ino
   For ESP8266 boards

   Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.1.1

   Version    Modified By   Date      Comments
   -------    -----------  ---------- -----------
    1.0.0     K Hoang      28/10/2019 Initial coding
    1.0.1     K Hoang      28/10/2019 Add features
    1.0.2     K Hoang      21/11/2019 Fix bug. Add features.
    1.0.3     K Hoang      31/11/2019 Fix compiler errors for ESP8266 core pre-2.5.2. Add examples.
    1.0.4     K Hoang      07/01/2020 Add configurable personalized RFC-952 DHCP hostname
    1.0.5     K Hoang      20/01/2020 Add configurable static IP, GW, SN, DNS1, DNS2 and Config Portal static IP and Credentials
    1.0.6     K Hoang      05/02/2020 Optimize, fix EEPROM size to 2K from 4K, shorten code size, add functions
    1.0.7     K Hoang      18/02/2020 Add checksum, enable AutoConnect to configurable MultiWiFi and MultiBlynk Credentials
    1.0.8     K Hoang      24/02/2020 Fix AP-staying-open bug. Add clearConfigData()
    1.0.9     K Hoang      12/03/2020 Enhance Config Portal GUI
    1.0.10    K Hoang      08/04/2020 SSID password maxlen is 63 now. Permit special chars # and % in input data.
    1.0.11    K Hoang      09/04/2020 Enable adding dynamic custom parameters from sketch
    1.0.12    K Hoang      13/04/2020 Fix MultiWiFi/Blynk bug introduced in broken v1.0.11
    1.0.13    K Hoang      25/04/2020 Add Configurable Config Portal Title, Default Config Data and DRD. Update examples.
    1.0.14    K Hoang      03/05/2020 Fix bug and change feature in dynamicParams.
    1.0.15    K Hoang      12/05/2020 Fix bug and Update to use LittleFS for ESP8266 core 2.7.1+. Add example.
    1.0.16    K Hoang      25/06/2020 Fix bug and logic of USE_DEFAULT_CONFIG_DATA. Auto format SPIFFS/LittleFS.
    1.1.0     K Hoang      01/01/2021 Add support to ESP32 LittleFS. Remove possible compiler warnings. Update examples. Add MRD
    1.1.1     K Hoang      16/01/2021 Add functions to control Config Portal from software or Virtual Switches
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#define DOUBLERESETDETECTOR_DEBUG     true
#define BLYNK_WM_DEBUG                3

// #define USE_SPIFFS and USE_LITTLEFS   false        => using EEPROM for configuration data in WiFiManager
// #define USE_LITTLEFS    true                       => using LITTLEFS for configuration data in WiFiManager
// #define USE_LITTLEFS    false and USE_SPIFFS true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_LITTLEFS and USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>
// From ESP8266 core 2.7.1, SPIFFS will be deprecated and to be replaced by LittleFS
// Select USE_LITTLEFS (higher priority) or USE_SPIFFS

#define USE_LITTLEFS                true
//#define USE_LITTLEFS                false
#define USE_SPIFFS                  false
//#define USE_SPIFFS                  true

#if USE_LITTLEFS
//LittleFS has higher priority
#define CurrentFileFS     "LittleFS"
#ifdef USE_SPIFFS
#undef USE_SPIFFS
#endif
#define USE_SPIFFS                  false
#elif USE_SPIFFS
#define CurrentFileFS     "SPIFFS"
#endif


#if !( USE_LITTLEFS || USE_SPIFFS)
// EEPROM_SIZE must be <= 4096 and >= CONFIG_DATA_SIZE (currently 172 bytes)
#define EEPROM_SIZE    (4 * 1024)
// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START  768
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

#define USE_DYNAMIC_PARAMETERS                    true
// Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h>

//You have to download Blynk WiFiManager Blynk_WM library at //https://github.com/khoih-prog/Blynk_WM
// In order to enable (USE_BLYNK_WM = true). Otherwise, use (USE_BLYNK_WM = false)
#define USE_BLYNK_WM   true
//#define USE_BLYNK_WM   false

//#define USE_SSL     true
#define USE_SSL     false

#if USE_BLYNK_WM
#if USE_SSL
#include <BlynkSimpleEsp8266_SSL_WM.h>        //https://github.com/khoih-prog/Blynk_WM
#else
#include <BlynkSimpleEsp8266_WM.h>            //https://github.com/khoih-prog/Blynk_WM
#endif

#include "Credentials.h"
#include "dynamicParams.h"

#else
#if USE_SSL
#include <BlynkSimpleEsp8266_SSL.h>
#define BLYNK_HARDWARE_PORT     9443
#else
#include <BlynkSimpleEsp8266.h>
#define BLYNK_HARDWARE_PORT     8080
#endif
#endif

#if !USE_BLYNK_WM

#ifndef LED_BUILTIN
#define LED_BUILTIN       2         // Pin D2 control on-board LED
#endif

#define USE_LOCAL_SERVER    true
//#define USE_LOCAL_SERVER    false

// If local server
#if USE_LOCAL_SERVER
char blynk_server[]   = "yourname.duckdns.org";
#endif

char auth[]     = "***";
char ssid[]     = "***";
char pass[]     = "***";

#endif

#define PIN_LED   2   // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
#define PIN_D2    4   // Pin D2 mapped to pin GPIO4 of ESP8266

#define DHT_PIN     PIN_D2
#define DHT_TYPE    DHT11

#define HOST_NAME   "8266-DHT11-Debug"

#endif      //defines_h

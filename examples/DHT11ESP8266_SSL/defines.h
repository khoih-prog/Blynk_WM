/****************************************************************************************************************************
  defines.h for DHT11ESP8266_SSL.ino
  For ESP8266 boards

  Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#ifndef ESP8266
  #error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#define DOUBLERESETDETECTOR_DEBUG     false
#define BLYNK_WM_DEBUG                0

// #define USE_SPIFFS and USE_LITTLEFS   false        => using EEPROM for configuration data in WiFiManager
// #define USE_LITTLEFS    true                       => using LITTLEFS for configuration data in WiFiManager
// #define USE_LITTLEFS    false and USE_SPIFFS true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_LITTLEFS and USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>
// From ESP8266 core 2.7.1, SPIFFS will be deprecated and to be replaced by LittleFS
// Select USE_LITTLEFS (higher priority) or USE_SPIFFS

#define USE_LITTLEFS                true
#define USE_SPIFFS                  false

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
  #define EEPROM_START  0
#endif

//////////////////////////////////////////

//You have to download Blynk WiFiManager Blynk_WM library at //https://github.com/khoih-prog/Blynk_WM
// In order to enable (USE_BLYNK_WM = true). Otherwise, use (USE_BLYNK_WM = false)
#define USE_BLYNK_WM   true

#define USE_SSL     true

#if USE_BLYNK_WM
  /////////////////////////////////////////////

  // Add customs headers from v1.2.0
  #define USING_CUSTOMS_STYLE                 true
  #define USING_CUSTOMS_HEAD_ELEMENT          true
  #define USING_CORS_FEATURE                  true
  
  /////////////////////////////////////////////
  
  // Force some params in Blynk, only valid for library version 1.0.1 and later
  #define TIMEOUT_RECONNECT_WIFI                    10000L
  #define RESET_IF_CONFIG_TIMEOUT                   true
  
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
  
  // Config Timeout 120s (default 60s)
  #define CONFIG_TIMEOUT                            120000L
  
  #define USE_DYNAMIC_PARAMETERS                    true

  /////////////////////////////////////////////

  #define REQUIRE_ONE_SET_SSID_PW             false

  #define SCAN_WIFI_NETWORKS                  true
  
  // To be able to manually input SSID, not from a scanned SSID lists
  #define MANUAL_SSID_INPUT_ALLOWED           true
  
  // From 2-15
  #define MAX_SSID_IN_LIST                    8
    
  /////////////////////////////////////////////
  
  // Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h> and <BlynkSimpleEsp8266_SSL_WM.h>
  
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

#define HOST_NAME   "ESP8266-DHT11-SSL"

#endif      //defines_h

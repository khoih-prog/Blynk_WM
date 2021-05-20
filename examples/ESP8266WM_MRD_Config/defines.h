/****************************************************************************************************************************
  defines.h for ESP8266WM_Config.ino
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

#define BLYNK_PRINT        Serial

#define BLYNK_WM_DEBUG     3

#define USING_MRD           true

#if USING_MRD
  // These definitions must be placed before #include <ESP_MultiResetDetector.h> to be used
  // Otherwise, default values (MRD_TIMES = 3, MRD_TIMEOUT = 10 seconds and MRD_ADDRESS = 0) will be used
  // Number of subsequent resets during MRD_TIMEOUT to activate
  #define MRD_TIMES               3
  
  // Number of seconds after reset during which a subseqent reset will be considered a mlti reset.
  #define MRD_TIMEOUT             10
  
  // RTC/EEPPROM Address for the MultiResetDetector to use
  #define MRD_ADDRESS             0

  #define MULTIRESETDETECTOR_DEBUG       true 
  
  #warning Using MultiResetDetector MRD
#else
  // These definitions must be placed before #include <ESP_DoubleResetDetector.h> to be used
  // Otherwise, default values (DRD_TIMEOUT = 10 seconds and DRD_ADDRESS = 0) will be used
  // Number of subsequent resets during DRD_TIMEOUT to activate
  
  // Number of seconds after reset during which a subseqent reset will be considered a mlti reset.
  #define DRD_TIMEOUT             10

// RTC/EEPPROM Address for the DoubleResetDetector to use
  #define DRD_ADDRESS             0

  #define DOUBLERESETDETECTOR_DEBUG     false
  
  #warning Using DoubleResetDetector DRD 
#endif

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
  #define EEPROM_START  768
#endif

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
//////////////////////////////////////////

#define USE_SSL   true
//#define USE_SSL   false

#if USE_SSL
  #include <BlynkSimpleEsp8266_SSL_WM.h>
#else
  #include <BlynkSimpleEsp8266_WM.h>
#endif

#define PIN_LED   2   // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
#define PIN_D2    4   // Pin D2 mapped to pin GPIO4 of ESP8266

#define DHT_PIN     PIN_D2
#define DHT_TYPE    DHT11

#define HOST_NAME   "8266-Master-Controller"

#endif      //defines_h

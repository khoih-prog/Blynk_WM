/****************************************************************************************************************************
   ESP_LED_BUILTINS.h Blynk_WM_Template.ino
   For ESP32/ESP8266 boards
   Written by Thor Johnson (https://github.com/thorathome) May 2020 as a template for
   Blynk Wifi ESP communications. See https://github.com/thorathome/Blynk_Examples
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

#ifndef ESP_LED_BUILTINS_h
#define ESP_LED_BUILTINS_h

// This is a simple Kludge that lets sketches be more device-independent
// Arduino for ESP8266 inverts the HIGH/LOW for the onboard LED_BUILTIN
// Use LED_BUILTIN_HIGH and LED_BUILTIN_LOW in your sketch and all will be right with the world

#if ESP8266  // There's a quirk in Arduino that has the LED_BUILTIN inverted. This corrects for it.
  #define LED_BUILTIN_HIGH      LOW
  #define LED_BUILTIN_LOW       HIGH
#else
  #define LED_BUILTIN_HIGH      HIGH
  #define LED_BUILTIN_LOW       LOW
#endif

// Also the ESP32 board manager files appear to NOT have LED_BUILTIN assigned correctly
// This fixes that
#if ESP32
  #ifdef LED_BUILTIN
    #undef LED_BUILTIN      
  #endif 
  #define LED_BUILTIN           13  // NOT DEFINED IN ESP32 BOARD FILES - HMMM.
#endif

#endif    //ESP_LED_BUILTINS_h

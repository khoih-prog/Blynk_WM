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

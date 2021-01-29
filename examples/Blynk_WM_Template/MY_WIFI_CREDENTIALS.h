/****************************************************************************************************************************
  MY_WIFI_CREDENTIALS.h Blynk_WM_Template.ino
  For ESP32/ESP8266 boards
  Written by Thor Johnson (https://github.com/thorathome) May 2020 as a template for
  Blynk Wifi ESP communications. See https://github.com/thorathome/Blynk_Examples
  Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license
  Version: 1.1.2

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
  1.1.2     K Hoang      28/01/2021 Fix Config Portal and Dynamic Params bugs
 *****************************************************************************************************************************/

/* MY_WIFI_CREDENTIALS.h

   Even if you use only one SSID/WiFiPassword, you may wish to keep it in a central place, out of your code.

   A simple way to manage SSIDs and WiFiPasswords you may wish to use...
     Put your WiFi credentials in a file you can #include in your Arduino sketches.
     Use a simple label like MY_SSID and MY_WIFI_PASSWORD in your code.

   Here's how...
     Create a new folder called MY_WIFI_CREDENTIALS in the Arduino/libraries folder
     Create a new text file named MY_WIFI_CREDENTIALS.h
     (Same as  as the folder. The .h is important.)

     Use this as a template.
     Edit in your own WiFi SSID(s) and WiFi Password(s)
*/

#ifndef MY_WIFI_CREDENTIALS_h
#define MY_WIFI_CREDENTIALS_h

#define MY_WIFI_SSID            "Serengeti"                       // network SSID (name)
#define MY_WIFI_PASSWORD        "hey-this is secret 9897%%&"      // network password

/* Comment out the credentials you do not use as regularly...
  #define MY_WIFI_SSID "Virus-Vault"                     // network SSID (name)
  #define MY_WIFI_PASSWORD "TwoFourSixEight2468!"        // network password
  #define MY_WIFI_SSID "MyAndroidPhone"                  // network SSID (name)
  #define MY_WIFI_PASSWORD "AndroidPassword66$"          // network password
*/

/*
 * * With the library file in place, restart your Arduino IDE.
 * * In each Arduino sketch, add the line
     #include "MY_WIFI_CREDENTIALS.h" // Use quotes " here.
 * * Write each sketch to use MY_SSID and MY_WIFI_PASSWORD throughout the sketch
 * * Compile and go

   This way,
 * * All your WiFi credentials are in one place where you can keep track of them.
 * * You are not hard-coding passwords in your sketches.
 * * You Arduino code becomes more portable because all sketches use MY_WIFI_CREDENTIALS.
 * * If you ever have to publish your code, your WiFi Credentials are not visible to everyone.
 * * You will be happier in life.
*/

#endif    //MY_WIFI_CREDENTIALS_h

/****************************************************************************************************************************
   MY_BLYNK_COLORS.h Blynk_WM_Template.ino
   For ESP32/ESP8266 boards
   Written by Thor Johnson (https://github.com/thorathome) May 2020 as a template for
   Blynk Wifi ESP communications. See https://github.com/thorathome/Blynk_Examples
   Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.16

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
 *****************************************************************************************************************************/

#ifndef MY_BLYNK_COLORS_h
#define MY_BLYNK_COLORS_h

// #include "MY_BLYNK_COLORS.h" 
// BLYNK COLOR PALETTE SAMPLE
#define BLYNK_GREEN             "#23C48E"
#define BLYNK_BLUE              "#04C0F8"
#define BLYNK_YELLOW            "#ED9D00"
#define BLYNK_RED               "#D3435C"
#define BLYNK_DARK_BLUE         "#5F7CD8"

#define BLYNK_WHITE             "#FFFFFF"
  
#define BLYNK_TEAL              "#00AE97"
#define BLYNK_REALLY_RED        "#F90000"
#define BLYNK_PLEASANT_GREEN    "#009140"
#define BLYNK_DK_GREY_BACKGRND  "#212266"

#endif    //MY_BLYNK_COLORS_h

/****************************************************************************************************************************
   MY_BLYNK_CREDENTIALS.h Blynk_WM_Template.ino
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

/* MY_BLYNK_CREDENTIALS.h

   Since Blynk requires a different Blynk Authcode for every device on every Blynking panel,
   I end up with a lot of Blynking Authcodes.

   A simple way to manage all the Blynk Authcodes you will likely generate...
   * Put them all in a library file you can #include in your Arduino sketches.
   * Name each of the Blynk Authcodes with a helpful name.
   * Select the right Blynk Authcode in each sketch without having to hard-code it.

   Here's how...
   * Create a new folder called MY_BLYNK_CREDENTIALS in your Arduino/libraries folder
  * Create a new text file named MY_BLYNK_CREDENTIALS.h
     (Same as as the folder. The .h is important.)

   * Use this as a template.
   * Edit in your own Blynk Authcodes with descriptive names for each of your projects or devices
*/


#ifndef MY_BLYNK_CREDENTIALS_h
#define MY_BLYNK_CREDENTIALS_h
        
#define MY_BLYNK_SERVER               "blynk-cloud.com"                     // You may or may not need this depending on your code
#define MY_WM_TEMPLATE_AUTHCODE       "0123456789abcdef0123456789abcdef"

// From my Blynk Panel 1 ( 3 devices )
#define MY_EXTERIOR_TEMP_AUTHCODE     "wtxxxxxxxxxxxxxxxxxxxxxxxxxxxxBS"  // Use your real Blynk Authcode here

#define MY_AC_DEV_AUTHCODE            "fnyyyyyyyyyyyyyyyyyyyyyyyyyyyy7t"  // Use your real Blynk Authcode here

#define MY_BARO_AUTHCODE              "_YzzzzzzzzzzzzzzzzzzzzzzzzzzzzRP"  // Use your real Blynk Authcode here


//From my Blynk Panel 2 ( 2 devices )
#define MY_IFTTT_DEMO_AUTHCODE        "_cbbbbbbbbbbbbbbbbbbbbbbbbbbbbsi"  // Use your real Blynk Authcode here
#define MY_SONOFF_DEV_AUTHCODE        "HWcccccccccccccccccccccccccccc7K"  // Use your real Blynk Authcode here


//From my Blynk Panel 3 ( 1 device )
#define MY_REAL_SONOFF_AUTHCODE       "Geddddddddddddddddddddddddddddqc"  // Use your real Blynk Authcode here


/*
 * * Once this library file is in place, restart your Arduino IDE.
 * * In each Arduino sketch, add the line
     #include "MY_BLYNK_AUTHCODES.h" // Use quotes " here.
 * * In all your sketches write something like
     #define MY_BLYNK_AUTHCODE MY_BARO_AUTHCODE //from your .h file.
 * * Write each sketch to use MY_BLYNK_AUTHCODE throughout the sketch
     instead of a hard-coded Blynk Authcode.
 * * Right after the #include "MY_BLYNK_AUTHCODES.h" statement, write a #define command to choose the
     correct Blynk Authcode.
 * * Compile and go

   This way,
 * * All Blynk Authcodes are in one place where you can keep track of them.
 * * You are not hard-coding Blynk Authcodes in your sketches.
 * * You Arduino code becomes more portable because all sketches use MY_BLYNK_AUTHCODE.
 * * If you ever have to publish your code, your Blynk Authcodes are not visible to everyone.
 * * You will be happier in life.
*/

#endif    //MY_BLYNK_CREDENTIALS_h

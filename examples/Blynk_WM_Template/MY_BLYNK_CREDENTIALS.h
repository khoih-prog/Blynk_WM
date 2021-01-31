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

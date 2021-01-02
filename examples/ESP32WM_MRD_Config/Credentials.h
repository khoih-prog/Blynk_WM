/****************************************************************************************************************************
   Credentials.h for ESP32WM_Config.ino
   For ESP32 boards

   Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.1.0

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
    1.1.0     K Hoang      01/01/2021 Add support to ESP32 LittleFS. Remove possible compiler warnings. Update examples
 *****************************************************************************************************************************/

#ifndef Credentials_h
#define Credentials_h

/// Start Default Config Data //////////////////

/*
  // Defined in <BlynkSimpleEsp32_WM.h> and <BlynkSimpleEsp32_SSL_WM.h>

  #define SSID_MAX_LEN      32
  #define PASS_MAX_LEN      64
  
  typedef struct
  {
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
  }  WiFi_Credentials;

  #define BLYNK_SERVER_MAX_LEN      32
  #define BLYNK_TOKEN_MAX_LEN       36

  typedef struct
  {
  char blynk_server[BLYNK_SERVER_MAX_LEN];
  char blynk_token [BLYNK_TOKEN_MAX_LEN];
  }  Blynk_Credentials;

  #define NUM_WIFI_CREDENTIALS      2
  #define NUM_BLYNK_CREDENTIALS     2

  typedef struct Configuration
  {
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char board_name     [24];
  int  checkSum;
  } Blynk_WM_Configuration;

*/

//bool LOAD_DEFAULT_CONFIG_DATA = true;
bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WM_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL  
  "SSL",
#else
  "NonSSL",
#endif
  //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
  //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
  "SSID1", "password1",
  "SSID2", "password2",
  // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
  "account.ddns.net",     "token",
  "account.duckdns.org",  "token1", 
  //int  blynk_port;
#if USE_SSL
  9443,
#else
  8080,
#endif
  //char board_name     [24];
  "Air-Control",
  //int  checkSum, dummy, not used
  0
};

/////////// End Default Config Data /////////////


#endif    //Credentials_h

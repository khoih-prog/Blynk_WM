/*******************************************************************************************************************************
  BlynkSimpleEsp8266_WM.h
  For ESP8266 boards

  Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license

  Original Blynk Library author:
  @file       BlynkSimpleEsp8266.h
  @author     Volodymyr Shymanskyy
  @license    This project is released under the MIT License (MIT)
  @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
  @date       Jan 2015
  @brief

  Version: 1.6.2

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
  1.1.3     K Hoang      31/01/2021 To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP
  1.2.0     K Hoang      24/02/2021 Add customs HTML header feature and support to ESP32-S2.
  1.3.0     K Hoang      19/04/2021 Add LittleFS and SPIFFS support to ESP32-S2. Add support to ESP32-C3 without LittleFS
                                    Fix SSL issue with Blynk Cloud Server
  1.3.1     K Hoang      24/04/2021 Fix issue of custom Blynk port (different from 8080 or 9443) not working on ESP32
  1.4.0     K Hoang      24/04/2021 Enable scan of WiFi networks for selection in Configuration Portal
  1.5.0     K Hoang      25/04/2021 Fix bug. Optimize and sync with Blynk_Async_WM library v1.5.0
  1.6.0     K Hoang      19/05/2021 Fix AP connect and SSL issues caused by breaking ESP8266 core v3.0.0
  1.6.1     K Hoang      29/06/2021 Fix issue with ESP8266 core v3.0.1
  1.6.2     K Hoang      10/10/2021  Update `platform.ini` and `library.json`  
 ********************************************************************************************************************************/


#ifndef BlynkSimpleEsp8266_WM_h
#define BlynkSimpleEsp8266_WM_h

#ifndef ESP8266
  #error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_WM_VERSION       "Blynk_WM for ESP8266 v1.6.2"

#include <version.h>

/////////////////////////////////////////////

#if (ARDUINO_ESP8266_GIT_VER == 0xcf6ff4c4)
  #define USING_ESP8266_CORE_VERSION    30002
  #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.2"
  #warning USING_ESP8266_CORE_VERSION "3.0.2"
#elif (ARDUINO_ESP8266_GIT_VER == 0xcbf44fb3)
  #define USING_ESP8266_CORE_VERSION    30001
  #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.1" 
  #warning USING_ESP8266_CORE_VERSION "3.0.1" 
#elif (ARDUINO_ESP8266_GIT_VER == 0xefb0341a)
  #define USING_ESP8266_CORE_VERSION    30000
  #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.0"
  #warning USING_ESP8266_CORE_VERSION "3.0.0"  
#elif (ARDUINO_ESP8266_GIT_VER == 0x2843a5ac)
  #define USING_ESP8266_CORE_VERSION    20704
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.4"
  #warning USING_ESP8266_CORE_VERSION "2.7.4"
#elif (ARDUINO_ESP8266_GIT_VER == 0x5d3af165)
  #define USING_ESP8266_CORE_VERSION    20703
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.3"
  #warning USING_ESP8266_CORE_VERSION "2.7.3"
#elif (ARDUINO_ESP8266_GIT_VER == 0x39c79d9b)
  #define USING_ESP8266_CORE_VERSION    20702
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.2"
  #warning USING_ESP8266_CORE_VERSION "2.7.2"
#elif (ARDUINO_ESP8266_GIT_VER == 0xa5432625)
  #define USING_ESP8266_CORE_VERSION    20701
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.1"
  #warning USING_ESP8266_CORE_VERSION "2.7.1"
#elif (ARDUINO_ESP8266_GIT_VER == 0x3d128e5c)
  #define USING_ESP8266_CORE_VERSION    20603
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.3"
  #warning USING_ESP8266_CORE_VERSION "2.6.3"
#elif (ARDUINO_ESP8266_GIT_VER == 0x482516e3)
  #define USING_ESP8266_CORE_VERSION    20602
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.2"
  #warning USING_ESP8266_CORE_VERSION "2.6.2"
#elif (ARDUINO_ESP8266_GIT_VER == 0x482516e3)
  #define USING_ESP8266_CORE_VERSION    20601
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.1"
  #warning USING_ESP8266_CORE_VERSION "2.6.1"
#elif (ARDUINO_ESP8266_GIT_VER == 0x643ec203)
  #define USING_ESP8266_CORE_VERSION    20600
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.0"
  #warning USING_ESP8266_CORE_VERSION "2.6.0"
#elif (ARDUINO_ESP8266_GIT_VER == 0x8b899c12)
  #define USING_ESP8266_CORE_VERSION    20502
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.5.2"
  #warning USING_ESP8266_CORE_VERSION "2.5.2"
#elif (ARDUINO_ESP8266_GIT_VER == 0x00000000)
  #define USING_ESP8266_CORE_VERSION    20402
  #define ESP8266_CORE_VERSION          "ESP8266 core v2.4.2"
  #warning USING_ESP8266_CORE_VERSION "2.4.2"
#elif (ARDUINO_ESP8266_GIT_VER == 0x643ec203)
  #define USING_ESP8266_CORE_VERSION    0
  #define ESP8266_CORE_VERSION          "ESP8266 core too old"
  #warning USING_ESP8266_CORE_VERSION "0.0.0"
#else
  #define USING_ESP8266_CORE_VERSION    999999
  #define ESP8266_CORE_VERSION          "ESP8266 core unknown"
  #warning USING_ESP8266_CORE_VERSION "x.y.z"  
#endif

//////////////////////////////////////////////
// From v1.6.0 to display correct BLYNK_INFO_DEVICE

#define BLYNK_USE_128_VPINS

#if defined(BLYNK_INFO_DEVICE)
  #undef BLYNK_INFO_DEVICE
#endif

#define BLYNK_BUFFERS_SIZE    4096

#if defined(BLYNK_INFO_DEVICE)
  #undef BLYNK_INFO_DEVICE
#endif

#if defined(ARDUINO_BOARD)
  #define BLYNK_INFO_DEVICE   ARDUINO_BOARD
#elif defined(BOARD_NAME)
  #define BLYNK_INFO_DEVICE   BOARD_NAME
#elif defined(BOARD_TYPE)
  #define BLYNK_INFO_DEVICE   BOARD_TYPE
#else
  #define BLYNK_INFO_DEVICE   "ESP8266"
#endif

/////////////////////////////////////////////

#if ESP_SDK_VERSION_NUMBER < 0x020200
#error Please update your ESP8266 Arduino Core
#endif

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>

#include <ESP8266WebServer.h>

//default to use EEPROM, otherwise, use LittleFS or SPIFFS
#if ( USE_LITTLEFS || USE_SPIFFS )

  #if USE_LITTLEFS
    #define FileFS    LittleFS
    #warning Using LittleFS in BlynkSimpleESP8266_WM.h
  #else
    #define FileFS    SPIFFS
    #warning Using SPIFFS in BlynkSimpleESP8266_WM.h
  #endif

  #include <FS.h>
  #include <LittleFS.h>
#else
  #include <EEPROM.h>
  #warning Using EEPROM in BlynkSimpleESP8266_WM.h
#endif

//////////////////////////////////////////////

// New from v1.4.0
// KH, Some minor simplification
#if !defined(SCAN_WIFI_NETWORKS)
  #define SCAN_WIFI_NETWORKS     true     //false
#endif
	
#if SCAN_WIFI_NETWORKS
  #warning Using SCAN_WIFI_NETWORKS
  
  #if !defined(MANUAL_SSID_INPUT_ALLOWED)
    #define MANUAL_SSID_INPUT_ALLOWED     true
  #endif

  #if !defined(MAX_SSID_IN_LIST)
    #define MAX_SSID_IN_LIST     10
  #elif (MAX_SSID_IN_LIST < 2)
    #warning Parameter MAX_SSID_IN_LIST defined must be >= 2 - Reset to 10
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      10
  #elif (MAX_SSID_IN_LIST > 15)
    #warning Parameter MAX_SSID_IN_LIST defined must be <= 15 - Reset to 10
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      10
  #endif
#else
  #warning SCAN_WIFI_NETWORKS disabled	
#endif

///////// NEW for DRD /////////////

#if !defined(USING_MRD)
  #define USING_MRD       false
#endif

#if USING_MRD

  ///////// NEW for MRD /////////////
  // These defines must be put before #include <ESP_DoubleResetDetector.h>
  // to select where to store DoubleResetDetector's variable.
  // For ESP32, You must select one to be true (EEPROM or SPIFFS/LittleFS)
  // For ESP8266, You must select one to be true (RTC, EEPROM or SPIFFS/LittleFS)
  // Otherwise, library will use default EEPROM storage
  #define ESP8266_MRD_USE_RTC     false   //true

  #if USE_LITTLEFS
    #define ESP_MRD_USE_LITTLEFS    true
    #define ESP_MRD_USE_SPIFFS      false
    #define ESP_MRD_USE_EEPROM      false
  #elif USE_SPIFFS
    #define ESP_MRD_USE_LITTLEFS    false
    #define ESP_MRD_USE_SPIFFS      true
    #define ESP_MRD_USE_EEPROM      false
  #else
    #define ESP_MRD_USE_LITTLEFS    false
    #define ESP_MRD_USE_SPIFFS      false
    #define ESP_MRD_USE_EEPROM      true
  #endif

  #ifndef MULTIRESETDETECTOR_DEBUG
    #define MULTIRESETDETECTOR_DEBUG     false
  #endif
  
  // These definitions must be placed before #include <ESP_MultiResetDetector.h> to be used
  // Otherwise, default values (MRD_TIMES = 3, MRD_TIMEOUT = 10 seconds and MRD_ADDRESS = 0) will be used
  // Number of subsequent resets during MRD_TIMEOUT to activate
  #ifndef MRD_TIMES
    #define MRD_TIMES               3
  #endif

  // Number of seconds after reset during which a
  // subsequent reset will be considered a double reset.
  #ifndef MRD_TIMEOUT
    #define MRD_TIMEOUT 10
  #endif

  // EEPROM Memory Address for the MultiResetDetector to use
  #ifndef MRD_TIMEOUT
    #define MRD_ADDRESS 0
  #endif
  
  #include <ESP_MultiResetDetector.h>      //https://github.com/khoih-prog/ESP_MultiResetDetector

  //MultiResetDetector mrd(MRD_TIMEOUT, MRD_ADDRESS);
  MultiResetDetector* mrd;

  ///////// NEW for MRD /////////////
  
#else

  ///////// NEW for DRD /////////////
  // These defines must be put before #include <ESP_DoubleResetDetector.h>
  // to select where to store DoubleResetDetector's variable.
  // For ESP32, You must select one to be true (EEPROM or SPIFFS/LittleFS)
  // For ESP8266, You must select one to be true (RTC, EEPROM or SPIFFS/LittleFS)
  // Otherwise, library will use default EEPROM storage
  #define ESP8266_DRD_USE_RTC     false   //true

  #if USE_LITTLEFS
    #define ESP_DRD_USE_LITTLEFS    true
    #define ESP_DRD_USE_SPIFFS      false
    #define ESP_DRD_USE_EEPROM      false
  #elif USE_SPIFFS
    #define ESP_DRD_USE_LITTLEFS    false
    #define ESP_DRD_USE_SPIFFS      true
    #define ESP_DRD_USE_EEPROM      false
  #else
    #define ESP_DRD_USE_LITTLEFS    false
    #define ESP_DRD_USE_SPIFFS      false
    #define ESP_DRD_USE_EEPROM      true
  #endif

  #ifndef DOUBLERESETDETECTOR_DEBUG
    #define DOUBLERESETDETECTOR_DEBUG     false
  #endif

  // Number of seconds after reset during which a
  // subsequent reset will be considered a double reset.
  #define DRD_TIMEOUT 10

  // RTC Memory Address for the DoubleResetDetector to use
  #define DRD_ADDRESS 0
  
  #include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

  //DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
  DoubleResetDetector* drd;

  ///////// NEW for DRD /////////////

#endif


#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;

#if USE_DYNAMIC_PARAMETERS
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#endif

#define SSID_MAX_LEN      32
//From v1.0.10, WPA2 passwords can be up to 63 characters long.
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

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 2 + (2 * NUM_WIFI_CREDENTIALS) + (2 * NUM_BLYNK_CREDENTIALS) )

#define HEADER_MAX_LEN            16
#define BOARD_NAME_MAX_LEN        24

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} Blynk_WM_Configuration;

// Currently CONFIG_DATA_SIZE  =  ( 48 + (96 * NUM_WIFI_CREDENTIALS) + (68 * NUM_BLYNK_CREDENTIALS) ) = 376

uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WM_Configuration);

///New from v1.0.13
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Blynk_WM_Configuration defaultConfig;

//From v1.0.10, Permit special chars such as # and %
// -- HTML page fragments

const char BLYNK_WM_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>BlynkSimpleEsp8266_WM</title>";

const char BLYNK_WM_HTML_HEAD_STYLE[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

const char BLYNK_WM_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style='text-align:left;display:inline-block;min-width:260px;'>\
<fieldset><div><label>*WiFi SSID</label>[[input_id]]<div></div></div>\
<div><label>*PWD (8+ chars)</label><input value='[[pw]]'id='pw'><div></div></div>\
<div><label>*WiFi SSID1</label>[[input_id1]]<div></div></div>\
<div><label>*PWD1 (8+ chars)</label><input value='[[pw1]]'id='pw1'><div></div></div></fieldset>\
<fieldset><div><label>Blynk Server</label><input value='[[sv]]'id='sv'><div></div></div>\
<div><label>Token</label><input value='[[tk]]'id='tk'><div></div></div>\
<div><label>Blynk Server1</label><input value='[[sv1]]'id='sv1'><div></div></div>\
<div><label>Token1</label><input value='[[tk1]]'id='tk1'><div></div></div>\
<div><label>Port</label><input value='[[pt]]'id='pt'><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value='[[nm]]'id='nm'><div></div></div></fieldset>"; 	// DO NOT CHANGE THIS STRING EVER!!!!

const char BLYNK_WM_HTML_INPUT_ID[]   /*PROGMEM*/ = "<input value='[[id]]' id='id'>";
const char BLYNK_WM_HTML_INPUT_ID1[]  /*PROGMEM*/ = "<input value='[[id1]]' id='id1'>";

const char BLYNK_WM_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char BLYNK_WM_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char BLYNK_WM_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char BLYNK_WM_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick='sv()'>Save</button></div>";
const char BLYNK_WM_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id='jsbin-javascript'>\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('sv',document.getElementById('sv').value);udVal('tk',document.getElementById('tk').value);\
udVal('sv1',document.getElementById('sv1').value);udVal('tk1',document.getElementById('tk1').value);\
udVal('pt',document.getElementById('pt').value);udVal('nm',document.getElementById('nm').value);";

const char BLYNK_WM_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char BLYNK_WM_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char BLYNK_WM_HTML_END[]          /*PROGMEM*/ = "</html>";

#if SCAN_WIFI_NETWORKS
const char BLYNK_WM_SELECT_START[]      /*PROGMEM*/ = "<select id=";
const char BLYNK_WM_SELECT_END[]        /*PROGMEM*/ = "</select>";
const char BLYNK_WM_DATALIST_START[]    /*PROGMEM*/ = "<datalist id=";
const char BLYNK_WM_DATALIST_END[]      /*PROGMEM*/ = "</datalist>";
const char BLYNK_WM_OPTION_START[]      /*PROGMEM*/ = "<option>";
const char BLYNK_WM_OPTION_END[]        /*PROGMEM*/ = "";			// "</option>"; is not required
const char BLYNK_WM_NO_NETWORKS_FOUND[] /*PROGMEM*/ = "No suitable WiFi networks available!";
#endif

//////////////////////////////////////////

//KH Add repeatedly used const
//KH, from v1.2.0
const char WM_HTTP_HEAD_CL[]         = "Content-Length";
const char WM_HTTP_HEAD_TEXT_HTML[]  = "text/html";
const char WM_HTTP_HEAD_TEXT_PLAIN[] = "text/plain";
const char WM_HTTP_CACHE_CONTROL[]   = "Cache-Control";
const char WM_HTTP_NO_STORE[]        = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          = "Pragma";
const char WM_HTTP_NO_CACHE[]        = "no-cache";
const char WM_HTTP_EXPIRES[]         = "Expires";
const char WM_HTTP_CORS[]            = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  = "*";

//////////////////////////////////////////

#define BLYNK_SERVER_HARDWARE_PORT    8080

#define BLYNK_BOARD_TYPE    "ESP8266"
#define NO_CONFIG           "blank"

class BlynkWifi
  : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
  public:
    BlynkWifi(BlynkArduinoClient& transp)
      : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
      BLYNK_LOG2(BLYNK_F("Con2:"), ssid);
      WiFi.mode(WIFI_STA);

      // New from Blynk_WM v1.0.5
      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        BLYNK_LOG1(BLYNK_F("UseStatIP"));
        WiFi.config(static_IP, static_GW, static_SN, static_DNS1, static_DNS2);
      }

      setHostname();

      if (WiFi.status() != WL_CONNECTED)
      {
        if (pass && strlen(pass))
        {
          WiFi.begin(ssid, pass);
        } else
        {
          WiFi.begin(ssid);
        }
      }
      while (WiFi.status() != WL_CONNECTED)
      {
        BlynkDelay(500);
      }

      BLYNK_LOG1(BLYNK_F("Conn2WiFi"));
      displayWiFiData();
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, domain, port);
      while (this->connect() != true) {}
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, ip, port);
      while (this->connect() != true) {}
    }

    // For ESP8266
#define LED_ON      LOW
#define LED_OFF     HIGH

// New from v1.3.0
#if !defined(REQUIRE_ONE_SET_SSID_PW)
  #define REQUIRE_ONE_SET_SSID_PW     false
#endif

#define PASSWORD_MIN_LEN        8

    void begin(const char *iHostname = "")
    {
#define TIMEOUT_CONNECT_WIFI			30000

      //Turn OFF
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LED_OFF);
      
#if USING_MRD
      //// New MRD ////
      mrd = new MultiResetDetector(MRD_TIMEOUT, MRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (mrd->detectMultiReset())
#else      
      //// New DRD ////
      drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
#endif
      {
#if ( BLYNK_WM_DEBUG > 1)
        BLYNK_LOG1(BLYNK_F("Multi or Double Reset Detected"));
#endif      
        noConfigPortal = false;
      }
      //// New DRD/MRD ////
      
#if ( BLYNK_WM_DEBUG > 2)    
      if (LOAD_DEFAULT_CONFIG_DATA) 
      {   
        BLYNK_LOG1(BLYNK_F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
#endif

      WiFi.mode(WIFI_STA);

      if (iHostname[0] == 0)
      {
        String _hostname = "ESP8266-" + String(ESP.getChipId(), HEX);
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());
      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }

      BLYNK_LOG2(BLYNK_F("Hostname="), RFC952_hostname);
          
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();
      
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      //if (getConfigData() && noConfigPortal)
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;
        
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(noConfigPortal? BLYNK_F("bg: noConfigPortal = true") : BLYNK_F("bg: noConfigPortal = false"));
#endif        
        
        for (uint16_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
        {
          wifiMulti.addAP(Blynk8266_WM_config.WiFi_Creds[i].wifi_ssid, Blynk8266_WM_config.WiFi_Creds[i].wifi_pw);
        }

        if (connectMultiWiFi() == WL_CONNECTED)
        {
          BLYNK_LOG1(BLYNK_F("bg: WiFi OK. Try Blynk"));

          int i = 0;
          while ( (i++ < 10) && !connectMultiBlynk() )
          {
          }

          if  (connected())
          {
            BLYNK_LOG1(BLYNK_F("bg: WiFi+Blynk OK"));
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("bg: WiFi OK, Blynk not"));
            // failed to connect to Blynk server, will start configuration mode
            startConfigurationMode();
          }
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("bg: Fail2connect WiFi+Blynk"));
          // failed to connect to Blynk server, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      { 
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(isForcedConfigPortal? BLYNK_F("bg: isForcedConfigPortal = true") : BLYNK_F("bg: isForcedConfigPortal = false"));
#endif
                                       
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
        }
        else
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-non-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
          clearForcedCP();
          
        }
          
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to Blynk server, will start configuration mode
        startConfigurationMode();
      }
    }

#ifndef TIMEOUT_RECONNECT_WIFI
  #define TIMEOUT_RECONNECT_WIFI   10000L
#else
    // Force range of user-defined TIMEOUT_RECONNECT_WIFI between 10-60s
  #if (TIMEOUT_RECONNECT_WIFI < 10000L)
    #warning TIMEOUT_RECONNECT_WIFI too low. Reseting to 10000
    #undef TIMEOUT_RECONNECT_WIFI
    #define TIMEOUT_RECONNECT_WIFI   10000L
  #elif (TIMEOUT_RECONNECT_WIFI > 60000L)
    #warning TIMEOUT_RECONNECT_WIFI too high. Reseting to 60000
    #undef TIMEOUT_RECONNECT_WIFI
    #define TIMEOUT_RECONNECT_WIFI   60000L
  #endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
  #define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
  // Force range of user-defined TIMES_BEFORE_RESET between 2-100
  #if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
  #elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Reseting to 100
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
  #endif
#endif

    void run()
    {
      static int retryTimes = 0;
      
#if USING_MRD
      //// New MRD ////
      // Call the mulyi reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call mrd.stop() when you wish to no longer
      // consider the next reset as a multi reset.
      mrd->loop();
      //// New MRD ////
#else      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
#endif

      // Lost connection in running. Give chance to reconfig.
      if ( WiFi.status() != WL_CONNECTED || !connected() )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi / Blynk.
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
            server->handleClient();

          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
#if ( BLYNK_WM_DEBUG > 2)                   
            BLYNK_LOG1(BLYNK_F("r:Check RESET_IF_CONFIG_TIMEOUT"));
#endif
          
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              BLYNK_LOG2(BLYNK_F("run: WiFi lost, configTimeout. Connect WiFi+Blynk. Retry#:"), retryTimes);
            }
            else
            {
              ESP.reset();
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          if ( WiFi.status() != WL_CONNECTED )
          {
            BLYNK_LOG1(BLYNK_F("run: WiFi lost. Reconnect WiFi+Blynk"));
            if (connectMultiWiFi() == WL_CONNECTED)
            {
              // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LED_OFF);

              BLYNK_LOG1(BLYNK_F("run: WiFi reconnected. Connect to Blynk"));

              if (connectMultiBlynk())
              {
                BLYNK_LOG1(BLYNK_F("run: WiFi+Blynk reconnected"));
              }
            }
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("run: Blynk lost. Try Blynk"));

            if (connectMultiBlynk())
            {
              // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LED_OFF);
              BLYNK_LOG1(BLYNK_F("run: Blynk reconnected"));
            }
          }

          //BLYNK_LOG1(BLYNK_F("run: Lost connection => configMode"));
          //startConfigurationMode();
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        BLYNK_LOG1(BLYNK_F("run: got WiFi+Blynk back"));
        // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
        digitalWrite(LED_BUILTIN, LED_OFF);
      }

      if (connected())
      {
        Base::run();
      }
    }

    void setHostname()
    {
      if (RFC952_hostname[0] != 0)
      {
        WiFi.hostname(RFC952_hostname);
      }
    }

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }

    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }

#define MIN_WIFI_CHANNEL      1
#define MAX_WIFI_CHANNEL      11

    int setConfigPortalChannel(int channel = 1)
    {
      // If channel < MIN_WIFI_CHANNEL - 1 or channel > MAX_WIFI_CHANNEL => channel = 1
      // If channel == 0 => will use random channel from MIN_WIFI_CHANNEL to MAX_WIFI_CHANNEL
      // If (MIN_WIFI_CHANNEL <= channel <= MAX_WIFI_CHANNEL) => use it
      if ( (channel < MIN_WIFI_CHANNEL - 1) || (channel > MAX_WIFI_CHANNEL) )
        WiFiAPChannel = 1;
      else if ( (channel >= MIN_WIFI_CHANNEL - 1) && (channel <= MAX_WIFI_CHANNEL) )
        WiFiAPChannel = channel;

      return WiFiAPChannel;
    }
    
    void setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn = IPAddress(255, 255, 255, 0),
                              IPAddress dns_address_1 = IPAddress(0, 0, 0, 0),
                              IPAddress dns_address_2 = IPAddress(0, 0, 0, 0))
    {
      static_IP     = ip;
      static_GW     = gw;
      static_SN     = sn;

      // Default to local GW
      if (dns_address_1 == IPAddress(0, 0, 0, 0))
        static_DNS1   = gw;
      else
        static_DNS1   = dns_address_1;

      // Default to Google DNS (8, 8, 8, 8)
      if (dns_address_2 == IPAddress(0, 0, 0, 0))
        static_DNS2   = IPAddress(8, 8, 8, 8);
      else
        static_DNS2   = dns_address_2;
    }

    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.WiFi_Creds[index].wifi_ssid));
    }

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.WiFi_Creds[index].wifi_pw));
    }

    String getServerName(uint8_t index)
    {
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");

      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.Blynk_Creds[index].blynk_server));
    }

    String getToken(uint8_t index)
    {
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");

      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.Blynk_Creds[index].blynk_token));
    }

    String getBoardName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.board_name));
    }

    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (Blynk8266_WM_config.blynk_port);
    }

    Blynk_WM_Configuration* getFullConfigData(Blynk_WM_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Blynk8266_WM_config, sizeof(Blynk_WM_Configuration));

      return (configData);
    }

    void clearConfigData()
    {
      memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
      saveConfigData();
    }

    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      ESP.reset();
    }
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      ESP.reset();
    }
    
    //////////////////////////////////////
    
    // Add customs headers from v1.2.0
    
    // New from v1.2.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"

#if USING_CUSTOMS_STYLE
    //sets a custom style, such as color
    // "<style>div,input{padding:5px;font-size:1em;}
    // input{width:95%;}body{text-align: center;}
    // button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}
    // fieldset{border-radius:0.3rem;margin:0px;}</style>";
    void setCustomsStyle(const char* CustomsStyle = BLYNK_WM_HTML_HEAD_STYLE) 
    {
      BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE = CustomsStyle;
      BLYNK_LOG2(BLYNK_F("Set CustomsStyle to : "), BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    //////////////////////////////////////
    
    const char* getCustomsStyle()
    {
      BLYNK_LOG2(BLYNK_F("Get CustomsStyle = "), BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE);
      return BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif

    //////////////////////////////////////

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = NULL) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      BLYNK_LOG2(BLYNK_F("Set CustomsHeadElement to : "), _CustomsHeadElement);
    }
    
    //////////////////////////////////////
    
    const char* getCustomsHeadElement()
    {
      BLYNK_LOG2(BLYNK_F("Get CustomsHeadElement = "), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif

    //////////////////////////////////////
    
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = NULL)
    {     
      _CORS_Header = CORSHeaders;

      BLYNK_LOG2(BLYNK_F("Set CORS Header to : "), _CORS_Header);
    }
    
    //////////////////////////////////////
    
    const char* getCORSHeader()
    {      
      BLYNK_LOG2(BLYNK_F("Get CORS Header = "), _CORS_Header);
      return _CORS_Header;
    }
#endif
          
    //////////////////////////////////////


  private:
  
    ESP8266WebServer *server;
    bool configuration_mode = false;

    ESP8266WiFiMulti wifiMulti;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;
    
    // default to channel 1
    int WiFiAPChannel = 1;

    Blynk_WM_Configuration Blynk8266_WM_config;
    
    uint16_t totalDataSize = 0;

    // For Config Portal, from Blynk_WM v1.0.5
    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);

    String portal_ssid = "";
    String portal_pass = "";

    // For static IP, from Blynk_WM v1.0.5
    IPAddress static_IP   = IPAddress(0, 0, 0, 0);
    IPAddress static_GW   = IPAddress(0, 0, 0, 0);
    IPAddress static_SN   = IPAddress(255, 255, 255, 0);
    IPAddress static_DNS1 = IPAddress(0, 0, 0, 0);
    IPAddress static_DNS2 = IPAddress(0, 0, 0, 0);

/////////////////////////////////////
    
    // Add customs headers from v1.2.0
    
#if USING_CUSTOMS_STYLE
    const char* BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE = NULL;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = NULL;
#endif
    
#if USING_CORS_FEATURE    
    const char* _CORS_Header        = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif
       
    //////////////////////////////////////
    // Add WiFi Scan from v1.4.0
    
#if SCAN_WIFI_NETWORKS
    int WiFiNetworksFound = 0;		// Number of SSIDs found by WiFi scan, including low quality and duplicates
    int *indices;					        // WiFi network data, filled by scan (SSID, BSSID)
    String ListOfSSIDs = "";		  // List of SSIDs found by scan, in HTML <option> format
#endif

    //////////////////////////////////////
    
#define RFC952_HOSTNAME_MAXLEN      24

    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }
    
    //////////////////////////////////////////////

    void displayConfigData(Blynk_WM_Configuration configData)
    {
      BLYNK_LOG4(BLYNK_F("Hdr="),       configData.header,
                 BLYNK_F(",BrdName="),  configData.board_name);
      BLYNK_LOG4(BLYNK_F("SSID="),      configData.WiFi_Creds[0].wifi_ssid,
                 BLYNK_F(",PW="),       configData.WiFi_Creds[0].wifi_pw);
      BLYNK_LOG4(BLYNK_F("SSID1="),     configData.WiFi_Creds[1].wifi_ssid,
                 BLYNK_F(",PW1="),      configData.WiFi_Creds[1].wifi_pw);
      BLYNK_LOG4(BLYNK_F("Server="),    configData.Blynk_Creds[0].blynk_server,
                 BLYNK_F(",Token="),    configData.Blynk_Creds[0].blynk_token);
      BLYNK_LOG4(BLYNK_F("Server1="),   configData.Blynk_Creds[1].blynk_server,
                 BLYNK_F(",Token1="),   configData.Blynk_Creds[1].blynk_token);
      BLYNK_LOG2(BLYNK_F("Port="),      configData.blynk_port);
      BLYNK_LOG1(BLYNK_F("======= End Config Data ======="));
    }
    
    //////////////////////////////////////////////

    void displayWiFiData()
    {
      BLYNK_LOG6(BLYNK_F("IP="), WiFi.localIP().toString(), BLYNK_F(",GW="), WiFi.gatewayIP().toString(),
                 BLYNK_F(",SN="), WiFi.subnetMask().toString());
      BLYNK_LOG4(BLYNK_F("DNS1="), WiFi.dnsIP(0).toString(), BLYNK_F(",DNS2="), WiFi.dnsIP(1).toString());
    }
    
    //////////////////////////////////////////////

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Blynk8266_WM_config) - sizeof(Blynk8266_WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Blynk8266_WM_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
       
    bool isWiFiConfigValid()
    {
      #if REQUIRE_ONE_SET_SSID_PW
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => return false
      // Only need 1 set of valid SSID/PWD
      if (!( ( ( strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, NO_CONFIG, strlen(NO_CONFIG)) && strlen(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) >  0 )  &&
             (   strlen(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw) >= PASSWORD_MIN_LEN ) ) ||
             ( ( strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, NO_CONFIG, strlen(NO_CONFIG)) && strlen(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) >  0 )  &&
               ( strlen(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw) >= PASSWORD_MIN_LEN ) ) ))
      #else
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => invalid set
      // Need both sets of valid SSID/PWD
      if ( !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,   NO_CONFIG, strlen(NO_CONFIG) )  ||
           !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,     NO_CONFIG, strlen(NO_CONFIG) )  ||
           !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,   NO_CONFIG, strlen(NO_CONFIG) )  ||
           !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,     NO_CONFIG, strlen(NO_CONFIG) )  ||
           ( strlen(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) == 0 ) || 
           ( strlen(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) == 0 ) ||
           ( strlen(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw)   < PASSWORD_MIN_LEN ) ||
           ( strlen(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw)   < PASSWORD_MIN_LEN ) )
      #endif     
      {
        // If SSID, PW ="blank" or NULL, set the flag
        BLYNK_LOG1(BLYNK_F("Invalid Stored WiFi Config Data"));
        
        // Nullify the invalid data to avoid displaying garbage
        memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
        
        hadConfigData = false;
        
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

#if ( USE_LITTLEFS || USE_SPIFFS )

#define  CONFIG_FILENAME                  BLYNK_F("/wm_config.dat")
#define  CONFIG_FILENAME_BACKUP           BLYNK_F("/wm_config.bak")

#define  CREDENTIALS_FILENAME             BLYNK_F("/wm_cred.dat")
#define  CREDENTIALS_FILENAME_BACKUP      BLYNK_F("/wm_cred.bak")

#define  CONFIG_PORTAL_FILENAME           BLYNK_F("/wm_cp.dat")
#define  CONFIG_PORTAL_FILENAME_BACKUP    BLYNK_F("/wm_cp.bak")

    //////////////////////////////////////////////
    
    void saveForcedCP(uint32_t value)
    {
      File file = FileFS.open(CONFIG_PORTAL_FILENAME, "w");
      
      BLYNK_LOG1(BLYNK_F("SaveCPFile "));

      if (file)
      {
        file.write((uint8_t*) &value, sizeof(value));
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }

      // Trying open redundant CP file
      file = FileFS.open(CONFIG_PORTAL_FILENAME_BACKUP, "w");
      
      BLYNK_LOG1(BLYNK_F("SaveBkUpCPFile "));

      if (file)
      {
        file.write((uint8_t *) &value, sizeof(value));
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(isPersistent ? BLYNK_F("setForcedCP Persistent") : BLYNK_F("setForcedCP non-Persistent"));
#endif
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("clearForcedCP"));
#endif
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("Check if isForcedCP"));
#endif
      
      File file = FileFS.open(CONFIG_PORTAL_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("LoadCPFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CONFIG_PORTAL_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("LoadBkUpCPFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
       }

      file.readBytes((char *) &readForcedConfigPortalFlag, sizeof(readForcedConfigPortalFlag));

      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      char* readBuffer;
           
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("LoadCredFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("LoadBkUpCredFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      uint16_t maxBufferLength = 0;
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see NULL => stop and return false
        if (readBuffer == NULL)
        {
          BLYNK_LOG1(BLYNK_F("ChkCrR: Error can't allocate buffer."));
          return false;
        }
#if ( BLYNK_WM_DEBUG > 2)          
        else
        {
          BLYNK_LOG2(BLYNK_F("ChkCrR: Buffer allocated, sz="), maxBufferLength + 1);
        }
#endif             
      }
     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;

        // Actual size of pdata is [maxlen + 1]
        memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
        
        file.readBytes(_pointer, myMenuItems[i].maxlen);

#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);
#endif          
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.readBytes((char *) &readCheckSum, sizeof(readCheckSum));
      
      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      // Free buffer
      if (readBuffer != NULL)
      {
        free(readBuffer);
        BLYNK_LOG1(BLYNK_F("Buffer freed"));
      }
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////

    bool loadDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(Blynk8266_WM_config) + sizeof(readCheckSum);
      
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("LoadCredFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("LoadBkUpCredFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
      }
     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;

        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
        
        file.readBytes(_pointer, myMenuItems[i].maxlen);

#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("CrR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif          
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.readBytes((char *) &readCheckSum, sizeof(readCheckSum));
      
      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    //////////////////////////////////////////////
    
    void saveDynamicData()
    {
      int checkSum = 0;
    
      File file = FileFS.open(CREDENTIALS_FILENAME, "w");
      BLYNK_LOG1(BLYNK_F("SaveCredFile "));

      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;

#if ( BLYNK_WM_DEBUG > 2)          
        BLYNK_LOG4(BLYNK_F("CW1:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif
        
        if (file)
        {
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen);         
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));    
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }   
           
      BLYNK_LOG2(BLYNK_F("CrWCSum=0x"), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "w");
      BLYNK_LOG1(BLYNK_F("SaveBkUpCredFile "));

      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;

#if ( BLYNK_WM_DEBUG > 2)         
        BLYNK_LOG4(BLYNK_F("CW2:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif
        
        if (file)
        {
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen);         
        }
        else
        {
          BLYNK_LOG1(BLYNK_F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));    
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }   
    }
#endif

    //////////////////////////////////////////////

    bool loadConfigData()
    {
      File file = FileFS.open(CONFIG_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("LoadCfgFile "));

      if (!file)
      {
        BLYNK_LOG1(BLYNK_F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CONFIG_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("LoadBkUpCfgFile "));

        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("failed"));
          return false;
        }
      }

      file.readBytes((char *) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));

      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();
      
      return isWiFiConfigValid();
    }
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      File file = FileFS.open(CONFIG_FILENAME, "w");
      BLYNK_LOG1(BLYNK_F("SaveCfgFile "));

      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;
      BLYNK_LOG2(BLYNK_F("WCSum=0x"), String(calChecksum, HEX));

      if (file)
      {
        file.write((uint8_t*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }

      // Trying open redundant Auth file
      file = FileFS.open(CONFIG_FILENAME_BACKUP, "w");
      BLYNK_LOG1(BLYNK_F("SaveBkUpCfgFile "));

      if (file)
      {
        file.write((uint8_t *) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));
        file.close();
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void saveAllConfigData()
    {
      saveConfigData();     
      
#if USE_DYNAMIC_PARAMETERS      
      saveDynamicData();
#endif      
    }
    
    //////////////////////////////////////////////
    
    // Return false if init new EEPROM, LittleFS or SPIFFS. No more need trying to connect. Go directly to config mode
    bool getConfigData()
    {
      bool dynamicDataValid = true; 
      int calChecksum;  
      
      hadConfigData = false;
      
      if (!FileFS.begin())
      {
        FileFS.format();
        
        if (!FileFS.begin())
        {
#if USE_LITTLEFS
          BLYNK_LOG1(BLYNK_F("LittleFS failed!. Please use SPIFFS or EEPROM."));
#else
          BLYNK_LOG1(BLYNK_F("SPIFFS failed!. Please use LittleFS or EEPROM."));
#endif 
          return false;
        }
      }

      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load Config Data from Sketch
        memcpy(&Blynk8266_WM_config, &defaultConfig, sizeof(Blynk8266_WM_config));
        strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        
        // Including config and dynamic data, and assume valid
        saveAllConfigData();
        
#if ( BLYNK_WM_DEBUG > 2)      
        BLYNK_LOG1(BLYNK_F("======= Start Loaded Config Data ======="));
        displayConfigData(Blynk8266_WM_config);
#endif

        // Don't need Config Portal anymore
        return true; 
      }
#if USE_DYNAMIC_PARAMETERS    
      else if ( ( FileFS.exists(CONFIG_FILENAME)      || FileFS.exists(CONFIG_FILENAME_BACKUP) ) &&
                ( FileFS.exists(CREDENTIALS_FILENAME) || FileFS.exists(CREDENTIALS_FILENAME_BACKUP) ) )
#else
      else if ( FileFS.exists(CONFIG_FILENAME) || FileFS.exists(CONFIG_FILENAME_BACKUP) )
#endif
      {
        // if config file exists, load
        // Get config data. If "blank" or NULL, set false flag and exit
        if (!loadConfigData())
        {
          return false;
        }
        
#if ( BLYNK_WM_DEBUG > 2)      
        BLYNK_LOG1(BLYNK_F("======= Start Stored Config Data ======="));
        displayConfigData(Blynk8266_WM_config);
#endif

        calChecksum = calcChecksum();

        BLYNK_LOG4(BLYNK_F("CCSum=0x"), String(calChecksum, HEX),
                   BLYNK_F(",RCSum=0x"), String(Blynk8266_WM_config.checkSum, HEX));

#if USE_DYNAMIC_PARAMETERS                 
        // Load dynamic data
        dynamicDataValid = loadDynamicData();
        
        if (dynamicDataValid)
        {
  #if ( BLYNK_WM_DEBUG > 2)      
          BLYNK_LOG1(BLYNK_F("Valid Stored Dynamic Data"));
  #endif          
        }
  #if ( BLYNK_WM_DEBUG > 2)  
        else
        {
          BLYNK_LOG1(BLYNK_F("Invalid Stored Dynamic Data. Ignored"));
        }
  #endif
#endif
      }
      else    
      {
        // Not loading Default config data, but having no config file => Config Portal
        return false;
      }    
      
      if ( (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WM_config.checkSum) || !dynamicDataValid )
                      
      {         
        // Including Credentials CSum
        BLYNK_LOG2(BLYNK_F("InitCfgFile,sz="), sizeof(Blynk8266_WM_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Blynk8266_WM_config, &defaultConfig, sizeof(Blynk8266_WM_config));
        }
        else
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
                      
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;      
          strcpy(Blynk8266_WM_config.board_name,       NO_CONFIG);

#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
            strncpy(myMenuItems[i].pdata, NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        
        #if (USE_DYNAMIC_PARAMETERS && ( BLYNK_WM_DEBUG > 2) )
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          BLYNK_LOG4(BLYNK_F("g:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
        }
        #endif
        
        // Don't need
        Blynk8266_WM_config.checkSum = 0;

        saveAllConfigData();

        return false;
      }
      else if ( !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) ) )
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(Blynk8266_WM_config);
      }

      return true;
    }
#else

  #ifndef EEPROM_SIZE
    #define EEPROM_SIZE     2048
  #else
    #if (EEPROM_SIZE > 4096)
      #warning EEPROM_SIZE must be <= 4096. Reset to 4096
      #undef EEPROM_SIZE
      #define EEPROM_SIZE     4096
    #endif
    // FLAG_DATA_SIZE is 4, to store DRD/MRD flag
    #if (EEPROM_SIZE < FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      #warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
      #undef EEPROM_SIZE
      #define EEPROM_SIZE     4096
    #endif
  #endif

  #ifndef EEPROM_START
    #define EEPROM_START     0      //define 256 in DRD/MRD
  #else
    #if (EEPROM_START + FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE)
      #error EPROM_START + FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
    #endif
  #endif

// Stating positon to store Blynk8266_WM_config
#define BLYNK_EEPROM_START    (EEPROM_START + FLAG_DATA_SIZE)


    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("setForcedCP"));
#endif
      
      EEPROM.put(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      EEPROM.commit();
    }
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
#if ( BLYNK_WM_DEBUG > 2)    
      BLYNK_LOG1(BLYNK_F("clearForcedCP"));
#endif
      
      EEPROM.put(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, 0);
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("Check if isForcedCP"));
#endif
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      EEPROM.get(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////
    
#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = BLYNK_EEPROM_START + sizeof(Blynk8266_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          BLYNK_LOG1(BLYNK_F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;

#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);
#endif          
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
           
      BLYNK_LOG4(BLYNK_F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = BLYNK_EEPROM_START + sizeof(Blynk8266_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      totalDataSize = sizeof(Blynk8266_WM_config) + sizeof(readCheckSum);
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          *_pointer = EEPROM.read(offset);
          
          checkSum += *_pointer;  
         }    
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("CR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif             
      }
      
      EEPROM.get(offset, readCheckSum);
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

    void EEPROM_putDynamicData()
    {
      int checkSum = 0;
      uint16_t offset = BLYNK_EEPROM_START + sizeof(Blynk8266_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG4(BLYNK_F("CW:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
#endif
                            
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      EEPROM.put(offset, checkSum);
      //EEPROM.commit();
      
      BLYNK_LOG2(BLYNK_F("CrWCSum=0x"), String(checkSum, HEX));
    }
#endif

    //////////////////////////////////////////////
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum;
      
      hadConfigData = false; 
      
      EEPROM.begin(EEPROM_SIZE);
      BLYNK_LOG2(BLYNK_F("EEPROMsz:"), EEPROM_SIZE);
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load Config Data from Sketch
        memcpy(&Blynk8266_WM_config, &defaultConfig, sizeof(Blynk8266_WM_config));
        strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        
        // Including config and dynamic data, and assume valid
        saveAllConfigData();
                 
#if ( BLYNK_WM_DEBUG > 2)      
        BLYNK_LOG1(BLYNK_F("======= Start Loaded Config Data ======="));
        displayConfigData(Blynk8266_WM_config);
#endif

        // Don't need Config Portal anymore
        return true;             
      }
      else
      {
        // Load data from EEPROM
        EEPROM.get(BLYNK_EEPROM_START, Blynk8266_WM_config);
        
        // If "blank" or NULL, set false flag and exit
        if (!isWiFiConfigValid())
        {
          return false;
        }
        
        
#if ( BLYNK_WM_DEBUG > 2)      
        BLYNK_LOG1(BLYNK_F("======= Start Stored Config Data ======="));
        displayConfigData(Blynk8266_WM_config);
#endif

        calChecksum = calcChecksum();

        BLYNK_LOG4(BLYNK_F("CCSum=0x"), String(calChecksum, HEX),
                   BLYNK_F(",RCSum=0x"), String(Blynk8266_WM_config.checkSum, HEX));

#if USE_DYNAMIC_PARAMETERS
                 
        // Load dynamic data from EEPROM
        dynamicDataValid = EEPROM_getDynamicData();
        
        if (dynamicDataValid)
        {
  #if ( BLYNK_WM_DEBUG > 2)      
          BLYNK_LOG1(BLYNK_F("Valid Stored Dynamic Data"));
  #endif          
        }
  #if ( BLYNK_WM_DEBUG > 2)  
        else
        {
          BLYNK_LOG1(BLYNK_F("Invalid Stored Dynamic Data. Ignored"));
        }
  #endif
#endif
      }
        
      if ( (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WM_config.checkSum) || !dynamicDataValid )
      {       
        // Including Credentials CSum
        BLYNK_LOG4(BLYNK_F("InitEEPROM,sz="), EEPROM_SIZE, F(",DataSz="), totalDataSize);

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Blynk8266_WM_config, &defaultConfig, sizeof(Blynk8266_WM_config));
        }
        else
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
             
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;      
          strcpy(Blynk8266_WM_config.board_name,       NO_CONFIG);

#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
            strncpy(myMenuItems[i].pdata, NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif
        }
    
        strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        
        #if ( USE_DYNAMIC_PARAMETERS && ( BLYNK_WM_DEBUG > 2) )
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          BLYNK_LOG4(BLYNK_F("g:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
        }
        #endif
        
        // Don't need
        Blynk8266_WM_config.checkSum = 0;

        saveAllConfigData();

        return false;
      }
      else if ( !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) ) )
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(Blynk8266_WM_config);
      }

      return true;
    }

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;
      BLYNK_LOG4(BLYNK_F("SaveEEPROM,sz="), EEPROM_SIZE, BLYNK_F(",CSum=0x"), String(calChecksum, HEX))

      EEPROM.put(BLYNK_EEPROM_START, Blynk8266_WM_config);
      
      EEPROM.commit();
    }
    
    void saveAllConfigData()
    {
      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;
      BLYNK_LOG4(BLYNK_F("SaveEEPROM,sz="), EEPROM_SIZE, BLYNK_F(",CSum=0x"), String(calChecksum, HEX))

      EEPROM.put(BLYNK_EEPROM_START, Blynk8266_WM_config);
      
#if USE_DYNAMIC_PARAMETERS      
      EEPROM_putDynamicData();
#endif
      
      EEPROM.commit();
    }

#endif

    //////////////////////////////////////////////

    bool connectMultiBlynk()
    {
#define BLYNK_CONNECT_TIMEOUT_MS      10000L

      for (uint16_t i = 0; i < NUM_BLYNK_CREDENTIALS; i++)
      {
        config(Blynk8266_WM_config.Blynk_Creds[i].blynk_token,
               Blynk8266_WM_config.Blynk_Creds[i].blynk_server, Blynk8266_WM_config.blynk_port);

        if (connect(BLYNK_CONNECT_TIMEOUT_MS) )
        {
          BLYNK_LOG4(BLYNK_F("Connected to BlynkServer="), Blynk8266_WM_config.Blynk_Creds[i].blynk_server,
                     BLYNK_F(",Token="), Blynk8266_WM_config.Blynk_Creds[i].blynk_token);
          return true;
        }
      }

      BLYNK_LOG1(BLYNK_F("Blynk not connected"));

      return false;

    }
    
    //////////////////////////////////////////////

    uint8_t connectMultiWiFi()
    {
      // For ESP8266, this better be 3000 to enable connect the 1st time
#define WIFI_MULTI_CONNECT_WAITING_MS      3000L

      uint8_t status;
      BLYNK_LOG1(BLYNK_F("Connecting MultiWifi..."));

      WiFi.mode(WIFI_STA);
      
      //New v1.0.11
      setHostname();
           
      int i = 0;
      status = wifiMulti.run();
      delay(WIFI_MULTI_CONNECT_WAITING_MS);

      while ( ( i++ < 10 ) && ( status != WL_CONNECTED ) )
      {
        status = wifiMulti.run();

        if ( status == WL_CONNECTED )
          break;
        else
          delay(WIFI_MULTI_CONNECT_WAITING_MS);
      }

      if ( status == WL_CONNECTED )
      {
        BLYNK_LOG2(BLYNK_F("WiFi connected after time: "), i);
        BLYNK_LOG4(BLYNK_F("SSID="), WiFi.SSID(), BLYNK_F(",RSSI="), WiFi.RSSI());
        BLYNK_LOG4(BLYNK_F("Channel="), WiFi.channel(), BLYNK_F(",IP="), WiFi.localIP() );
      }
      else
        BLYNK_LOG1(BLYNK_F("WiFi not connected"));

      return status;
    }

    //////////////////////////////////////////////

    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template  = BLYNK_WM_HTML_HEAD_START;
      
  #if USING_CUSTOMS_STYLE
      // Using Customs style when not NULL
      if (BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE)
        root_html_template  += BLYNK_WM_HTML_HEAD_CUSTOMS_STYLE;
      else
        root_html_template  += BLYNK_WM_HTML_HEAD_STYLE;
  #else     
      root_html_template  += BLYNK_WM_HTML_HEAD_STYLE;
  #endif
      
  #if USING_CUSTOMS_HEAD_ELEMENT
      if (_CustomsHeadElement)
        root_html_template += _CustomsHeadElement;
  #endif          
      
#if SCAN_WIFI_NETWORKS
      
      // Replace HTML <input...> with <select...>, based on WiFi network scan in startConfigurationMode()

      ListOfSSIDs = "";

      for (int i = 0, list_items = 0; (i < WiFiNetworksFound) && (list_items < MAX_SSID_IN_LIST); i++)
      {
        if (indices[i] == -1) 
          continue; 		// skip duplicates and those that are below the required quality
          
        ListOfSSIDs += BLYNK_WM_OPTION_START + String(WiFi.SSID(indices[i])) + BLYNK_WM_OPTION_END;	
        list_items++;		// Count number of suitable, distinct SSIDs to be included in list
      }

  #if ( BLYNK_WM_DEBUG > 3)
      BLYNK_LOG2(WiFiNetworksFound, BLYNK_F(" SSIDs found, generating HTML now"));
      BLYNK_LOG1(ListOfSSIDs);
  #endif

      if (ListOfSSIDs == "")		// No SSID found or none was good enough
        ListOfSSIDs = BLYNK_WM_OPTION_START + String(BLYNK_WM_NO_NETWORKS_FOUND) + BLYNK_WM_OPTION_END;

      pitem = String(BLYNK_WM_HTML_HEAD_END);

#if MANUAL_SSID_INPUT_ALLOWED
      pitem.replace("[[input_id]]",  "<input id='id' list='SSIDs'>"  + String(BLYNK_WM_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + BLYNK_WM_DATALIST_END);
      
      pitem.replace("[[input_id1]]", "<input id='id1' list='SSIDs'>" + String(BLYNK_WM_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + BLYNK_WM_DATALIST_END);
      
  #if ( BLYNK_WM_DEBUG > 3) 
      BLYNK_LOG2(BLYNK_F("pitem:"), pitem);
      BLYNK_LOG2(BLYNK_F("pitem:"), pitem);
  #endif
  
#else
      pitem.replace("[[input_id]]",  "<select id='id'>"  + ListOfSSIDs + BLYNK_WM_SELECT_END);
      pitem.replace("[[input_id1]]", "<select id='id1'>" + ListOfSSIDs + BLYNK_WM_SELECT_END);
#endif

      root_html_template += pitem + BLYNK_WM_FLDSET_START;

#else

      pitem = String(BLYNK_WM_HTML_HEAD_END);
      pitem.replace("[[input_id]]",  BLYNK_WM_HTML_INPUT_ID);
      pitem.replace("[[input_id1]]", BLYNK_WM_HTML_INPUT_ID1);
      root_html_template += pitem + BLYNK_WM_FLDSET_START;

#endif    // SCAN_WIFI_NETWORKS

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(BLYNK_WM_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(BLYNK_WM_FLDSET_END) + BLYNK_WM_HTML_BUTTON + BLYNK_WM_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(BLYNK_WM_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(BLYNK_WM_HTML_SCRIPT_END) + BLYNK_WM_HTML_END;
      
      return;     
    }
       
    //////////////////////////////////////////////

    void serverSendHeaders()
    {
      BLYNK_LOG4(BLYNK_F("serverSendHeaders:WM_HTTP_CACHE_CONTROL:"), WM_HTTP_CACHE_CONTROL, "=", WM_HTTP_NO_STORE);
      server->sendHeader(WM_HTTP_CACHE_CONTROL, WM_HTTP_NO_STORE);
      
#if USING_CORS_FEATURE
      // New from v1.2.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
      BLYNK_LOG4(BLYNK_F("serverSendHeaders:WM_HTTP_CORS:"), WM_HTTP_CORS, " : ", _CORS_Header);
      server->sendHeader(WM_HTTP_CORS, _CORS_Header);
#endif
     
      BLYNK_LOG4(BLYNK_F("serverSendHeaders:WM_HTTP_PRAGMA:"), WM_HTTP_PRAGMA, " : ", WM_HTTP_NO_CACHE);
      server->sendHeader(WM_HTTP_PRAGMA, WM_HTTP_NO_CACHE);
      
      BLYNK_LOG4(BLYNK_F("serverSendHeaders:WM_HTTP_EXPIRES:"), WM_HTTP_EXPIRES, " : ", "-1");
      server->sendHeader(WM_HTTP_EXPIRES, "-1");
    }
       
    //////////////////////////////////////////////
    
    void handleRequest()
    {
      if (server)
      {
        String key = server->arg("key");
        String value = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          // New from v1.2.0         
          serverSendHeaders();        
          //////
          
          String result;
          createHTML(result);

          //BLYNK_LOG1(BLYNK_F("h:repl"));

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;
          
          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("BlynkSimpleEsp8266_WM", RFC952_hostname);
          }
          else if ( Blynk8266_WM_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("BlynkSimpleEsp8266_WM", Blynk8266_WM_config.board_name);
          }
          
          if (!hadConfigData)
          {
            // Nullify the invalid data to avoid displaying garbage
            memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
            Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          }
                 
          result.replace("[[id]]",  Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",  Blynk8266_WM_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]", Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]", Blynk8266_WM_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[sv]]",  Blynk8266_WM_config.Blynk_Creds[0].blynk_server);
          result.replace("[[tk]]",  Blynk8266_WM_config.Blynk_Creds[0].blynk_token);
          result.replace("[[sv1]]", Blynk8266_WM_config.Blynk_Creds[1].blynk_server);
          result.replace("[[tk1]]", Blynk8266_WM_config.Blynk_Creds[1].blynk_token);
          result.replace("[[pt]]",  String(Blynk8266_WM_config.blynk_port));
          result.replace("[[nm]]",  Blynk8266_WM_config.board_name);

#if USE_DYNAMIC_PARAMETERS          
          // Load default configuration        
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
  #if ( BLYNK_WM_DEBUG > 2)                 
            BLYNK_LOG4(BLYNK_F("h1:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata )
  #endif            
          }
#endif

          server->send(200, WM_HTTP_HEAD_TEXT_HTML, result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
          strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        }
        
#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;           
            }
  #if ( BLYNK_WM_DEBUG > 2)                 
            BLYNK_LOG1(BLYNK_F("h: Init menuItemUpdated" ));
  #endif                        
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool id1_Updated = false;
        static bool pw1_Updated = false;
        static bool sv_Updated  = false;
        static bool tk_Updated  = false;
        static bool sv1_Updated = false;
        static bool tk1_Updated = false;
        static bool pt_Updated  = false;
        static bool nm_Updated  = false;

        if (key == String("id"))
        {
          if (!id_Updated)
          {
            id_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (key == String("pw"))
        {
          if (!pw_Updated)
          {
            pw_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (key == String("id1"))
        {
          if (!id1_Updated)
          {
            id1_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (key == String("pw1"))
        {
          if (!pw1_Updated)
          {
            pw1_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (key == String("sv"))
        {
          if (!sv_Updated)
          {
            sv_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_server) - 1)
            strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server, value.c_str());
          else
            strncpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_server) - 1);
        }
        else if (key == String("tk"))
        {
          if (!tk_Updated)
          {
            tk_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_token) - 1)
            strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token, value.c_str());
          else
            strncpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_token) - 1);
        }
        else if (key == String("sv1"))
        {
          if (!sv1_Updated)
          {
            sv1_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_server) - 1)
            strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server, value.c_str());
          else
            strncpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_server) - 1);
        }
        else if (key == String("tk1"))
        {
          if (!tk1_Updated)
          {
            tk1_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_token) - 1)
            strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token, value.c_str());
          else
            strncpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_token) - 1);
        }
        else if (key == String("pt"))
        {
          if (!pt_Updated)
          {
            pt_Updated = true;          
            number_items_Updated++;
          }
          
          Blynk8266_WM_config.blynk_port = value.toInt();
        }
        else if (key == String("nm"))
        {
          if (!nm_Updated)
          {
            nm_Updated = true;          
            number_items_Updated++;
          }
          
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.board_name) - 1)
            strcpy(Blynk8266_WM_config.board_name, value.c_str());
          else
            strncpy(Blynk8266_WM_config.board_name, value.c_str(), sizeof(Blynk8266_WM_config.board_name) - 1);
        }

#if USE_DYNAMIC_PARAMETERS
        else
        {
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
            {
              BLYNK_LOG4(BLYNK_F("h:"), myMenuItems[i].id, BLYNK_F("="), value.c_str() );
              
              if (!menuItemUpdated[i])
              {
                menuItemUpdated[i] = true;          
                number_items_Updated++;
              }

              // Actual size of pdata is [maxlen + 1]
              memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

              if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
                strcpy(myMenuItems[i].pdata, value.c_str());
              else
                strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
  #if ( BLYNK_WM_DEBUG > 2)                   
              BLYNK_LOG4(BLYNK_F("h2:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
  #endif
              break;
            }
          }
        }
#endif
        
        server->send(200, WM_HTTP_HEAD_TEXT_HTML, "OK");

#if USE_DYNAMIC_PARAMETERS
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif
        {
#if USE_LITTLEFS
          BLYNK_LOG2(BLYNK_F("h:Updating LittleFS:"), CONFIG_FILENAME);     
#elif USE_SPIFFS
          BLYNK_LOG2(BLYNK_F("h:Updating SPIFFS:"), CONFIG_FILENAME);
#else
          BLYNK_LOG1(BLYNK_F("h:Updating EEPROM. Please wait for reset"));
#endif

          saveAllConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
          {
            clearForcedCP();
          }

          BLYNK_LOG1(BLYNK_F("h:Rst"));

          // Delay then reset the ESP8266 after save data
          delay(1000);
          ESP.reset();
        }
      }    // if (server)
    }
    
    //////////////////////////////////////////////

#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    void startConfigurationMode()
    {  
      // turn the LED_BUILTIN ON to tell us we are in configuration mode.
      digitalWrite(LED_BUILTIN, LED_ON);

#if SCAN_WIFI_NETWORKS
	    configTimeout = 0;  // To allow user input in CP
	    
	    WiFiNetworksFound = scanWifiNetworks(&indices);	
#endif
    
    
      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String chipID = String(ESP.getChipId(), HEX);
        chipID.toUpperCase();

        portal_ssid = "ESP_" + chipID;

        portal_pass = "MyESP_" + chipID;
      }

      WiFi.mode(WIFI_AP);
      
      // New
      delay(100);

      static int channel;
      // Use random channel if  WiFiAPChannel == 0
      if (WiFiAPChannel == 0)
        channel = random(MAX_WIFI_CHANNEL) + 1;
      else
        channel = WiFiAPChannel;
        
      // KH, Must be here for ESP8266 core v3.0.0. Good for v2.7.4- as well
      WiFi.softAPConfig(portal_apIP, portal_apIP, IPAddress(255, 255, 255, 0));  

      WiFi.softAP(portal_ssid.c_str(), portal_pass.c_str(), channel);
      
      BLYNK_LOG4(BLYNK_F("\nstConf:SSID="), portal_ssid, BLYNK_F(",PW="), portal_pass);
      BLYNK_LOG4(BLYNK_F("IP="), portal_apIP.toString(), ",ch=", channel);

      IPAddress myIP = WiFi.softAPIP();
      BLYNK_LOG2(BLYNK_F("AP IP address: "), myIP);
      
      if (!server)
        server = new ESP8266WebServer;

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
      if (server)
      {
        server->on("/", [this]() { handleRequest(); });
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
        
#if ( BLYNK_WM_DEBUG > 2)                   
        BLYNK_LOG4(BLYNK_F("s:millis() = "), millis(), BLYNK_F(", configTimeout = "), configTimeout);
#endif
      }
      else
      {
        configTimeout = 0;
#if ( BLYNK_WM_DEBUG > 2)                   
        BLYNK_LOG1(BLYNK_F("s:configTimeout = 0"));
#endif        
      }  

      configuration_mode = true;
    }
    
#if SCAN_WIFI_NETWORKS

	  // Source code adapted from https://github.com/khoih-prog/ESP_WiFiManager/blob/master/src/ESP_WiFiManager-Impl.h

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    bool          _removeDuplicateAPs     = true;
	
	  //////////////////////////////////////////
    
    void swap(int *thisOne, int *thatOne)
    {
       int tempo;

       tempo    = *thatOne;
       *thatOne = *thisOne;
       *thisOne = tempo;
    }

    //////////////////////////////////////////
	
	  void setMinimumSignalQuality(int quality)
	  {
	    _minimumQuality = quality;
	  }

	  //////////////////////////////////////////

	  //if this is true, remove duplicate Access Points - default true
	  void setRemoveDuplicateAPs(bool removeDuplicates)
	  {
	    _removeDuplicateAPs = removeDuplicates;
	  }

	  //////////////////////////////////////////

	  //Scan for WiFiNetworks in range and sort by signal strength
	  //space for indices array allocated on the heap and should be freed when no longer required  
	  int scanWifiNetworks(int **indicesptr)
	  {
	    BLYNK_LOG1(BLYNK_F("Scanning Network"));

	    int n = WiFi.scanNetworks();

	    BLYNK_LOG2(BLYNK_F("scanWifiNetworks: Done, Scanned Networks n = "), n); 

	    //KH, Terrible bug here. WiFi.scanNetworks() returns n < 0 => malloc( negative == very big ) => crash!!!
	    //In .../esp32/libraries/WiFi/src/WiFiType.h
	    //#define WIFI_SCAN_RUNNING   (-1)
	    //#define WIFI_SCAN_FAILED    (-2)
	    //if (n == 0)
	    if (n <= 0)
	    {
		    BLYNK_LOG1(BLYNK_F("No network found"));
		    return (0);
	    }
	    else
	    {
		    // Allocate space off the heap for indices array.
		    // This space should be freed when no longer required.
		    // Don't need to free as whenever CP is done, the system is reset
		    int* indices = (int *)malloc(n * sizeof(int));

		    if (indices == NULL)
		    {
		      BLYNK_LOG1(BLYNK_F("ERROR: Out of memory"));
		      *indicesptr = NULL;
		      return (0);
		    }

		    *indicesptr = indices;
	       
		    //sort networks
		    for (int i = 0; i < n; i++)
		    {
		      indices[i] = i;
		    }

		    BLYNK_LOG(BLYNK_F("Sorting"));

		    // RSSI SORT
		    // old sort
		    for (int i = 0; i < n; i++)
		    {
		      for (int j = i + 1; j < n; j++)
		      {
			      if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
			      {
                    //std::swap(indices[i], indices[j]);
                    // Using locally defined swap()
                    swap(&indices[i], &indices[j]);
       			}
		      }
		    }

		    BLYNK_LOG1(BLYNK_F("Removing Dup"));

		    // remove duplicates ( must be RSSI sorted )
		    if (_removeDuplicateAPs)
		    {
		      String cssid;
		      
		      for (int i = 0; i < n; i++)
		      {
			      if (indices[i] == -1)
			        continue;

			      cssid = WiFi.SSID(indices[i]);
			      
			      for (int j = i + 1; j < n; j++)
			      {
			        if (cssid == WiFi.SSID(indices[j]))
			        {
				        BLYNK_LOG2("DUP AP:", WiFi.SSID(indices[j]));
				        indices[j] = -1; // set dup aps to index -1
			        }
			      }
		      }
		    }

		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups

		      int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));

		      if (!(_minimumQuality == -1 || _minimumQuality < quality))
		      {
			      indices[i] = -1;
			      BLYNK_LOG1(BLYNK_F("Skipping low quality"));
		      }
		    }

		    BLYNK_LOG1(BLYNK_F("WiFi networks found:"));
		    
		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups
		      else
			      BLYNK_LOG6(i+1,": ",WiFi.SSID(indices[i]), ", ", WiFi.RSSI(i), "dB");
		    }

		    return (n);
	    }
	  }

	  //////////////////////////////////////////

	  int getRSSIasQuality(int RSSI)
	  {
	    int quality = 0;

	    if (RSSI <= -100)
	    {
		    quality = 0;
	    }
	    else if (RSSI >= -50)
	    {
		    quality = 100;
	    }
	    else
	    {
		    quality = 2 * (RSSI + 100);
	    }

	    return quality;
	  }

  //////////////////////////////////////////

#endif    
};

//////////////////////////////////////////////

static WiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif

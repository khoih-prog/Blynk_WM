/****************************************************************************************************************************
   Blynk_WM_Template.ino
   For ESP32/ESP8266 boards
   Written by Thor Johnson (https://github.com/thorathome) May 2020 as a template for
   Blynk Wifi ESP communications. See https://github.com/thorathome/Blynk_Examples
   Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.15

   Original Blynk Library author:
   @file       BlynkSimpleEsp8266.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Jan 2015
   @brief

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
 *****************************************************************************************************************************/

// Sketch uses Arduino IDE-selected ESP32 and ESP8266 to select compile choices

/*  
 * The Arduino/Blynk sketch Blynk_WiFiMgr_ESP32_8266_Template_HexColor.ino is a fully-developed 
 * get-started demo program for the powerful BlynkSimpleEsp... and the newer WiFiManager (WM) libraries. 
 * This demo sketch written by Thor Johnson (https://github.com/thorathome) May 2020 as a template for
 * Blynk Wifi ESP communications. See https://github.com/thorathome/Blynk_Examples
 * 
 * It demonstrates
 * * WiFiManager Config Portal configuration and use
 * * WiFiManager Dynamic (extended) Parameters configuration and use
 * * Use of compiler constants for compile-time selection
 * * Use of Blynk's BLYNK_WRITE_DEFAULT() flexible capability
 *
 * This sketch lets end-users choose a color using ZeRGBa, colors a blinking (heartbeat) LED, 
 * and shows the HEX code for that color.
 *
 * It requires:
 * * Blynk ZeRGBa configured in MERGE mode with values between 0 and 255
 * * Blynk LED
 * * Blynk Value Display
 * * Blynk master library installed
 * * Blynk_WiFiManager installed
 * * ESP32 or ESP8266 devices
 *
 * As in all Blynk sketches using WiFi, you will need
 * * Your WiFi SSID or SSIDs and passwords
 * * Your Blynk authcode or authcodes
 * * Your Blynk server URL (Main US Blyk server is blynk-cloud.com.)
 *
 * These values do not need to be coded into the sketch as they may be entered at runtime (once) 
 * into the Config Portal.
 *
 * You also do not have to hardcode the Virtual Pins for the ZeRGBa, LED or Value Display, 
 * can input them at runtime using the Config Portal. 
 * This sketch uses Blynk's BLYNK_WRITE_DEFAULT() capability to deliver this flexibility. 
 * I use this approach to manage a number of similar wireless controls like SONOFFs.
 *
 * The Config Portal will appear as SSID MyConfigPortal, with WiFi password of 12345678 
 * and IP address of 192,168,220,1. 
 * These three values (Config Portal SSID, password, IP address) are hardcoded into the sketch 
 * (but could be made selectable in the Config Portal, itself.)
 *
 * I hope this is as useful to you as it has been to me to understand Blynk, 
 * the BlynkSimpleEsp... and ...WiFiManager libraries, the ESP32 and ESP8266.
 */

#define SERIAL_SPEED 115200
#define SKETCH_NAME "Blynk_WM_Template"

#define BLYNK_PRINT Serial  // Generates Blynk debug prints. Comment out if not needed, saving space

#define BLYNK_WM_DEBUG      0

///////////////////////////////////////////////////////////////////////////////////////////
//// COMPILER SWITCH SELECTION - USE WIFI MANAGER OR NOT //////////////////////////////////
#define USE_WM true   // to easily select WiFi Manager or not
//#define USE_WM false   // to easily select WiFi Manager or not
// REMEMBER: not using _WM means we make our own initial WiFi connection


///////////////////////////////////////////////////////////////////////////////////////////
//// COMPILER SWITCH SELECTION - USE SSL OR NOT ///////////////////////////////////////////
#define USE_SSL true // to easily select SSL or not
//#define USE_SSL false // to easily select SSL or not


///////////////////////////////////////////////////////////////////////////////////////////
//// COMPILER VALUE SELECTION - VIRTUAL PINS FOR THE 3 WIDGETS ////////////////////////////
#define CONTROL_DEFAULT_VPIN "2"        // Can also be changed via Config Portal (USE_DYNAMIC_PARAMETERS)
#define HEARTBEAT_LED_DEFAULT_VPIN "3"  // Can also be changed via Config Portal (USE_DYNAMIC_PARAMETERS)
#define DISPLAY_DEFAULT_VPIN "4"        // Can also be changed via Config Portal (USE_DYNAMIC_PARAMETERS)
// These can all be reset using Config Portal. I have included them as default values only. */ 

#if USE_WM
  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER SWITCH SELECTION - USE DEFAULT CONFIG PORTAL FIELD DATA OR NOT //////////////
  //// SELECT IF YOU WANT CONFIG PORTAL FIELDS INITIALIZED TO SOMETHING OTHER THAN BLANK ////
  //// This data only gets loaded on an initial compile and upload and after Config Portal data gets deleted
  //// such as by using DRD (Double Reset) or the Blynk command Blynk.clearConfigData()
  #define USE_DEFAULT_CONFIG_DATA true
  //#define USE_DEFAULT_CONFIG_DATA false


  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER SWITCH SELECTION - USE DYNAMIC (CUSTOM) CONFIG PORTAL FIELDS OR NOT /////////
  #define USE_DYNAMIC_PARAMETERS true
  //#define USE_DYNAMIC_PARAMETERS false

  
  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER SWITCH SELECTION - USE SPIFFS OR EEPROM /////////////////////////////////////
  //// only relevant if using WiFiManager _WM
  
  #if defined(ESP8266)
    // #define USE_SPIFFS and USE_LITTLEFS   false        => using EEPROM for configuration data in WiFiManager
    // #define USE_LITTLEFS    true                       => using LITTLEFS for configuration data in WiFiManager
    // #define USE_LITTLEFS    false and USE_SPIFFS true  => using SPIFFS for configuration data in WiFiManager
    // Be sure to define USE_LITTLEFS and USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>
    // From ESP8266 core 2.7.1, SPIFFS will be deprecated and to be replaced by LittleFS
    // Select USE_LITTLEFS (higher priority) or USE_SPIFFS
  
    #define USE_LITTLEFS                true
    //#define USE_LITTLEFS                false

    #define USE_SPIFFS false  // Choosing EEPROM over LittleFS / SPIFFS here
    //#define USE_SPIFFS true   
    
    #if USE_LITTLEFS
      //LittleFS has higher priority
      #ifdef USE_SPIFFS
        #undef USE_SPIFFS
      #endif
      #define USE_SPIFFS                  false
      #warning Use LittleFS for ESP8266
    #elif USE_SPIFFS
      //#define USE_SPIFFS false  // ESP8266, Choosing EEPROM over LittleFS / SPIFFS here
      #define USE_SPIFFS true
      #warning Use SPIFFS for ESP8266
    #else
      #warning Use EEPROM for ESP8266
    #endif  
  #else
    #define USE_SPIFFS false  // ESP32, Choosing EEPROM over LittleFS / SPIFFS here
    //#define USE_SPIFFS true
    #if USE_SPIFFS
      #warning Use SPIFFS for ESP32
    #else
      #warning Use EEPROM for ESP32
    #endif
  #endif

  #if USE_LITTLEFS
    #define CurrentFileFS     "LittleFS"
  #elif USE_SPIFFS
    #define CurrentFileFS     "SPIFFS"
  #endif  

  // COMPILE-TIME LOGIC: NON-VOLATILE MEMORY SELECTION (WiFiManager only) 
  // NOT NECESSARY TO MODIFY
  #if !( USE_LITTLEFS || USE_SPIFFS)
    // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
    #define EEPROM_SIZE    (2 * 1024)
    // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
    #define EEPROM_START   512
  #endif


  // NOT NECESSARY TO MODIFY - MUST BE INCLUDED
  // Force some params in Blynk, only valid for library version 1.0.1 and later
  // (from the Github doc)
  #define TIMEOUT_RECONNECT_WIFI                    10000L
  #define RESET_IF_CONFIG_TIMEOUT                   true
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    3  // Library default is 10 (times 2) - DEBUG SET AT 2

  // NOT NECESSARY TO MODIFY
  // COMPILE-TIME LOGIC: AUTOMATIC LIBRARY SELECTION 
  #if USE_SSL
    #if ESP8266
      #include <BlynkSimpleEsp8266_SSL_WM.h>
    #endif
    #if ESP32
      #include <BlynkSimpleEsp32_SSL_WM.h> 
    #endif
  #else // no SSL
    #if ESP8266
      #include <BlynkSimpleEsp8266_WM.h>
    #endif
    #if ESP32
      #include <BlynkSimpleEsp32_WM.h>
    #endif
  #endif

// NOT NECESSARY TO MODIFY
#else // not using WiFiManager
  #if USE_SSL
    #if ESP8266
      #include <BlynkSimpleEsp8266_SSL.h>
    #endif
    #if ESP32
      #include <BlynkSimpleEsp32_SSL.h>
    #endif
  #else // no SSL
    #if ESP8266
      #include <BlynkSimpleEsp8266.h>
    #endif
    #if ESP32
      #include <BlynkSimpleEsp32.h>
    #endif
  #endif
#endif


#if USE_WM
  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER VALUE SELECTION - CONFIG PORTAL'S OWN SSID AND password /////////////////////
  //// Config Portal turns on when WiFiManager cannot connect to WiFi or Blynk
  //// only relevant if using WiFiManager _WM
  #define CONFIG_PORTAL_SSID "MyConfigPortal"   // SSID for device-generated WiFi beacon
  #define CONFIG_PORTAL_PASSWORD "12345678"     // password for device-generated WiFi beacon - 8+ characters
  #define CONFIG_PORTAL_IPADDRESS 192,168,220,1 // IP address of Config Portal once connected to WiFi beacon
  #define DEVICE_HOST_NAME "Configurator-Demo"  // DHCP Host name for device


  #if USE_DEFAULT_CONFIG_DATA // Set default values for "standard" fields presented in Config Portal
    bool LOAD_DEFAULT_CONFIG_DATA = true;  //do not modify - used by library
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER SWITCH SELECTIONS - SET DEFAULT VALUES PRESENTED IN CONFIG PORTAL ///////////////
    //// Data structure AND default values for "standard" fields presented in Config Portal
    Blynk_WM_Configuration defaultConfig =
    {
      // NOT NECESSARY TO MODIFY
      //char header[16], dummy, not used
      #if USE_SSL  
        "SSL",
      #else
        "NonSSL",
      #endif

      ///////////////////////////////////////////////////////////////////////////////////////////
      //// COMPILER SWITCH SELECTIONS - SET UP TO TWO SSIDs & TWO passwords /////////////////////
      //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
      //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
      "SSID",  "password",              // Config Portal WiFi SSID & PWD field values
      "SSID1", "password1",             // Config Portal WiFi SSID1 & PWD1 field values
    
      ///////////////////////////////////////////////////////////////////////////////////////////
      //// COMPILER SWITCH SELECTIONS - SET UP TO TWO BLYNK SERVERS & TWO AUTH CODES ////////////
      // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
      // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
      "account.bogus.org", "token1",    // Config Portal Blynk Server & Token field values
      "blynk-cloud.com", "<authcode>",  // Config Portal Blynk Server1 & Token1 field values
      
      ///////////////////////////////////////////////////////////////////////////////////////////
      //// COMPILER SWITCH SELECTIONS - SET DEFAULT PORTS (FOR SSL OR NON-SSL) //////////////////
      //int  blynk_port;
      #if USE_SSL
        9443,                           // Config Portal Port field (default SSL port) value
      #else
        8080,                           // Config Portal Port field (default non-SSL) value
      #endif
    
      ///////////////////////////////////////////////////////////////////////////////////////////
      //// COMPILER SWITCH SELECTIONS - SET DEFAULT BOARD NAME //////////////////////////////////
      //char board_name     [24];
      "Air-Control",                    // Config Portal Board Name field value
    
      // terminate the list
      //int  checkSum, dummy, not used
      0
      /////////// End Default Config Data /////////////
    };
   
  #else // not using USE_DEFAULT_CONFIG_DATA 
    // Set up the "standard" Config Portal fields
    bool LOAD_DEFAULT_CONFIG_DATA = false;
    
    // AUTOMATICALLY GENERATE THE "STANDARD"CONFIG PORTAL DATA STRUCTURE
    // NOT NECESSARY TO MODIFY
    Blynk_WM_Configuration defaultConfig;  // loads t4he default confir portal data type with blacnk defaults  
  #endif

  
  #if USE_DYNAMIC_PARAMETERS
    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP DYNAMIC PARAMETER DATA TYPES & INITIAL VALUES //////
    //Defined in <BlynkSimpleEsp8266_WM.h> and <BlynkSimpleEsp8266_SSL_WM.h>   
    /**************************************
    #define MAX_ID_LEN                5
    #define MAX_DISPLAY_NAME_LEN      16
    typedef struct
    {
    char id             [MAX_ID_LEN + 1];
    char displayName    [MAX_DISPLAY_NAME_LEN + 1];
    char *pdata;
    uint8_t maxlen;
    } MenuItem;
    ************************************* */    
    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define CONTROL_VPIN_LENGTH 5 // First DYNAMIC_PARAMETER (ZeRGBa Virtual Pin)
    char controlVpinC [ CONTROL_VPIN_LENGTH + 1 ] = CONTROL_DEFAULT_VPIN;

    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define CONTROL_LABEL_LENGTH 18 // Second DYNAMIC_PARAMETER (Widget Label for ZeRGBa) 
    char controlLabel [ CONTROL_LABEL_LENGTH + 1 ] = "Select a color";

    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define HEARTBEAT_LED_VPIN_LENGTH 5 // Third DYNAMIC_PARAMETER (Heartbeat LED Virtual Pin)
    char heartbeatVpinC [ HEARTBEAT_LED_VPIN_LENGTH + 1 ] = HEARTBEAT_LED_DEFAULT_VPIN;  

    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define HEARTBEAT_LED_LABEL_LENGTH 26 // Fourth DYNAMIC_PARAMETER (Widget Label for Heartbeat LED)
    char heartbeatLabel [ HEARTBEAT_LED_LABEL_LENGTH + 1 ] = "My Beating Heart";  

    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define DISPLAY_VPIN_LENGTH 5 // Fifth DYNAMIC_PARAMETER (Hex Color Value Display Virtual Pin)
    char displayVpinC [ DISPLAY_VPIN_LENGTH + 1 ] = DISPLAY_DEFAULT_VPIN;  

    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET UP FIELD LENGTHS AND DEFAULT VALUES FOR EACH DYNAMIC PARAMETER
    #define DISPLAY_LABEL_LENGTH 26 // Sixth DYNAMIC_PARAMETER (Widget Label for Hex color display)
    char displayLabel [ DISPLAY_LABEL_LENGTH + 1 ] = "HEX Color Value";  


    ///////////////////////////////////////////////////////////////////////////////////////////
    //// COMPILER VALUE SELECTION - SET THE LABELS SHOWN IN CONFIG PORTAL FOR EACH DYNAMIC VARIABLE
    //// MAKE SURE YOUR DYNAMIC_PARAMETERS MATCH THIS STRUCTURE ////    
    MenuItem myMenuItems [] =
    { // 1234    123456789012345
      { "cvpn", "ZeRGBa VPin (#)", controlVpinC,    CONTROL_VPIN_LENGTH },
      { "clab", "ZeRGBa Label",    controlLabel,    CONTROL_LABEL_LENGTH },
      { "hvpn", "Hbeat VPin (#)",  heartbeatVpinC,  HEARTBEAT_LED_VPIN_LENGTH },
      { "hlab", "Hbeat Label",     heartbeatLabel,  HEARTBEAT_LED_LABEL_LENGTH },
      { "dvpn", "Hex VPin (#)",    displayVpinC,    DISPLAY_VPIN_LENGTH },
      { "dlab", "Hex Label",       displayLabel,    DISPLAY_LABEL_LENGTH },
    };

    // Automatically calculate the # of DYNAMIC PARAMETERS menu items - DO NOT TOUCH
    uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

  #else // not using USE_DYNAMIC_PARAMETERS - SET UP NULL (DYNAMIC) MENU
    // NOT NECESSARY TO MODIFY
    MenuItem myMenuItems [] = {};
    uint16_t NUM_MENU_ITEMS = 0;
  #endif // end USE_DYNAMIC_PARAMETERS    


  // NOT NECESSARY TO MODIFY - MUST BE INCLUDED
  // Force some params in Blynk, only valid for library version 1.0.1 and later
  // (from the Github doc)
  #define TIMEOUT_RECONNECT_WIFI                    10000L
  #define RESET_IF_CONFIG_TIMEOUT                   true
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    3  // Library default is 10 (times 2) - DEBUG SET AT 2

#else // NOT USING WIFI MANAGER - SET STANDARD WIFI & BLYNK CREDENTIALS, VIRTUAL PIN CHAR VARIABLES
  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER VALUE SELECTION - STANDARD WIFI CREDENTIALS /////////////////////////////////
  //// Will be used in standard WiFi/begin() and Blynk.config() commands below //////////////
  char WiFiSSID[] = "<my ssid";  // network SSID (name)
  char WiFiPass[] = "<my passcode>";  // network password

  ///////////////////////////////////////////////////////////////////////////////////////////
  //// COMPILER VALUE SELECTION - BLYNK AUTH /////////////////////////////////
  //// Will be used in standard WiFi/begin() and Blynk.config() commands below //////////////
  char blynkAuth[] = "<my_auth>"; // BLYNK Auth 

  // Will be converted to int values in Setup
  char controlVpinC[] =   CONTROL_DEFAULT_VPIN;
  char heartbeatVpinC[] = HEARTBEAT_LED_DEFAULT_VPIN;
  char displayVpinC[] =   DISPLAY_DEFAULT_VPIN;
#endif


// Integer versions of our three Virtual Pins - values loaded in Setup
int controlVpin;   // = CONTROL_DEFAULT_VPIN or set in Config Portam (WM)
int heartbeatVpin; // = HEARTBEAT_LED_DEFAULT_VPIN or set in Config Portam (WM)
int displayVpin;   // = DISPLAY_DEFAULT_VPIN or set in Config Portam (WM)


// THIS SKETCH SETS UP A HEARTBEAT LED ON A TIMER TO SHOW SYSTEM IS ALIVEAND WELL
BlynkTimer myTimer;
// Blynk timers to blink a heartbeat LED on and off
int heartbeatLEDinterval = 3000; // interval between heartbeats for onboard and Blynk Virtual LED in millisec 
int heartbeatLEDtimerID; 

int heartbeatLEDduration = 750; // duraction of each blink in millisec (set as an interval timer)
int heartbeatLEDdurationTimerID;
bool heartbeatLEDon = false; // this lets me use the same routine for the turn-on timer and the turn-off interval

#ifdef ESP32
  #define BUILTIN_LED 13  // NOT DEFINED IN ESP32 BOARD FILES - HMMM.  
#endif


// SETUP WIFI, BLYNK, HEARTBEAT
 void setup() 
{
  // HELP DEBUG THIS SKETCH WITH GOOD PRINTOUTS
  Serial.begin ( SERIAL_SPEED );
  delay ( 500 );  
  Serial.println ( "\n\n=======================================" );
  Serial.print ( SKETCH_NAME ); 
  #if USE_SSL
    Serial.println ( " ** Using SSL ** \n" );  
  #endif
  Serial.println();

  connectToWLANandBlynk();  // Connect to WiFi, then to Blynk server

  setupBlynkTimers();  // Establish Blynk timers after Blynk is connected

  // Initialize Onboard LED 
  pinMode ( BUILTIN_LED, OUTPUT );  
  digitalWrite ( BUILTIN_LED, LOW ); 
    

  // Set Blynk Virtual Heartbeat LED OFF
  Blynk.virtualWrite ( heartbeatVpin, 000 );  
  heartbeatLEDblink(); // first heartbeat 
  
  Serial.println ( "\nSetup complete \n" );    
  
} //end setup

// KEEPING IT SIMPLE
void loop()
{
  Blynk.run();
  myTimer.run();  
} 

// CONNECT TO WLAN WITH OR WITHOUT WM
// Connect to Blynk once WiFi connection establishked
// Uses compiler switches for WiFiManager, SSL, other choices
void connectToWLANandBlynk()
{
  // Setup WLAN and Blynk
  Serial.print ( "\nSetting up WLAN and Blynk " );  
  #if USE_WM
    Serial.println ( "WITH WiFiManager" ); 
  #else
    Serial.println ( "WITHOUT WiFiManager" );  
  #endif
  
  #if USE_WM
    Serial.println ( "Starting Blynk.begin (with WM)" );  

    Blynk.setConfigPortal ( CONFIG_PORTAL_SSID, CONFIG_PORTAL_PASSWORD );
    Blynk.setConfigPortalIP ( IPAddress ( CONFIG_PORTAL_IPADDRESS ) );  

    Serial.print ( "Blynk.setConfigPortal(" ); 
    Serial.print ( CONFIG_PORTAL_SSID ); Serial.print ( "," );  
    Serial.print ( CONFIG_PORTAL_PASSWORD ); Serial.println ( ")" );   
    Serial.print ( "  Config Portal will be found at IP: " ); Serial.print ( IPAddress ( CONFIG_PORTAL_IPADDRESS ) );  
    Serial.println ( "\n" );  
    
    //Blynk.config ( blynkAuth );  // not needed with WM 
    Blynk.begin ( DEVICE_HOST_NAME ); // DHCP (router) device name
  
  #else//NOT using WM
    Serial.println ( "Starting WiFi.begin (no WM)" );  
    WiFi.begin ( WiFiSSID, WiFiPass );
    Serial.println ( "... waiting a few seconds for WiFi ..." );    
    #if ESP8266
      delay ( 7500 );  // For esp8266, it needs a delay to realize it has connected
    #endif
      
    // REBOOT if we do not have a good WiFi connection
    if ( WiFi.status() != WL_CONNECTED )
    {
      Serial.println ( "Resetting in a few seconds...\n\n\n\n\n" );
      delay ( 3000 );  
      ESP.restart();
    } 
    
    // Configure and launch Blynk
    Blynk.config ( blynkAuth );
    Blynk.connect ( 2500 ); // Don't get stuck hanging for more than 2500 millis.
  #endif // using WM
  
  if ( Blynk.connected() ) 
  {
    #if ( USE_LITTLEFS || USE_SPIFFS)
      Serial.println("\nBlynk using " + String(CurrentFileFS) + " connected. Board Name : " + Blynk.getBoardName());
    #else
      Serial.println("\nBlynk using EEPROM connected. Board Name : " + Blynk.getBoardName());
      Serial.printf("EEPROM size = %d bytes, EEPROM start address = %d / 0x%X\n", EEPROM_SIZE, EEPROM_START, EEPROM_START);
    #endif  
        
    Serial.println ( "Blynk connected just fine" ); 
    Serial.print   ( "  IP address  " ); Serial.println ( WiFi.localIP() ) ;
    Serial.print   ( "  MAC address " ); Serial.println ( WiFi.macAddress() );  
    Serial.println();  
  }
  else Serial.println ( "Blynk NOT CONNECTED \n\n" );  
} // end connectToWLANandBlynk

// SET UP BLYNK TIMER FOR HEARTBEAT (and anything eles you may want later)
void setupBlynkTimers()
{
  Serial.println ( "Setting up Blynk timers" );  
  // Interval timer for heartbeatLED (Blynk LED and onboard LED
  heartbeatLEDtimerID = myTimer.setInterval ( heartbeatLEDinterval, heartbeatLEDblink );  

  Serial.println ( "... Blynk timers set up." );  
  
} //end setupBlynkTimers


// LED HEARTBEAT
void heartbeatLEDblink()
/* Blink the on-board LED AND the Virtual Blynk LED
 * If LED is off, it turne the LEDs on, then sets a timer to turn LED off
 * When the timer triggers, same routine turns the LEDs off
 */
{
  if ( heartbeatLEDon ) // if LED is on, turn it off and vice cersa
  {
    //heartbeatLED.off(); // Blynk Virtual LED
    
    digitalWrite ( BUILTIN_LED, LOW ); // On-board LED
    Blynk.virtualWrite ( heartbeatVpin, 000 );  
    Serial.println ( " ..." );
  } else
  {
    //heartbeatLED.on();      // Blynk Virtual LED
    
    digitalWrite ( BUILTIN_LED, HIGH );  // On-board LED
    Blynk.virtualWrite ( heartbeatVpin, 255 );  
    // Set the timer to turn off the LEDs in a bit  
    heartbeatLEDdurationTimerID = myTimer.setTimeout ( heartbeatLEDduration, heartbeatLEDblink ); 
    
    Serial.print ( "... heartbeat of " ); Serial.print ( SKETCH_NAME ); 
    Serial.print ( " WiFi.status() = " ); Serial.print ( WiFi.status() );  
  }
  
  heartbeatLEDon = ! heartbeatLEDon; // flip status
} //end heartbeatLEDblink


// BLYNK_WRITE_DEFAULT GETS CALLED WHEN THERE IS NO SPECIFIC BLYNK_WRITE FOR THAT VIRTUAL PIN
// This makes it a flexible - and programmable - receiver
// The Config Portal can provide FLEXIBLE Virtual Pin to power this
BLYNK_WRITE_DEFAULT() 
{
  // THE VIRTUAL PIN THAT SENT THE MESSAGE TO BLYNK
  int writeVpin = request.pin; 
  
  Serial.print ( "\nRECEIVED BLYNK SIGNAL FROM V");
  Serial.print ( writeVpin );
  Serial.println ( ": " );
  
  // Print all parameter values
  for ( auto i = param.begin(); i < param.end(); ++i ) 
  {
    Serial.print ( "* param = " ); 
    Serial.println ( i.asString() );  
  }
  Serial.println ( "*****\n" );  

  if ( writeVpin == controlVpin ) // We have color input from ZeRGBa
  {
    // Get the colorfrom ZeRGBa, updatethe Heartbeat LED color and display
    int r = param[0].asInt();
    int g = param[1].asInt();
    int b = param[2].asInt();

    Serial.print ( "\n\nHORSE sent r, g, b (HEX) = " );
    Serial.print ( r, HEX ); Serial.print ( ", " );  
    Serial.print ( g, HEX ); Serial.print ( ", " );  
    Serial.print ( b, HEX ); Serial.println(); 

    String rS = String ( r, HEX ); if ( rS.length() < 2 ) rS = "0" + rS;  
    String gS = String ( g, HEX ); if ( gS.length() < 2 ) gS = "0" + gS;   
    String bS = String ( b, HEX ); if ( bS.length() < 2 ) bS = "0" + bS;  
    Serial.print ( "HEX = " );
    Serial.print ( rS ); Serial.print ( ", " );  
    Serial.print ( gS ); Serial.print ( ", " );  
    Serial.print ( bS ); Serial.println();  

    String rgbHEX = "#" + rS + gS + bS;
    Serial.print ( "Color = " ); Serial.println ( rgbHEX ); Serial.println();  

    // UPDATE THE HEARTBEAT LED COCLOR AND HEX DISPLAY
    Blynk.setProperty ( heartbeatVpin, "color", rgbHEX );  
    
    Blynk.setProperty ( displayVpin, "color", "#FFFFFF" );  
    Blynk.virtualWrite ( displayVpin, rgbHEX );  
  }
} //end BLYNK_WRITE_DEFAULT


#if USE_WM
// UPDATE DYNAMIC PARAMETERS 
//  1 - CONVERTS THE char INFO FROM THE CONFIG PORTAL OR COMPILER CONSTANTS TO THE int VALUES THEY NEED TO BE FOR USE IN A SKETCH
//  2 -   UPDATES BLYNK WITH OTHER DYNAMIC PARAMETERS (WIDGET LABELS) 
void updateDynamicParameters()
{

  Serial.print ( "\nupdateDynamicParameters has: \n   controlVpinC/label = """ ); Serial.print ( controlVpinC ); Serial.print ( """/" ); Serial.print ( controlLabel ); 
  Serial.print ( "\n   heartbeatVpinC/label = """ ); Serial.print ( heartbeatVpinC ); Serial.print ( """/" ); Serial.print ( heartbeatLabel ); 
  Serial.print ( "\n   displayVpinC/label = """ ); Serial.print ( displayVpinC ); Serial.print ( """/" ); Serial.print ( displayLabel ); 
  Serial.println ( "\n" );  
    
  // Convert char Virtual Pin numbers to int in preperation for Blynk connect
  controlVpin = atoi ( controlVpinC );
  if ( controlVpin < 0 || controlVpin > 255 )
  {
    controlVpin = atoi ( CONTROL_DEFAULT_VPIN );
    Serial.print ( "**** Bad controlVpin input value of " );
    Serial.println ( controlVpinC );
  };
  Serial.print ( "   Set controlVpin/controlLabel to " ) ; Serial.print ( controlVpin );
  Serial.print ( "/" ); Serial.println ( controlLabel );   
  Blynk.setProperty ( controlVpin, "label", controlLabel ); 

  heartbeatVpin = atoi ( heartbeatVpinC );
  if ( heartbeatVpin < 0 || heartbeatVpin > 255 )
  {
    heartbeatVpin = atoi ( HEARTBEAT_LED_DEFAULT_VPIN );
    Serial.print ( "**** Bad heartbeatVpin input value of " );
    Serial.println ( heartbeatVpinC );
  }
  Serial.print ( "   Set heartbeatVpin/heartbeatLabel to " ) ; Serial.print ( heartbeatVpin );
  Serial.print ( "/" ); Serial.println ( heartbeatLabel );   
  Blynk.setProperty ( heartbeatVpin, "label", heartbeatLabel );  
    
  displayVpin = atoi ( displayVpinC );
  if ( displayVpin < 0 || displayVpin > 255 )
  {
    displayVpin = atoi ( DISPLAY_DEFAULT_VPIN );
    Serial.print ( "**** Bad displayVpin input value of " );
    Serial.println ( displayVpinC );
  }
  Serial.print ( "   Set displayVpin/displayLabel to " ) ; Serial.print ( displayVpin );
  Serial.print ( "/" ); Serial.println ( displayLabel );   
  Blynk.setProperty ( displayVpin, "label", displayLabel );  

  Serial.println();  
} // end updateDynamicParameters
#endif // (updateDynamicParameters not needed if NOT USE_WM)




// BLYNK_CONNECTED GETS CALLED WHEN CONNECTING TO BLYNK SERVERS
// GETS CALLED IMMEDIATELY ON FIRST CONNECT TO BLYNK SERVER, TOO
BLYNK_CONNECTED()
{
  Serial.println ( "\nBLYNK_CONNECTED..." );  

  #if USE_WM
    // Convert the Config Portal (or compiler constant) Virtual Pin char values to Blynk-usable ints
    updateDynamicParameters();  
  #endif

} // end BLYNK_CONNECTED


// BLYNK_APP_CONNECTED GETS CALLED WHEN APP CONNECTS TO BLYNK SERVERS
// IT IS NOT SUPER RELIABLE !  
BLYNK_APP_CONNECTED()
{
  Serial.println ( "\nBLYNK_APP_CONNECTED..." );  

} // end BLYNK_APP_CONNECTED

/****************************************************************************************************************************
   AM2315_ESP8266.ino
   For ESP8266 boards

   Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
   Licensed under MIT license
   Version: 1.0.12

   Original Blynk Library author:
   @file       BlynkSimpleEsp8266.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Jan 2015
   @brief

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      28/10/2019 Initial coding
    1.0.1   K Hoang      28/10/2019 Add features
    1.0.2   K Hoang      21/11/2019 Fix bug. Add features.
    1.0.3   K Hoang      31/11/2019 Fix compiler errors for ESP8266 core pre-2.5.2. Add examples.
    1.0.4   K Hoang      07/01/2020 Add configurable personalized RFC-952 DHCP hostname
    1.0.5   K Hoang      20/01/2020 Add configurable static IP, GW, SN, DNS1, DNS2 and Config Portal static IP and Credentials
    1.0.6   K Hoang      05/02/2020 Optimize, fix EEPROM size to 2K from 4K, shorten code size, add functions
    1.0.7   K Hoang      18/02/2020 Add checksum, enable AutoConnect to configurable MultiWiFi and MultiBlynk Credentials
    1.0.8   K Hoang      24/02/2020 Fix AP-staying-open bug. Add clearConfigData()
    1.0.9   K Hoang      12/03/2020 Enhance Config Portal GUI
    1.0.10  K Hoang      08/04/2020 SSID password maxlen is 63 now. Permit special chars # and % in input data.
    1.0.11  K Hoang      09/04/2020 Enable adding dynamic custom parameters from sketch
    1.0.12  K Hoang      13/04/2020 Fix MultiWiFi/Blynk bug introduced in broken v1.0.11
 *****************************************************************************************************************************/

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>

#define USE_SPIFFS    true

//You have to download Blynk WiFiManager Blynk_WM library at //https://github.com/khoih-prog/Blynk_WM
// In order to enable (USE_BLYNK_WM = true). Otherwise, use (USE_BLYNK_WM = false)
#define USE_BLYNK_WM   true
//#define USE_BLYNK_WM   false

#define USE_SSL     false

#if USE_BLYNK_WM
#if USE_SSL
#include <BlynkSimpleEsp8266_SSL_WM.h>        //https://github.com/khoih-prog/Blynk_WM
#else
#include <BlynkSimpleEsp8266_WM.h>            //https://github.com/khoih-prog/Blynk_WM
#endif

#define USE_DYNAMIC_PARAMETERS      false

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp32_WM.h> and <BlynkSimpleEsp32_SSL_WM.h>
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
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

#else

MenuItem myMenuItems [] = {};

#endif

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;
/////// // End dynamic Credentials ///////////

#else
#if USE_SSL
#include <BlynkSimpleEsp8266_SSL.h>
#define BLYNK_HARDWARE_PORT     9443
#else
#include <BlynkSimpleEsp8266.h>
#define BLYNK_HARDWARE_PORT     8080
#endif
#endif

#if !USE_BLYNK_WM

#ifndef LED_BUILTIN
#define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#endif

#define USE_LOCAL_SERVER    true
//#define USE_LOCAL_SERVER    false

// If local server
#if USE_LOCAL_SERVER
char blynk_server[]   = "yourname.duckdns.org";
#endif

char auth[]     = "***";
char ssid[]     = "***";
char pass[]     = "***";

#endif

#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_AM2315.h>        // To install Adafruit AM2315 library

#define PIN_D1            5         // Pin D1 mapped to pin GPIO5/SCL of ESP8266
#define PIN_D2            4         // Pin D2 mapped to pin GPIO4/SDA of ESP8266

// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock (PIN_D1 / SCL)
// Connect YELLOW to i2c data (PIN_D2 / SDA)

Adafruit_AM2315 AM2315;

#define AM2315_DEBUG     true

BlynkTimer timer;
Ticker     led_ticker;

#define READ_INTERVAL        30000          //read AM2315 interval 30s

void ReadData()
{
  static float temperature, humidity;

  if (!AM2315.readTemperatureAndHumidity(&temperature, &humidity))
  {
#if AM2315_DEBUG
    Serial.println("Failed to read data from AM2315");
#endif

    return;
  }

#if AM2315_DEBUG
  Serial.println("Temp *C: " + String(temperature));
  Serial.println("Humid %: " + String(humidity));
#endif

  //V1 and V2 are Blynk Display widgets' VPIN
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
}

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
}

void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk.connected())
  {
    set_led(LOW);
    led_ticker.once_ms(111, set_led, (byte) HIGH);
    Serial.print("B");
  }
  else
  {
    Serial.print("F");
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(" ");
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // report status to Blynk
    heartBeatPrint();

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.println("\nStarting");

  if (!AM2315.begin())
  {
    Serial.println("Sensor not found, check wiring & pullups!");
  }

#if USE_BLYNK_WM
  // From v1.0.5
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 200, 1));

  // From v1.0.5, select either one of these to set static IP + DNS
  Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));

  // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
  //Blynk.begin();
  // Use this to personalize DHCP hostname (RFC952 conformed)
  // 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char
  Blynk.begin("AM2315_ESP8266");
#else
  WiFi.begin(ssid, pass);

#if USE_LOCAL_SERVER
  Blynk.config(auth, blynk_server, BLYNK_HARDWARE_PORT);
#else
  Blynk.config(auth);
#endif

  Blynk.connect();
#endif

  if (Blynk.connected())
  {
#if USE_SPIFFS
    Serial.print("\nBlynk ESP8266 using SPIFFS connected.");
    
#else
    Serial.println("\nBlynk ESP8266 SSL using EEPROM connected.");
#endif
#if USE_BLYNK_WM
    Serial.println("Board Name : " + Blynk.getBoardName());
#endif
  }

  timer.setInterval(READ_INTERVAL, ReadData);
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials(void)
{
  Serial.println("Your stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk.run();
  timer.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif     
}

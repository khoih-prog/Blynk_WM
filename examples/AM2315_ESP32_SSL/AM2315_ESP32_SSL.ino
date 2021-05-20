/****************************************************************************************************************************
  AM2315_ESP32_SSL.ino
  For ESP32 boards

  Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license
  Version: 1.6.0

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
 *****************************************************************************************************************************/

#include "defines.h"

#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_AM2315.h>        // To install Adafruit AM2315 library


// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock (PIN_D22 / SCL)
// Connect YELLOW to i2c data (PIN_D21 / SDA)

Adafruit_AM2315 AM2315;

#define AM2315_DEBUG     true

BlynkTimer timer;
Ticker     led_ticker;

#define READ_INTERVAL        60000L          //read AM2315 interval 30s

void readAndSendData()
{
  static float temperature, humidity;

  temperature = AM2315.readTemperature();
  humidity    = AM2315.readHumidity();

  if (!isnan(temperature) && !isnan(humidity))
  {
    Blynk.virtualWrite(V1, String(temperature, 1));
    Blynk.virtualWrite(V2, String(humidity, 1));

#if AM2315_DEBUG
    Serial.println("Temp *C: " + String(temperature));
    Serial.println("Humid %: " + String(humidity));
#endif
  }
  else
  {
    Blynk.virtualWrite(V1, "NAN");
    Blynk.virtualWrite(V2, "NAN");
  }
}

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
}

void heartBeatPrint()
{
  static int num = 1;

  if (Blynk.connected())
  {
    set_led(HIGH);
    led_ticker.once_ms(111, set_led, (byte) LOW);
    Serial.print(F("B"));
  }
  else
  {
    Serial.print(F("F"));
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
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

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if (USE_LITTLEFS)
  Serial.print(F("\nStarting AM2315_ESP32_SSL using LITTLEFS"));
#elif (USE_SPIFFS)
  Serial.print(F("\nStarting AM2315_ESP32_SSL using SPIFFS"));  
#else
  Serial.print(F("\nStarting AM2315_ESP32_SSL using EEPROM"));
#endif

#if USE_SSL
  Serial.print(F(" with SSL on ")); Serial.println(ARDUINO_BOARD);
#else
  Serial.print(F(" without SSL on ")); Serial.println(ARDUINO_BOARD);
#endif

#if USE_BLYNK_WM
  Serial.println(BLYNK_WM_VERSION);
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);
#endif

  if (!AM2315.begin())
  {
    Serial.println(F("Sensor not found, check wiring & pullups!"));
  }

#if USE_BLYNK_WM

  // From v1.0.5
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 200, 1));
  // Set config portal channel, defalut = 1. Use 0 => random channel from 1-13
  Blynk.setConfigPortalChannel(0);

  // From v1.0.5, select either one of these to set static IP + DNS
  Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));

//////////////////////////////////////////////
  
#if USING_CUSTOMS_STYLE
  Blynk.setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  Blynk.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
#endif

#if USING_CORS_FEATURE  
  Blynk.setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  //////////////////////////////////////////////
  
  // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
  //Blynk.begin();
  // Use this to personalize DHCP hostname (RFC952 conformed)
  // 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char
  //Blynk.begin("AM2315_ESP32_SSL");
  Blynk.begin(HOST_NAME);
#else
  WiFi.begin(ssid, pass);

#if USE_LOCAL_SERVER
  Blynk.config(auth, blynk_server, BLYNK_HARDWARE_PORT);
#else
  Blynk.config(auth);
#endif

  Blynk.connect();
#endif

  timer.setInterval(READ_INTERVAL, readAndSendData);

  if (Blynk.connected())
  {
#if (USE_LITTLEFS)
    Serial.println(F("\nBlynk ESP32 using LittleFS connected"));
#elif (USE_SPIFFS)
    Serial.println(F("\nBlynk ESP32 using SPIFFS connected."));
#else
    Serial.println(F("\nBlynk ESP32 using EEPROM connected."));
    Serial.printf("EEPROM size = %d bytes, EEPROM start address = %d / 0x%X\n", EEPROM_SIZE, EEPROM_START, EEPROM_START);
#endif

#if USE_BLYNK_WM
    Serial.print(F("Board Name : ")); Serial.println(Blynk.getBoardName());
#endif
  }
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
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
}

#endif

void loop()
{
  Blynk.run();
  timer.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  displayCredentialsInLoop();
#endif
}

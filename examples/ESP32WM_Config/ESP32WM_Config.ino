/****************************************************************************************************************************
  ESP32WM_Config.ino
  For ESP32 boards
  
  Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
  Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
  Licensed under MIT license
  Version: 1.6.1

  Version    Modified By   Date      Comments
  -------    -----------  ---------- -----------
  1.0.0     K Hoang      28/10/2019 Initial coding
  ...
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
 *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#include <Ticker.h>
#include <DHT.h>        // https://github.com/adafruit/DHT-sensor-library

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;
Ticker     led_ticker;

void readAndSendData()
{
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity))
  {
    Blynk.virtualWrite(V17, String(temperature, 1));
    Blynk.virtualWrite(V18, String(humidity, 1));
  }
  else
  {
    Blynk.virtualWrite(V17, "NAN");
    Blynk.virtualWrite(V18, "NAN");
  }

  // Blynk Timer uses millis() and is still working even if WiFi/Blynk not connected
  Serial.print(F("R"));
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

  if (num == 40)
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
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if (USE_LITTLEFS)
  Serial.print(F("\nStarting ESP32_WM_Config using LITTLEFS"));
#elif (USE_SPIFFS)
  Serial.print(F("\nStarting ESP32_WM_Config using SPIFFS"));  
#else
  Serial.print(F("\nStarting ESP32_WM_Config using EEPROM"));
#endif

#if USE_SSL
  Serial.print(F(" with SSL on ")); Serial.println(ARDUINO_BOARD);
#else
  Serial.print(F(" without SSL on ")); Serial.println(ARDUINO_BOARD);
#endif

  Serial.println(BLYNK_WM_VERSION);
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);

  dht.begin();

  // From v1.0.5
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP32", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 220, 1));
  // Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);

  // From v1.0.5, select either one of these to set static IP + DNS
  Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 230), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
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
  //Blynk.begin("ESP32-WM-Config");
  Blynk.begin(HOST_NAME);

  timer.setInterval(60 * 1000, readAndSendData);

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

    Serial.print(F("Board Name : ")); Serial.println(Blynk.getBoardName());
  }
}

#if USE_DYNAMIC_PARAMETERS
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

#if USE_DYNAMIC_PARAMETERS
  displayCredentialsInLoop();
#endif
}

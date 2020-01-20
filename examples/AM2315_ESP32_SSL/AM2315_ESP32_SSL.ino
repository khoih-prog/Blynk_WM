/****************************************************************************************************************************
 * AM2315_ESP32_SSL.ino
 * For ESP32 boards
 *
 * Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
 * configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
 * Licensed under MIT license
 * Version: 1.0.5
 *
 * Original Blynk Library author:
 * @file       BlynkSimpleEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      28/10/2019 Initial coding
 *  1.0.1   K Hoang      28/10/2019 Add features
 *  1.0.2   K Hoang      21/11/2019 Fix bug. Add features.
 *  1.0.4   K Hoang      07/01/2020 Use configurable personalized RFC-952 DHCP hostname in Blynk_WM v1.0.4
 *  1.0.5   K Hoang      20/01/2020 Add configurable static IP, GW, SN, DNS1, DNS2 and Config Portal static IP and Credentials
 *****************************************************************************************************************************/

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>

#define USE_SPIFFS    true

//You have to download Blynk WiFiManager Blynk_WM library at //https://github.com/khoih-prog/Blynk_WM
// In order to enable (USE_BLYNK_WM = true). Otherwise, use (USE_BLYNK_WM = false)
#define USE_BLYNK_WM   true
//#define USE_BLYNK_WM   false

#define USE_SSL     true
//#define USE_SSL     false

#if USE_BLYNK_WM
  #if USE_SSL
    #include <BlynkSimpleEsp32_SSL_WM.h>        //https://github.com/khoih-prog/Blynk_WM
  #else
    #include <BlynkSimpleEsp32_WM.h>            //https://github.com/khoih-prog/Blynk_WM
  #endif
#else
  #if USE_SSL
    #include <BlynkSimpleEsp32_SSL.h>
    #define BLYNK_HARDWARE_PORT     9443
  #else
    #include <BlynkSimpleEsp32.h>
    #define BLYNK_HARDWARE_PORT     8080   
  #endif
#endif

#if !USE_BLYNK_WM
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

#define PIN_D21           21        // Pin D21 mapped to pin GPIO21/SDA of ESP32
#define PIN_D22           22        // Pin D22 mapped to pin GPIO22/SCL of ESP32

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

void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk.connected())
  {
    set_led(HIGH);
    led_ticker.once_ms(111, set_led, (byte) LOW); 
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
  pinMode(LED_BUILTIN, OUTPUT);
 
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
    Blynk.begin("AM2315_ESP32_SSL");
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
     #if USE_SPIFFS     
      Serial.println("\nBlynk ESP32 SSL using SPIFFS connected. Board Name : " + Blynk.getBoardName());
    #else
      Serial.println("\nBlynk ESP32 SSL using EEPROM connected. Board Name : " + Blynk.getBoardName());
    #endif  

  }
}

void loop()
{  
  Blynk.run();
  timer.run();
  check_status();  
}

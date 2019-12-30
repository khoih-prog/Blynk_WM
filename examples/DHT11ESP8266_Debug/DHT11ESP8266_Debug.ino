/****************************************************************************************************************************
 * DHT11ESP8266_Debug.ino
 * For ESP8266 boards
 *
 * Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
 * configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
 * Licensed under MIT license
 * Version: 1.0.2
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
 *****************************************************************************************************************************/

#define BLYNK_PRINT Serial

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>

#define USE_SPIFFS    true

#include <BlynkSimpleEsp8266_WM.h>
#include <Ticker.h>
#include <DHT.h>

#define PIN_LED   2   // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
#define PIN_D2    4   // Pin D2 mapped to pin GPIO4 of ESP8266
  
#define DHT_PIN     PIN_D2
#define DHT_TYPE    DHT11

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
}

void set_led(byte status)
{
  digitalWrite(PIN_LED, status);
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     15000L

  // Send status report every STATUS_REPORT_INTERVAL (10) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // report status to Blynk
    if (Blynk.connected())
    {
      set_led(LOW);
      led_ticker.once_ms(111, set_led, (byte) HIGH);

      Serial.println("B");
    }
    else
    {
      Serial.println("F");
    }

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup() 
{
    // Debug console
    Serial.begin(115200);
    pinMode(PIN_LED, OUTPUT);

    Serial.println("\nStarting ...");
    
    dht.begin();
    Blynk.begin();
    timer.setInterval(60 * 1000, readAndSendData);

    if (Blynk.connected())
    {
       #if USE_SPIFFS     
        Serial.println("\nBlynk ESP8288 using SPIFFS connected. Board Name : " + Blynk.getBoardName());
      #else
        Serial.println("\nBlynk ESP8288 using EEPROM connected. Board Name : " + Blynk.getBoardName());
      #endif  
    }
}

void loop() 
{
    Blynk.run();
    timer.run();
    check_status();
}

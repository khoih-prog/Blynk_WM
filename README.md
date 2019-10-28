## Blynk_ESP_WM
I'm inspired by [EasyBlynk8266] (https://github.com/Barbayar/EasyBlynk8266)
 
To help you to eliminate hardcoding your Wifi and Blynk credentials for ESP8266 and ESP32 (with / wwithout SSL), and updating/reflashing every time when you need to change them.

Just copy BlynkSimpleEsp8266_WM.h, BlynkSimpleEsp8266_SSL_WM.h, BlynkSimpleEsp32_WM.h and BlynkSimpleEsp32_SSL_WM.h into Blynk libraries directory (normally ./Arduino/libraries/Blynk/src)

In your code, replace
1. BlynkSimpleEsp8266.h     with BlynkSimpleEsp8266_WM.h      for ESP8266 without SSL
2. BlynkSimpleEsp8266_SSL.h with BlynkSimpleEsp8266_SSL_WM.h  for ESP8266 with SSL
3. BlynkSimpleEsp32.h       with BlynkSimpleEsp32_WM.h        for ESP32 without SSL
4. BlynkSimpleEsp32_SSL.h   with BlynkSimpleEsp32_SSL_WM.h    for ESP32 with SSL
5. In your code, insert

```
#define USE_SPIFFS    true
```
to use SPIFFS or

```
#define USE_SPIFFS    false
```
to use EEPROM ( 172 bytes from address EEPROM_START ) to save your configuration data.
EEPROM_SIZE can be specified from 256 to 4096 bytes. See examples ESP32WM_Config and ESP8266WM_Config.


```
// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

```

Then replace

, `Blynk.begin(...)` with `Blynk.begin()` in your code. Keep `Blynk.run()`.

That's it.

## So, how it works?
If it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an access point called `ESP_xxxxxx`. Connect to it using password `MyESP_xxxxxx` .

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Selection_004.jpg">
</p>

After you connected, please, go to http://192.168.4.1.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Selection_005.jpg">
</p>

Enter your credentials, then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically.

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for graphical user interface.

## Prerequisite
* ESP8266 core for Arduino https://github.com/esp8266/Arduino#installing-with-boards-manager
* Blynk library https://www.arduino.cc/en/guide/libraries#toc3

## TO DO

1. Same features for other boards with WiFi.

## DONE

1. Permit EEPROM size and location configurable to avoid conflict with others.
2. More flexible to configure reconnection timeout.
3. For fresh config data, don't need to wait for connecting timeout before entering config portal.

## Hello World
Please take a look at examples, as well.
```
#define BLYNK_PRINT Serial

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>

//#define USE_SPIFFS                  true
#define USE_SPIFFS                  false

#if (!USE_SPIFFS)
  // EEPROM_SIZE must be <= 4096 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (4 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   1024
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
// Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h>

#define USE_SSL   true

#if USE_SSL
  #include <BlynkSimpleEsp8266_SSL_WM.h>
#else
  #include <BlynkSimpleEsp8266_WM.h>
#endif

void setup() 
{
    Blynk.begin();
}


void loop() 
{
    Blynk.run();
}
```

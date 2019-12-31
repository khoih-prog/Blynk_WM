## Blynk_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager)

I'm inspired by [`EasyBlynk8266`] (https://github.com/Barbayar/EasyBlynk8266)
 
To help you to eliminate `hardcoding` your Wifi and Blynk credentials for ESP8266 and ESP32 (with / wwithout SSL), and updating/reflashing every time when you need to change them.

### Installation

The easiest way is to use `Arduino Library Manager`. Search for `Blynk_WiFiManager`, then select / install the latest version.

Another way to install is to:

1. Navigate to [Blynk_WM] (https://github.com/khoih-prog/Blynk_WM) page.
2. Download the latest release `Blynk_WM-master.zip`.
3. Extract the zip file to `Blynk_WM-master` directory 
4. Copy whole `Blynk_WM-master/src` folder to Arduino libraries' `src` directory such as `.Arduino/libraries/Blynk/src`.

The file BlynkSimpleEsp8266_WM.h, BlynkSimpleEsp8266_SSL_WM.h, BlynkSimpleEsp32_WM.h and BlynkSimpleEsp32_SSL_WM.h must be placed in Blynk libraries `src` directory (normally ./Arduino/libraries/Blynk/src)

### How to use

In your code, replace
1. `BlynkSimpleEsp8266.h`     with `BlynkSimpleEsp8266_WM.h`      for ESP8266 `without SSL`
2. `BlynkSimpleEsp8266_SSL.h` with `BlynkSimpleEsp8266_SSL_WM.h`  for ESP8266 `with SSL`
3. `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WM.h`        for ESP32 `without SSL`
4. `BlynkSimpleEsp32_SSL.h`   with `BlynkSimpleEsp32_SSL_WM.h`    for ESP32 `with SSL`
5. In your code, insert

```
#define USE_SPIFFS    true
```
to use SPIFFS or

```
#define USE_SPIFFS    false
```
to use EEPROM ( 172 bytes from address EEPROM_START ) to save your configuration data.
EEPROM_SIZE can be specified from 256 to 4096 bytes. See examples [ESP32WM_Config] (https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP32WM_Config) and [ESP8266WM_Config] (https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP8266WM_Config).


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

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:
```
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```
just
```
void loop()
{
  Blynk.run();
  ...
}
```

## Prerequisite
* `ESP8266 core 2.5.2 or later` for Arduino (https://github.com/esp8266/Arduino#installing-with-boards-manager)
* `Blynk library 0.6.1 or later` (https://www.arduino.cc/en/guide/libraries#toc3)

## TO DO

1. Same features for other boards with WiFi.

## DONE

1. Permit EEPROM size and location configurable to avoid conflict with others.
2. More flexible to configure reconnection timeout.
3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
4. If the config data not entered completely (SSID, password, Server and Blynk token), entering config portal
5. Correct the operation of BUILTIN_LED
6. Modify code to be compatible with ESP8266 core pre-2.5.2.

## Example
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

### Releases v1.0.3

***New in this version***

1. Modify code to be compatible with ESP8266 core pre-2.5.2. But it's still advisable to update to the latest stable core, such as 2.6.3

2. Add examples

### Releases v1.0.2

***Features***

1. This release of very-easy-to-use will help you to eliminate hardcoding your Wifi and Blynk credentials for ESP8266 and ESP32 (with / without SSL), and updating/reflashing every time when you need to change them.

2. Configuration data are stored in either SPIFFS or EEPROM.

3. When WiFi and/or Blynk connection is lost, the WM will try auto-reconnect.

***New in this version***

1. Fix bug

2. If the config data not entered completely (SSID, password, Server and Blynk token), entering config portal

3. Correct the operation of BUILTIN_LED

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2019- Khoi Hoang

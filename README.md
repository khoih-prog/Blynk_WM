## Blynk_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager)

I'm inspired by [`EasyBlynk8266`] (https://github.com/Barbayar/EasyBlynk8266)
 
To help you to eliminate `hardcoding` your Wifi and Blynk credentials for ESP8266 and ESP32 (with / wwithout SSL), and updating/reflashing every time when you need to change them.

With version `v1.0.5` or later, you now can configure:

1. `Config Portal Static IP address, Name and Password.`
2. `Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.`

### Installation

The suggested way to install is to:

1. Navigate to [Blynk_WM] (https://github.com/khoih-prog/Blynk_WM) page.
2. Download the latest release `Blynk_WM-master.zip`.
3. Extract the zip file to `Blynk_WM-master` directory 
4. Copy whole `Blynk_WM-master/src` folder to Arduino libraries' `src` directory such as `~/Arduino/libraries/Blynk/src`.

The file BlynkSimpleEsp8266_WM.h, BlynkSimpleEsp8266_SSL_WM.h, BlynkSimpleEsp32_WM.h and BlynkSimpleEsp32_SSL_WM.h must be placed in Blynk libraries `src` directory (normally `~/Arduino/libraries/Blynk/src`)

Another way is to use `Arduino Library Manager`. Search for `Blynk_WiFiManager`, then select / install the latest version. Then move the 2 files `BlynkSimpleEsp8266_SSL_WM.h` and `BlynkSimpleEsp32_SSL_WM.h` from directory `~/Arduino/libraries/Blynk_WiFiManager/src` into Blynk libraries `src` directory (normally `~/Arduino/libraries/Blynk/src`)

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

Then replace `Blynk.begin(...)` with :

1. `Blynk.begin()` to use default DHCP hostname `ESP8266-XXXXXX` or `ESP32-XXXXXX`

or to have a personalized hostname `(RFC952-conformed,- 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char)`

2. `Blynk.begin("Personalized-HostName")`

in your code. Keep `Blynk.run()` intact.

That's it.

Also see examples: 
1. [AM2315_ESP32_SSL](examples/AM2315_ESP32_SSL)
2. [AM2315_ESP8266](examples/AM2315_ESP8266)
3. [DHT11ESP32](examples/DHT11ESP32) 
4. [DHT11ESP32_SSL](examples/DHT11ESP32_SSL) 
5. [DHT11ESP8266](examples/DHT11ESP8266)
6. [DHT11ESP8266_Debug](examples/DHT11ESP8266_Debug)
7. [DHT11ESP8266_SSL](examples/DHT11ESP82662_SSL) 
8. [ESP32WM_Config](examples/ESP32WM_Config)
9. [ESP82WM_Config](examples/ESP8266WM_Config)


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

The following is the sample terminal output when running example [ESP32WM_Config](examples/ESP32WM_Config)

```
Starting ...
[34] RFC925 Hostname = ESP32-WM-Config
[46] Header = SSL_ESP32, SSID = ***, PW = ***
[46] Server = account.duckdns.org, Port = 9443, Token = ***
[47] Board Name = ESP32-WM-SSL-Config
[50] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[146] Use static IP
[151] connectToWifi: start
[402] connectToWifi: connected OK
[402] IP = 192.168.2.230, GW = 192.168.2.1, SN = 255.255.255.0
[402] DNS1 = 192.168.2.1, DNS2 = 8.8.8.8
[403] begin: WiFi connected. Try connecting to Blynk
[408] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[3684] Certificate OK
[3696] Ready (ping: 10ms).
[3763] begin: WiFi and Blynk connected

Blynk ESP32 using EEPROM connected. Board Name : ESP32-WM-SSL-Config
EEPROM size = 4096 bytes, EEPROM start address = 1024 / 0x400

```

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```
just

```cpp
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
 7. Add RFC952 hostname
 8. Add configurable Config Portal IP, SSID and Password
 9. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.

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

#define USE_SSL   false

#if USE_SSL
  #include <BlynkSimpleEsp8266_SSL_WM.h>
#else
  #include <BlynkSimpleEsp8266_WM.h>
#endif

void setup() 
{
    ....
    
    // From v1.0.5
    // Set config portal SSID and Password
    Blynk.setConfigPortal("TestPortal", "TestPortalPass");
    // Set config portal IP address
    Blynk.setConfigPortalIP(IPAddress(192, 168, 220, 1));

    // From v1.0.5, select either one of these to set static IP + DNS
    Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 230), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
    //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0), 
    //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
    //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0), 
    //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));   
    
  // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
  //Blynk.begin();
  // Use this to personalize DHCP hostname (RFC952 conformed)
  // 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char
  Blynk.begin("Personalized-HostName");
}

void loop() 
{
    Blynk.run();
}
```

### Releases v1.0.5

***Why this version***

Normally, the `default Portal IP (192.168.4.1)`, SSID and PW as well as the `dynamically allocated` board's IP address are good enough.
In special cases where there is conflict, if static IP is required or bad router's DNS settings, you can use the new features to force the configurable IP addresses. ***But please use with care to avoid potential issues.***

***New in this version***

Add new features to enable :

1. configuring Portal Static IP address, Name and Password.
2. configuring Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.

### Releases v1.0.4

***Why this version***

I'm really fed-up with the unfriendly, confusing and cryptic DHCP hostnames such as `ESP_XXXXXX`, `espressif` using ChipID. Thanks to an issue opened in library [ESP_WiFiManager](https://github.com/khoih-prog/ESP_WiFiManager), I decided to add this option to have built-in, yet configurable DHCP hostname to these libraries.

Now you can easily specify and have the friendly, identifiable, RFC-952-conformed DHP hostnames associated with your boards, such as `SmartFarm-1`, `Irrigation`, `Master-Controller`, etc. You'll be happier to have a look at your WiFi Router DHCP list.

***New in this version***

1. Add configurable personalized RFC-952 DHCP hostname and setHostname()

2. Modify examples to use new feature

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

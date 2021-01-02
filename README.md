## Blynk_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_WM.svg)](https://github.com/khoih-prog/Blynk_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_WM.svg)](http://github.com/khoih-prog/Blynk_WM/issues)
[![star this repo](https://githubbadges.com/star.svg?user=khoih-prog&repo=Blynk_WM&style=default)](https://github.com/khoih-prog/Blynk_WM)

---
---

## Table of Contents

* [Important Note](#important-note)
* [Why do we need the new Async Blynk_Async_WM library](#why-do-we-need-the-new-async-blynk_async_wm-library)
* [Why do we need this Blynk_WM library](#why-do-we-need-this-blynk_wm-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.16](#releases-v1016)
  * [Releases v1.0.15](#releases-v1015)
  * [Releases v1.0.14](#releases-v1014)
  * [Releases v1.0.13](#releases-v1013)
  * [Releases v1.0.12](#releases-v1012)
  * [Releases v1.0.11](#releases-v1011)
  * [Releases v1.0.10](#releases-v1010)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [I) For Arduino IDE](#i-for-arduino-ide)
  * [II) For VS Code & PlatformIO:](#ii-for-vs-code--platformio)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [How to use](#how-to-use)
* [HOWTO use default Credentials and have them pre-loaded onto Config Portal](#howto-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [ 1. To load Default Credentials](#1-to-load-default-credentials)
  * [ 2. To use system default to load "blank" when there is no valid Credentials](#2-to-use-system-default-to-load-blank-when-there-is-no-valid-credentials)
  * [ 3. Example of Default Credentials](#3-example-of-default-credentials)
  * [ 4. How to add dynamic parameters from sketch](#4-how-to-add-dynamic-parameters-from-sketch)
  * [ 5. If you don't need to add dynamic parameters](#5-if-you-dont-need-to-add-dynamic-parameters)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Important Notes](#important-notes)
* [Why using this Blynk_WiFiManager with MultiWiFi-MultiBlynk features](#why-using-this-blynk_wifimanager-with-multiwifi-multiblynk-features)
* [Examples](#examples)
  * [ 1. AM2315_ESP32_SSL](examples/AM2315_ESP32_SSL)
  * [ 2. AM2315_ESP8266](examples/AM2315_ESP8266)
  * [ 3. DHT11ESP32](examples/DHT11ESP32)
  * [ 4. DHT11ESP32_SSL](examples/DHT11ESP32_SSL)
  * [ 5. DHT11ESP8266](examples/DHT11ESP8266)
  * [ 6. DHT11ESP8266_Debug](examples/DHT11ESP8266_Debug)
  * [ 7. DHT11ESP8266_SSL](examples/DHT11ESP82662_SSL)
  * [ 8. ESP32WM_Config](examples/ESP32WM_Config)
  * [ 9. ESP8266WM_Config](examples/ESP8266WM_Config)
  * [10. Blynk_WM_Template](examples/Blynk_WM_Template)
  * [11. **ESP32WM_MRD_Config**](examples/ESP32WM_MRD_Config)
  * [12. **ESP8266WM_MRD_Config**](examples/ESP8266WM_MRD_Config)
* [So, how it works?](#so-how-it-works)
* [Example ESP32WM_MRD_Config](#example-esp32wm_mrd_config)
  * [1. File ESP32WM_MRD_Config.ino](#1-file-esp32wm_mrd_configino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU](#1-esp8266wm_mrd_config-using-littlefs-with-ssl-on-esp8266_nodemcu)
    * [1.1. No MultiReset Detected => Running normally](#11-no--multireset-detected--running-normally)
    * [1.2. MultiReset Detected => Enter Config Portal](#12-multireset-detected--enter-config-portal)
  * [2. DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU](#2-dht11esp8266_ssl-using-littlefs-with-ssl-on-esp8266_nodemcu)
  * [3. ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV](#3-esp32wm_mrd_config-using-littlefs-without-ssl-on-es32_dev)
    * [3.1. No MultiReset Detected => Running normally](#31-no--multireset-detected--running-normally)
    * [3.2. MultiReset Detected => Enter Config Portal](#32-multireset-detected--enter-config-portal)
    * [3.3. Exit Config Portal with Data](#33-exit-config-portal-with-data)
    * [3.4. WiFi Lost => AutoReconnect WiFi and Blynk.](#34-wifi-lost--autoreconnect-wifi-and-blynk)
  * [4. DHT11ESP32_SSL using LittleFS with SSL on ESP32_DEV](#4-dht11esp32_ssl-using-littlefs-with-ssl-on-es32_dev)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Note

This [**Blynk_WiFiManager**](https://github.com/khoih-prog/Blynk_WM) has just been modified to create the new [**Blynk_Async_WM**](https://github.com/khoih-prog/Blynk_Async_WM) in order to use the better and more efficient [**ESPAsyncWebServer Library**](https://github.com/me-no-dev/ESPAsyncWebServer), instead of the (ESP8266)WebServer library.

The new [**Blynk_Async_WM**](https://github.com/khoih-prog/Blynk_Async_WM) is based on and sync'ed with [**Blynk_WiFiManager**](https://github.com/khoih-prog/Blynk_WM). Therefore, all the features currently supported by this [**Blynk_WiFiManager**](https://github.com/khoih-prog/Blynk_WM) will be available to the new library. The code change is to port to the new library is also very negligible, **mostly just changing the include file from `BlynkSimpleEspxxxx_WM.h` to `BlynkSimpleEspxxxx_Async_WM.h`.**

---

### Why do we need the new Async [Blynk_Async_WM library](https://github.com/khoih-prog/Blynk_Async_WM)

- Using asynchronous network means that you can handle **more than one connection at the same time**
- **You are called once the request is ready and parsed**
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- **Easy to use API, HTTP Basic and Digest MD5 Authentication (default), ChunkedResponse**
- Easily extensible to handle **any type of content**
- Supports Continue 100
- **Async WebSocket plugin offering different locations without extra servers or ports**
- Async EventSource (Server-Sent Events) plugin to send events to the browser
- URL Rewrite plugin for conditional and permanent url rewrites
- ServeStatic plugin that supports cache, Last-Modified, default index and more
- Simple template processing engine to handle templates

---


### Why do we need this [Blynk_WM library](https://github.com/khoih-prog/Blynk_WM)

#### Features

This is a Blynk and WiFiManager Library for configuring/auto(re)connecting **ESP8266/ESP32** modules to the best or available MultiWiFi APs and MultiBlynk servers at runtime. Connection is with or without SSL. Configuration data to be saved in either LittleFS, SPIFFS or EEPROM. Default Credentials as well as Dynamic custom parameters can be added and modified easily without coding knowledge. DoubleResetDetector is used to force Config Portal opening even if the Credentials are still valid.
 
This library is designed to help you to eliminate `hardcoding` your Wifi and Blynk credentials for ESP8266 and ESP32 (with/without SSL), and updating/reflashing every time you need to change them.

With version `v1.1.0` or later, you can use:

1. `LittleFS for ESP32`
2. `Multiple Reset Detection to enter Config Portal`

With version `v1.0.7` or later, you can configure:

1. `Multiple WiFi Credentials (SSID, Password) and system will autoconnect to the best and available WiFi SSID.`
2. `Multiple Blynk Credentials (Server, Token) and system will autoconnect to the available Blynk Servers.`

With version `v1.0.5` or later, you can configure:

1. `Config Portal Static IP address, Name and Password.`
2. `Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.`

#### Currently supported Boards

This [**BlynkESP32_BT_WF** library](https://github.com/khoih-prog/BlynkESP32_BT_WF) currently supports these following boards:

 1. **ESP8266 and ESP32-based boards using EEPROM, SPIFFS or LittleFS**.


---
---

## Changelog

### Major Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library
2. Add support to MultiDetectDetector. **MultiDetectDetector** feature to force Config Portal when configurable multi-reset is detected within predetermined time.
3. Clean-up all compiler warnings possible.
4. Add Table of Contents
5. Add Version String
6. Add MRD-related examples.

### Releases v1.0.16

1. Fix bug and logic of USE_DEFAULT_CONFIG_DATA.
2. Auto format SPIFFS/LittleFS for first time usage.

#### Releases v1.0.15

1. Update to use LittleFS for ESP8266 core 2.7.1+.
2. Fix SSL connection bug.
3. Fix dynamicParams loading bug in v1.0.14. 
4. Add [Blynk_WM_Template example](examples/Blynk_WM_Template) contributed by [Thor Johnson](https://github.com/thorathome).

Again thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome) for testing, bug finding, feature adding, README rewriting, collaborating, etc..

#### Releases v1.0.14

1. Fix dynamicParams bug in v1.0.13. Again thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome)

#### Releases v1.0.13

1. Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
2. **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
3. Configurable **Config Portal Title** to be either HostName, BoardName or default undistinguishable names.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.

Thanks to [Thor Johnson](https://github.com/thorathome) to test, suggest and encourage to add those new features in v1.0.13, such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD.

### Releases v1.0.12

1. Fix severe bug in v1.0.11

#### Releases v1.0.11

##### Severe connecting bug. Don't use

1. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved **automatically in EEPROM, or SPIFFS**.

#### Releases v1.0.10

1. WiFi Password max length is 63, according to WPA2 standard
2. Permit to input special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

---
---

## Prerequisites

1. [`Arduino IDE 1.8.13+`](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1+`](https://github.com/blynkkk/blynk-library/releases)
3. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
4. [`ESP8266 core 2.7.4+`](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards. To use ESP8266 core 2.7.1+ for LittleFS.
5. [`ESP_DoubleResetDetector library 1.1.1+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to use DRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).
6. [`ESP_MultiResetDetector library 1.1.1+`](https://github.com/khoih-prog/ESP_MultiResetDetector) to use MRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_MultiResetDetector.svg?)](https://www.ardu-badge.com/ESP_MultiResetDetector).
7. [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to use ESP32 LittleFS.

---

## Installation

### I) For Arduino IDE

1. Be certain you have installed the most up to date version of Arduino IDE.
2. Be certain you have installed the most up-to-date Blynk library.
3. Using Arduino IDE, 
* either *use the zip file*
	 * **Navigate to the** [Blynk_WiFiManager](https://github.com/khoih-prog/Blynk_WM) page in Github.
	 * **Download the latest release** of `Blynk_WM-master.zip` and save to your hard drive.
	 * **Open Arduino IDE.**
	 * Menu: Sketch->Include Library->Add .ZIP library…
	 * Select the downloaded `Blynk_WM-master.zip` file
	 * Hit Open
  * Once Arduino IDE is finished installing the library, **EXIT Arduino IDE.**
	 
* or *use Arduino IDE's Library Manager*
	 * **Open Arduino IDE.**
  * Menu: Tools->**Manage Libraries…**
  * Wait for library list to populate.
  * Search for the keyword "Blynk". **Find Blynk_WiFiManager** in the library list.
  * Select the latest version of the Blynk_WiFiManager library.
  * Hit Install.
  * Once Arduino IDE is finished installing the library, **EXIT Arduino IDE.**

4. COPY the /certs files from the main Blynk library to the Blynk_WiFiManager library.	
   * **Find the `Blynk/src/certs` library directory.** (This is in the main Blynk library, may be named differently.)
   * **Find the `Blynk_WiFiManager/src/certs` library directory.** (This is in the installed Blynk_WiFiManager library, may be named differently.) Using Arduino IDE, these directories are normally found under .../Arduino/Sketchbook/libraries or .../Arduino/libraries. 
      * *(Sometimes Arduino IDE names a library folder with an unhelpful name like Arduino_12345. You can safely rename that folder under …/libraries/ to a compliant name like Blynk_WiFiManager for convenience. Remember to exit and restart IDE after renaming any library directory.)*
   * **COPY (do not cut and paste) the entire contents** of the `Blynk/src/certs` directory to the `Blynk_WiFiManager/src/certs` directory.
      * *(FYI: the reason for copying the certs from the Blynk library to Blynk_WiFiManager library is so that Blynk_WiFiManager will have access to Blynk's SSL certificates. And you almost certainly want to be using SSL!)*
  * **You must do Step 4 each time you update the Blynk_WiFiManager library** to keep those SSL certs accessible. 
   
5. **Open Arduino IDE.** Your library is installed.

### II) For VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Blynk_WiFiManager** library](https://platformio.org/lib/show/6925/Blynk_WiFiManager) by using [Library Manager](https://platformio.org/lib/show/6925/Blynk_WiFiManager/installation). Search for **Blynk_WiFiManager** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### How to use

In your code, replace
1. `BlynkSimpleEsp8266.h`     with `BlynkSimpleEsp8266_WM.h`      for ESP8266 `without SSL`
2. `BlynkSimpleEsp8266_SSL.h` with `BlynkSimpleEsp8266_SSL_WM.h`  for ESP8266 `with SSL`
3. `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WM.h`        for ESP32 `without SSL`
4. `BlynkSimpleEsp32_SSL.h`   with `BlynkSimpleEsp32_SSL_WM.h`    for ESP32 `with SSL`

5. For EP8266, add

```cpp
#define USE_LITTLEFS    true
#define USE_SPIFFS      false
```
to use LittleFS or

```cpp
#define USE_LITTLEFS    false
#define USE_SPIFFS      true
```

to use SPIFFS or

```cpp
#define USE_LITTLEFS    false
#define USE_SPIFFS      false
```
to use EEPROM.

6. For EP32, add

```cpp
#define USE_LITTLEFS          true
#define USE_SPIFFS            false
```

to use LittleFS or

```cpp
#define USE_LITTLEFS          false
#define USE_SPIFFS            true
```

to use SPIFFS or


```cpp
#define USE_LITTLEFS          false
#define USE_SPIFFS            false
```
to use EEPROM.

Currently, data size in v1.1.0, with DRD/MRD and not including dynamic params, is 380  bytes from address EEPROM_START ) to save your configuration data.

EEPROM_SIZE can be specified from 512 to 4096 (2048 for ESP32) bytes. 

See examples [ESP32WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP32WM_Config) and [ESP8266WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP8266WM_Config).

```cpp
// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
```

To use personalized Config Portal AP SSID and Password, as well as IP Address, channel e.g. call :

```cpp
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP8266", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 200, 1));
  // Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);
```

You can specify STA-mode Static IP address,  Gateway, Subnet Mask, as well as DNS server 1 and 2:

```cpp
  // From v1.0.5, select either one of these to set static IP
  Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
  //Blynk.setSTAStaticIPConfig(IPAddress(192, 168, 2, 220), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));
```

Then replace `Blynk.begin(...)` with :

1. `Blynk.begin()` to use default DHCP hostname `ESP8266-XXXXXX` or `ESP32-XXXXXX`

or to have a personalized hostname `(RFC952-conformed,- 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char)`

2. `Blynk.begin("Personalized-HostName")`

in your code. Keep `Blynk.run()` intact.

That's it.

---
---

### HOWTO Use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To load [Default Credentials](examples/ESP32WM_Config/Credentials.h)

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To use system default to load "blank" when there is no valid Credentials

```cpp
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/ESP32WM_Config/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
  // Defined in <BlynkSimpleEsp32_WM.h> and <BlynkSimpleEsp32_SSL_WM.h>

  #define SSID_MAX_LEN      32
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

  typedef struct Configuration
  {
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char board_name     [24];
  int  checkSum;
  } Blynk_WM_Configuration;

*/

bool LOAD_DEFAULT_CONFIG_DATA = true;
//bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WM_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL  
  "SSL",
#else
  "NonSSL",
#endif
  //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
  //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
  "SSID1", "password1",
  "SSID2", "password2",
  // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
  "account.ddns.net",     "token",
  "account.duckdns.org",  "token1", 
  //int  blynk_port;
#if USE_SSL
  9443,
#else
  8080,
#endif
  //char board_name     [24];
  "Air-Control",
  //int  checkSum, dummy, not used
  0
};

/////////// End Default Config Data /////////////
```

### 4. How to add dynamic parameters from sketch

- To add custom parameters, just modify the example below

```cpp
#define USE_DYNAMIC_PARAMETERS      true

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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

```
#### 5. If you don't need to add dynamic parameters

Use the following code snippet in sketch

```cpp
#define USE_DYNAMIC_PARAMETERS     false
```

or

```cpp
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```

---
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"sv"    for Blynk Server
"tk"    for Blynk Token
"sv1"   for Blynk Server1
"tk1"   for Blynk Token1
"pt"    for Blynk Port
"nm"    for Board Name
```

---

### Important notes

1. Now you can use special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords, BlynkServers and Tokens must be input (or to make them different from **nothing**). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.
4. Sometimes, it's hard or not possible to connect to Config Portal WiFi AP, the majority cases are caused by WiFi channel conflict if there are too many WiFi APs running around. Please use **random ConfigPortal WiFi AP channel** in sketch (see code snippet below) and reset the board so that another channel is used. Repeat until connection is OK

```cpp
// Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);
```

---
---

### Why using this [Blynk_WiFiManager](https://github.com/khoih-prog/Blynk_WM) with MultiWiFi-MultiBlynk features

You can see that the system **automatically detects and connects to the best or avaiable WiFi APs and/or Blynk Servers**, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, this `Blynk.begin()` is **not a blocking call**, so you can use it for critical functions requiring in loop().

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

---
---

### Examples

 1. [AM2315_ESP32_SSL](examples/AM2315_ESP32_SSL)
 2. [AM2315_ESP8266](examples/AM2315_ESP8266)
 3. [DHT11ESP32](examples/DHT11ESP32) 
 4. [DHT11ESP32_SSL](examples/DHT11ESP32_SSL) 
 5. [DHT11ESP8266](examples/DHT11ESP8266)
 6. [DHT11ESP8266_Debug](examples/DHT11ESP8266_Debug)
 7. [DHT11ESP8266_SSL](examples/DHT11ESP82662_SSL) 
 8. [ESP32WM_Config](examples/ESP32WM_Config)
 9. [ESP8266WM_Config](examples/ESP8266WM_Config)
10. [Blynk_WM_Template](examples/Blynk_WM_Template)
11. [**ESP32WM_MRD_Config**](examples/ESP32WM_MRD_Config)
12. [**ESP8266WM_MRD_Config**](examples/ESP8266WM_MRD_Config)

---
---

## So, how it works?

If it cannot connect to the Blynk server in 30 seconds, no valid stored Credentials or Double Reset is detected within 10s, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an AP with default name `ESP_xxxxxx` and password `MyESP_xxxxxx` or configurable name and password you specified. The AP IP address is default at `192.168.4.1` or configured IP (e.g. `192.168.200.1`).

First, connect your (PC, Laptop, Tablet, phone, etc.) WiFi to Config Portal AP, then enter the WiFi password :

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/PortalAuth.jpg">
</p>

1. If you choose **not to load** default Credentials and Dynamic Parameters

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The following Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Main.png">
</p>

2. If you choose **to load** default Credentials and Dynamic Parameters

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The following  Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Default_Main.png">
</p>

Enter your WiFi and Blynk Credentials:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/ConfigPortal.png">
</p>

Then click **Save**. The system will auto-restart. You will see the board's built-in LED turned OFF. That means, it's already connected to your Blynk server successfully.

---
---

## Example [ESP32WM_MRD_Config](examples/ESP32WM_MRD_Config)

#### 1. File [ESP32WM_MRD_Config.ino](examples/ESP32WM_MRD_Config/ESP32WM_MRD_Config.ino)

```
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#include <Ticker.h>
#include <DHT.h>

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

void heartBeatPrint(void)
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

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if (USE_LITTLEFS)
  Serial.print(F("\nStarting ESP32WM_MRD_Config using LITTLEFS"));
#elif (USE_SPIFFS)
  Serial.print(F("\nStarting ESP32WM_MRD_Config using SPIFFS"));  
#else
  Serial.print(F("\nStarting ESP32WM_MRD_Config using EEPROM"));
#endif

#if USE_SSL
  Serial.print(F(" with SSL on ")); Serial.println(ARDUINO_BOARD);
#else
  Serial.print(F(" without SSL on ")); Serial.println(ARDUINO_BOARD);
#endif

  Serial.println(BLYNK_WM_VERSION);

#if USING_MRD
  Serial.println(ESP_MULTI_RESET_DETECTOR_VERSION);
#else
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);
#endif  

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
void displayCredentials(void)
{
  Serial.println(F("\nYour stored Credentials :"));

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

#if USE_DYNAMIC_PARAMETERS
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
```

#### 2. File [defines.h](examples/ESP32WM_MRD_Config/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#ifndef ESP32
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT        Serial

#define BLYNK_WM_DEBUG     3

#define USING_MRD           true

#if USING_MRD
  // These definitions must be placed before #include <ESP_MultiResetDetector.h> to be used
  // Otherwise, default values (MRD_TIMES = 3, MRD_TIMEOUT = 10 seconds and MRD_ADDRESS = 0) will be used
  // Number of subsequent resets during MRD_TIMEOUT to activate
  #define MRD_TIMES               3
  
  // Number of seconds after reset during which a subseqent reset will be considered a mlti reset.
  #define MRD_TIMEOUT             10
  
  // RTC/EEPPROM Address for the MultiResetDetector to use
  #define MRD_ADDRESS             0

  #define MULTIRESETDETECTOR_DEBUG       true 
  
  #warning Using MultiResetDetector MRD
#else
  // These definitions must be placed before #include <ESP_DoubleResetDetector.h> to be used
  // Otherwise, default values (DRD_TIMEOUT = 10 seconds and DRD_ADDRESS = 0) will be used
  // Number of subsequent resets during DRD_TIMEOUT to activate
  
  // Number of seconds after reset during which a subseqent reset will be considered a mlti reset.
  #define DRD_TIMEOUT             10

// RTC/EEPPROM Address for the DoubleResetDetector to use
  #define DRD_ADDRESS             0

  #define DOUBLERESETDETECTOR_DEBUG     false
  
  #warning Using DoubleResetDetector DRD 
#endif

// Not use #define USE_LITTLEFS and #define USE_SPIFFS  => using SPIFFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == false)    => using EEPROM for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == false)     => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == true) and (USE_SPIFFS == true)      => using LITTLEFS for configuration data in WiFiManager
// (USE_LITTLEFS == false) and (USE_SPIFFS == true)     => using SPIFFS for configuration data in WiFiManager
// Those above #define's must be placed before #include <BlynkSimpleEsp32_WFM.h>

#define USE_LITTLEFS          true
#define USE_SPIFFS            false

#if !( USE_SPIFFS || USE_LITTLEFS)
  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
// Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h>

//#define USE_SSL   true
#define USE_SSL   false

#if USE_SSL
#include <BlynkSimpleEsp32_SSL_WM.h>
#else
#include <BlynkSimpleEsp32_WM.h>
#endif

#define PIN_D22   22            // Pin D22 mapped to pin GPIO22/SCL of ESP32

#define DHT_PIN     PIN_D22     // pin DATA @ D22 / GPIO22
#define DHT_TYPE    DHT11

#define HOST_NAME   "ESP32-Master-Controller"

#endif      //defines_h
```

---

#### 3. File [Credentials.h](examples/ESP32WM_MRD_Config/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

/// Start Default Config Data //////////////////

/*
  // Defined in <BlynkSimpleEsp32_WM.h> and <BlynkSimpleEsp32_SSL_WM.h>

  #define SSID_MAX_LEN      32
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

  typedef struct Configuration
  {
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char board_name     [24];
  int  checkSum;
  } Blynk_WM_Configuration;

*/

//bool LOAD_DEFAULT_CONFIG_DATA = true;
bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_WM_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL  
  "SSL",
#else
  "NonSSL",
#endif
  //WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS]
  //WiFi_Creds.wifi_ssid and WiFi_Creds.wifi_pw
  "SSID1", "password1",
  "SSID2", "password2",
  // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
  "account.ddns.net",     "token",
  "account.duckdns.org",  "token1", 
  //int  blynk_port;
#if USE_SSL
  9443,
#else
  8080,
#endif
  //char board_name     [24];
  "Air-Control",
  //int  checkSum, dummy, not used
  0
};

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```

---

#### 4. File [dynamicParams.h](examples/ESP32WM_MRD_Config/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#define USE_DYNAMIC_PARAMETERS      true

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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

#endif      //dynamicParams_h
```

---
---


### Debug Terminal Output Samples

#### 1. ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU

The following is the sample terminal output when running example [ESP8266WM_MRD_Config](examples/ESP8266WM_MRD_Config) on **ESP8266_NODEMCU**

#### 1.1 No MultiReset Detected => Running normally


```
Starting ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM v1.1.0
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFD0002
multiResetDetectorFlag = 0xFFFD0002
lowerBytes = 0x0002, upperBytes = 0x0002
No multiResetDetected, number of times = 2
LittleFS Flag read = 0xFFFD0002
Saving config file...
Saving config file OK
[310] Hostname=8266-Master-Controller
[335] LoadCfgFile 
[336] OK
[336] ======= Start Stored Config Data =======
[336] Hdr=SSL_ESP8266,BrdName=Air-Control
[336] SSID=HueNet1,PW=12345678
[338] SSID1=HueNet2,PW1=12345678
[341] Server=account.duckdns.org,Token=token1
[347] Server1=account.duckdns.org,Token1=token2
[353] Port=9443
[355] ======= End Config Data =======
[358] CCSum=0x36c8,RCSum=0x36c8
[365] LoadCredFile 
[365] CrR:pdata=new-mqtt-server,len=34
[366] CrR:pdata=1883,len=6
[369] CrR:pdata=new-mqtt-username,len=34
[372] CrR:pdata=default-mqtt-password,len=34
[376] CrR:pdata=default-mqtt-SubTopic,len=34
[380] CrR:pdata=default-mqtt-PubTopic,len=34
[384] OK
[385] CrCCsum=0x2670,CrRCsum=0x2670
[388] Valid Stored Dynamic Data
[391] Hdr=SSL_ESP8266,BrdName=Air-Control
[395] SSID=HueNet1,PW=12345678
[398] SSID1=HueNet2,PW1=12345678
[401] Server=account.duckdns.org,Token=token1
[407] Server1=account.duckdns.org,Token1=token2
[413] Port=9443
[415] ======= End Config Data =======
[418] bg: noConfigPortal = true
[421] Connecting MultiWifi...
[6699] WiFi connected after time: 1
[6699] SSID: HueNet1, RSSI = -37
[6700] Channel: 2, IP address: 192.168.2.166
[6700] bg: WiFi OK. Try Blynk
[6701] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[22723] NTP time: Fri Jan  1 22:15:49 2021
[22724] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[23520] Certificate OK
[23528] Ready (ping: 4ms).
[23601] Connected to Blynk Server = account.duckdns.org, Token = token1
[23601] bg: WiFi+Blynk OK

Blynk ESP8288 using LittleFS connected.
Board Name : Air-Control
Stop multiResetDetecting
Saving config file...
Saving config file OK
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
BBBBBB
```


#### 1.2 MultiReset Detected => Enter Config Portal


```
Starting ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM v1.1.0
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFC0003
multiResetDetectorFlag = 0xFFFC0003
lowerBytes = 0x0003, upperBytes = 0x0003
multiResetDetected, number of times = 3
Saving config file...
Saving config file OK
[299] Multi or Double Reset Detected
[299] Hostname=8266-Master-Controller
[328] LoadCfgFile 
[328] OK
[328] ======= Start Stored Config Data =======
[328] Hdr=SSL_ESP8266,BrdName=Air-Control
[328] SSID=HueNet1,PW=12345678
[330] SSID1=HueNet2,PW1=12345678
[333] Server=account.duckdns.org,Token=token1
[339] Server1=account.duckdns.org,Token1=token2
[346] Port=9443
[347] ======= End Config Data =======
[351] CCSum=0x36c8,RCSum=0x36c8
[358] LoadCredFile 
[358] CrR:pdata=new-mqtt-server,len=34
[359] CrR:pdata=1883,len=6
[361] CrR:pdata=new-mqtt-username,len=34
[365] CrR:pdata=default-mqtt-password,len=34
[369] CrR:pdata=default-mqtt-SubTopic,len=34
[373] CrR:pdata=default-mqtt-PubTopic,len=34
[377] OK
[378] CrCCsum=0x2670,CrRCsum=0x2670
[381] Valid Stored Dynamic Data
[384] Hdr=SSL_ESP8266,BrdName=Air-Control
[387] SSID=HueNet1,PW=12345678
[390] SSID1=HueNet2,PW1=12345678
[393] Server=account.duckdns.org,Token=token1
[399] Server1=account.duckdns.org,Token1=token2
[406] Port=9443
[407] ======= End Config Data =======
[411] bg: Stay forever in config portal.DRD/MRD detected
[2473] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[2473] IP=192.168.200.1,ch=5
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
FFFFFRFFFF FFRF
```

---

#### 2. DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU

The following is the sample terminal output when running example [DHT11ESP8266_SSL](examples/DHT11ESP8266_SSL) on **ESP8266_NODEMCU**


```
Starting DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM v1.1.0
ESP_DoubleResetDetector v1.1.1
[293] Hostname=ESP8266-DHT11-SSL
[316] LoadCfgFile 
[316] OK
[316] CCSum=0x36c8,RCSum=0x36c8
[320] LoadCredFile 
[320] OK
[320] CrCCsum=0x2670,CrRCsum=0x2670
[320] Hdr=SSL_ESP8266,BrdName=Air-Control
[320] SSID=HueNet1,PW=12345678
[322] SSID1=HueNet2,PW1=12345678
[325] Server=account.duckdns.org,Token=token1
[331] Server1=account.duckdns.org,12345678=token2
[338] Port=9443
[339] ======= End Config Data =======
[343] Connecting MultiWifi...
[6619] WiFi connected after time: 1
[6620] SSID: HueNet1, RSSI = -32
[6620] Channel: 2, IP address: 192.168.2.166
[6620] bg: WiFi OK. Try Blynk
[6621] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[22644] NTP time: Fri Jan  1 21:13:34 2021
[22645] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[23405] Certificate OK
[23411] Ready (ping: 2ms).
[23485] Connected to Blynk Server = account.duckdns.org, Token = token1
[23485] bg: WiFi+Blynk OK

Blynk ESP8288 using LittleFS connected.
Board Name : Air-Control
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
```

---

#### 3. ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV

The following is the sample terminal output when running example [ESP32WM_MRD_Config](examples/ESP32WM_MRD_Config) on **ESP32_DEV**

#### 3.1 No MultiReset Detected => Running normally


```
Starting ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV
Blynk_WM v1.1.0
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[498] Hostname=ESP32-Master-Controller
[516] LoadCfgFile 
[518] OK
[518] ======= Start Stored Config Data =======
[518] Hdr=ESP32,BrdName=ESP32_MRD
[518] SSID=HueNet1,PW=12345678
[518] SSID1=HueNet2,PW1=12345678
[523] Server=account.duckdns.org,Token=token1
[529] Server1=account.duckdns.org,Token1=token2
[535] Port=9443
[537] ======= End Config Data =======
[540] CCSum=0x336b,RCSum=0x336b
[555] LoadCredFile 
[559] CrR:pdata=default-mqtt-server,len=34
[559] CrR:pdata=1883,len=6
[559] CrR:pdata=default-mqtt-username,len=34
[559] CrR:pdata=default-mqtt-password,len=34
[563] CrR:pdata=default-mqtt-SubTopic,len=34
[567] CrR:pdata=default-mqtt-PubTopic,len=34
[571] OK
[572] CrCCsum=0x29a6,CrRCsum=0x29a6
[575] Valid Stored Dynamic Data
[578] Hdr=ESP32,BrdName=ESP32_MRD
[581] SSID=HueNet1,PW=12345678
[584] SSID1=HueNet2,PW1=12345678
[587] Server=account.duckdns.org,Token=token1
[593] Server1=account.duckdns.org,Token1=token2
[600] Port=9443
[601] ======= End Config Data =======
[604] bg: noConfigPortal = true
[607] Connecting MultiWifi...
[6439] WiFi connected after time: 1
[6439] SSID:HueNet1,RSSI=-25
[6439] Channel:2,IP address:192.168.2.101
[6439] bg: WiFi OK. Try Blynk
[6440] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[6453] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6587] Ready (ping: 8ms).
[6655] Connected to Blynk Server = account.duckdns.org, Token = token1
[6655] bg: WiFi+Blynk OK

Blynk ESP32 using LittleFS connected
Board Name : ESP32_MRD
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK
BBBBBB
```

#### 3.2 MultiReset Detected => Enter Config Portal


```
Starting ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV
Blynk_WM v1.1.0
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFC0003
multiResetDetectorFlag = 0xFFFC0003
lowerBytes = 0x0003, upperBytes = 0x0003
multiResetDetected, number of times = 3
Saving config file...
Saving config file OK
[280] Multi or Double Reset Detected
[352] Hostname=ESP32-Master-Controller
[391] LoadCfgFile 
[396] OK
[396] ======= Start Stored Config Data =======
[397] Hdr=ESP32,BrdName=ESP32_MRD
[397] SSID=HueNet1,PW=12345678
[397] SSID1=HueNet2,PW1=12345678
[399] Server=account.duckdns.org,Token=token1
[405] Server1=account.duckdns.org,Token1=token2
[412] Port=9443
[413] ======= End Config Data =======
[416] CCSum=0x336b,RCSum=0x336b
[433] LoadCredFile 
[438] CrR:pdata=default-mqtt-server,len=34
[438] CrR:pdata=1883,len=6
[438] CrR:pdata=default-mqtt-username,len=34
[438] CrR:pdata=default-mqtt-password,len=34
[441] CrR:pdata=default-mqtt-SubTopic,len=34
[445] CrR:pdata=default-mqtt-PubTopic,len=34
[449] OK
[450] CrCCsum=0x29a6,CrRCsum=0x29a6
[453] Valid Stored Dynamic Data
[456] Hdr=ESP32,BrdName=ESP32_MRD
[459] SSID=HueNet1,PW=12345678
[462] SSID1=HueNet2,PW1=12345678
[465] Server=account.duckdns.org,Token=token1
[471] Server1=account.duckdns.org,Token1=token2
[477] Port=9443
[479] ======= End Config Data =======
[482] bg: Stay forever in config portal.DRD/MRD detected
[1332] 
stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[1332] IP=192.168.220.1,ch=10
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
ets Jun  8 2016 00:22:57
```

#### 3.3 Exit Config Portal with Data


```
Starting ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV
Blynk_WM v1.1.0
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[498] Hostname=ESP32-Master-Controller
[516] LoadCfgFile 
[518] OK
[518] ======= Start Stored Config Data =======
[518] Hdr=ESP32,BrdName=ESP32_MRD
[518] SSID=HueNet1,PW=12345678
[518] SSID1=HueNet2,PW1=12345678
[523] Server=account.duckdns.org,Token=token1
[529] Server1=account.duckdns.org,Token1=token2
[535] Port=9443
[537] ======= End Config Data =======
[540] CCSum=0x336b,RCSum=0x336b
[555] LoadCredFile 
[559] CrR:pdata=default-mqtt-server,len=34
[559] CrR:pdata=1883,len=6
[559] CrR:pdata=default-mqtt-username,len=34
[559] CrR:pdata=default-mqtt-password,len=34
[563] CrR:pdata=default-mqtt-SubTopic,len=34
[567] CrR:pdata=default-mqtt-PubTopic,len=34
[571] OK
[572] CrCCsum=0x29a6,CrRCsum=0x29a6
[575] Valid Stored Dynamic Data
[578] Hdr=ESP32,BrdName=ESP32_MRD
[581] SSID=HueNet1,PW=12345678
[584] SSID1=HueNet2,PW1=12345678
[587] Server=account.duckdns.org,Token=token1
[593] Server1=account.duckdns.org,Token1=token2
[600] Port=9443
[601] ======= End Config Data =======
[604] bg: noConfigPortal = true
[607] Connecting MultiWifi...
[6439] WiFi connected after time: 1
[6439] SSID:HueNet1,RSSI=-25
[6439] Channel:2,IP address:192.168.2.101
[6439] bg: WiFi OK. Try Blynk
[6440] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[6453] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6587] Ready (ping: 8ms).
[6655] Connected to Blynk Server = account.duckdns.org, Token = token1
[6655] bg: WiFi+Blynk OK

Blynk ESP32 using LittleFS connected
Board Name : ESP32_MRD
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK
RBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB
RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRB
```

#### 3.4 WiFi Lost => AutoReconnect WiFi and Blynk

```
[3977051] run: WiFi lost. Reconnect WiFi+Blynk
[3977051] Connecting MultiWifi...
[3984620] WiFi connected after time: 2
[3984620] SSID:HueNet2,RSSI=-53
[3984620] Channel:4,IP address:192.168.2.101
[3984620] run: WiFi reconnected. Connect to Blynk
[3984623] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[3984637] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[3984791] Ready (ping: 6ms).
[3984859] Connected to Blynk Server = account.duckdns.org, Token = token1
[3984859] run: WiFi+Blynk reconnected
RBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB
RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRBRBRBRB RBRBRBRBRBRBRB
[3977051] run: WiFi lost. Reconnect WiFi+Blynk
[3977051] Connecting MultiWifi...
[3984620] WiFi connected after time: 2
[3984620] SSID:HueNet2,RSSI=-53
[3984620] Channel:4,IP address:192.168.2.101
[3984620] run: WiFi reconnected. Connect to Blynk
[3984623] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[3984637] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[3984791] Ready (ping: 6ms).
[3984859] Connected to Blynk Server = account.duckdns.org, Token = token1
[3984859] run: WiFi+Blynk reconnected

```

---

#### 4. DHT11ESP32_SSL using LITTLEFS with SSL on ESP32_DEV

The following is the sample terminal output when running example [DHT11ESP8266_SSL](examples/DHT11ESP8266_SSL) on **ESP8266_NODEMCU**


```
Starting DHT11ESP32_SSL using LITTLEFS with SSL on ESP32_DEV
Blynk_WM v1.1.0
ESP_DoubleResetDetector v1.1.1
[346] Hostname=ESP32-DHT11-SSL
[385] LoadCfgFile 
[391] OK
[391] CCSum=0x3657,RCSum=0x3657
[407] LoadCredFile 
[412] OK
[412] CrCCsum=0x2670,CrRCsum=0x2670
[413] Hdr=SSL_ESP32,BrdName=Air-Control
[413] SSID=HueNet1,PW=12345678
[413] SSID1=HueNet2,PW1=12345678
[415] Server=account.duckdns.org,Token=token1
[421] Server1=account.duckdns.org,12345678=token2
[427] Port=9443
[429] ======= End Config Data =======
[432] Connecting MultiWifi...
[6349] WiFi connected after time: 1
[6349] SSID: HueNet1, RSSI = -27
[6349] Channel: 2, IP address: 192.168.2.101
[6349] bg: WiFi OK. Try Blynk
[6351] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[7364] NTP time: Fri Jan  1 21:14:44 2021
[7364] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[9152] Certificate OK
[9160] Ready (ping: 7ms).
[9229] Connected to Blynk Server = account.duckdns.org, Token = token1
[9229] bg: WiFi+Blynk OK

Blynk ESP32 using LittleFS connected
Board Name : Air-Control
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
```

---
---


### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define BLYNK_PRINT        Serial

#define BLYNK_WM_DEBUG     3

#define USING_MRD          true

#if USING_MRD
  #define MULTIRESETDETECTOR_DEBUG       true 
#else
  #define DOUBLERESETDETECTOR_DEBUG     false
#endif
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

## Releases

### Major Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library
2. Add support to MultiDetectDetector. **MultiDetectDetector** feature to force Config Portal when configurable multi-reset is detected within predetermined time.
3. Clean-up all compiler warnings possible.
4. Add Table of Contents
5. Add Version String
6. Add MRD-related examples.

### Releases v1.0.16

1. Fix bug and logic of USE_DEFAULT_CONFIG_DATA.
2. Auto format SPIFFS/LittleFS for first time usage.

#### Releases v1.0.15

1. Update to use LittleFS for ESP8266 core 2.7.1+.
2. Fix SSL connection bug.
3. Fix dynamicParams loading bug in v1.0.14. 
4. Add [Blynk_WM_Template example](examples/Blynk_WM_Template) contributed by [Thor Johnson](https://github.com/thorathome).

Again thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome) for testing, bug finding, feature adding, README rewriting, collaborating, etc..

#### Releases v1.0.14

1. Fix dynamicParams bug in v1.0.13. Again thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome)

#### Releases v1.0.13

1. Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
2. **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
3. Configurable **Config Portal Title** to be either Hostname, BoardName or default undistinguishable names.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

#### Releases v1.0.12

1. Fix severe bug in v1.0.11

#### Releases v1.0.11

**Severe connecting bug. Don't use**

1. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved **automatically in EEPROM, or SPIFFS**.

#### Releases v1.0.10

**Why this version**

1. WiFi Password max length is 63, according to WPA2 standard.
2. Permit to input special chars such as **~, !, @, #, $, %, ^, &, *, (, ), _, -, space,etc"** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

#### Releases v1.0.9

1. Enhance Config Portal GUI. Not using the terrible GUI of the original version. Finally had some time to get this out of the bucket list.

#### Releases v1.0.8

1. Fix [AP-staying-open bug](https://github.com/khoih-prog/Blynk_WM/issues/2). Thanks to [chriskio](https://github.com/chriskio) to report.
2. Add clearConfigData().

#### Releases v1.0.7

**Why this version**

1. Add checksum for more reliable data
2. Add MultiWiFi feature to enable reconnect to the best / available WiFi AP.
3. Add MultiBlynk feature to enable reconnect to the best / available Blynk Server.

#### Releases v1.0.6

Optimize, fix ESP32 EEPROM size to 2K from 4K, shorten code size, add functions, use dynamically allocated Config Portal WebServer.

#### Releases v1.0.5

Normally, the `default Portal IP (192.168.4.1)`, SSID and PW as well as the `dynamically allocated` board's IP address are good enough.
In special cases where there is conflict, if static IP is required or bad router's DNS settings, you can use the new features to force the configurable IP addresses. **But please use with care to avoid potential issues.**

**New in this version**

Add new features to enable :

1. configuring Portal Static IP address, Name and Password.
2. configuring Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.

#### Releases v1.0.4

I'm really fed-up with the unfriendly, confusing and cryptic DHCP hostnames such as `ESP_XXXXXX`, `espressif` using ChipID. Thanks to an issue opened in library [ESP_WiFiManager](https://github.com/khoih-prog/ESP_WiFiManager), I decided to add this option to have built-in, yet configurable DHCP hostname to these libraries.

Now you can easily specify and have the friendly, identifiable, RFC-952-conformed DHCP hostnames associated with your boards, such as `SmartFarm-1`, `Irrigation`, `Master-Controller`, etc. You'll be happier to have a look at your WiFi Router DHCP list.

**New in this version**

1. Add configurable personalized RFC-952 DHCP hostname and setHostname()

2. Modify examples to use new feature

#### Releases v1.0.3

1. Modify code to be compatible with ESP8266 core pre-2.5.2. But it's still advisable to update to the latest stable core, such as 2.6.3

2. Add examples

#### Releases v1.0.2

**Features**

1. This release of very-easy-to-use will help you to eliminate hardcoding your Wifi and Blynk credentials for ESP8266 and ESP32 (with / without SSL), and updating/reflashing every time when you need to change them.

2. Configuration data are stored in either SPIFFS or EEPROM.

3. When WiFi and/or Blynk connection is lost, the WM will try auto-reconnect.

**New in this version**

1. Fix bug

2. If the config data not entered completely (SSID, password, Server and Blynk token), entering config portal

3. Correct the operation of BUILTIN_LED

---

### Issues ###

Submit issues to: [Blynk_WM issues](https://github.com/khoih-prog/Blynk_WM/issues)

---
---

## TO DO

1. Fix bug. Add enhancement


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
10. Add checksum for more reliable data
11. Add MultiWiFi feature to enable reconnect to the best / available WiFi AP.
12. Add MultiBlynk feature to enable reconnect to the best / available Blynk Server.
13. WiFi Password max length is 63, as in WPA2 standards
14. Permit to input special chars such as **%** and **#** into data fields.
15. Add Dynamic Parameters with checksum
16. Default Credentials and dynamic parameters
17. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
18. Configurable Config Portal Title
19. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
20. Add **LittleFS** support to ESP8266 as SPIFFS deprecated since **ESP8266 core 2.7.1.**
21. Add **LittleFS** support to ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library.\
22. Add support to MultiDetectDetector and MRD-related examples
23. Clean-up all compiler warnings possible.
24. Add Table of Contents
25. Add Version String

---
---

### Contributions and thanks

1. Thanks to [chriskio](https://github.com/chriskio) to report [AP-staying-open bug](https://github.com/khoih-prog/Blynk_WM/issues/2). 
2. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
3. Thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome) to test, find bug, suggest and encourage to add those new features in v1.0.13, such as Default Credentials/Dynamic Parms, Configurable Config Portal Title, DRD. The powerful [Blynk_WM_Template](examples/Blynk_WM_Template) is written by [Thor Johnson](https://github.com/thorathome) and is included in the examples with his permission. See [WM Config Portal using BlynkSimpleEsp32/8266_WM.h](https://community.blynk.cc/t/wm-config-portal-using-blynksimpleesp32-8266-wm-h/45402).
4. Thanks to [Thor Johnson](https://github.com/thorathome) and [kevinleberge](https://github.com/kevinleberge) to help locate the bugs, discuss the USE_DEFAULT_CONFIG_DATA solution leading to release v1.0.16. See [Can’t load defaults](https://github.com/khoih-prog/Blynk_WM/issues/15) and [Setting "#define USE_DYNAMIC_PARAMETERS false" on Blynk_WM_Template.ino results in compile error](https://github.com/khoih-prog/Blynk_WM/issues/16)

<table>
  <tr>
    <td align="center"><a href="https://github.com/chriskio"><img src="https://github.com/chriskio.png" width="100px;" alt="chriskio"/><br /><sub><b>chriskio</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/brondolin"><img src="https://github.com/brondolin.png" width="100px;" alt="brondolin"/><br /><sub><b>brondolin</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/thorathome"><img src="https://github.com/thorathome.png" width="100px;" alt="thorathome"/><br /><sub><b>Thor Johnson</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kevinleberge"><img src="https://github.com/kevinleberge.png" width="100px;" alt="kevinleberge"/><br /><sub><b>kevinleberge</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Blynk_WM/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang

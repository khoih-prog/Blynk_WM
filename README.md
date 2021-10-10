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
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [I) For Arduino IDE](#i-for-arduino-ide)
  * [II) For VS Code & PlatformIO:](#ii-for-vs-code--platformio)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
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
  * [ 6. To use custom HTML Style](#6-to-use-custom-html-style)
  * [ 7. To use custom Head Elements](#7-to-use-custom-head-elements)
  * [ 8. To use CORS Header](#8-to-use-cors-header)
  * [ 9. To use and input only one set of WiFi SSID and PWD](#9-to-use-and-input-only-one-set-of-wifi-ssid-and-pwd)
    * [ 9.1 If you need to use and input only one set of WiFi SSID/PWD](#91-if-you-need-to-use-and-input-only-one-set-of-wifi-ssidpwd)
    * [ 9.2 If you need to use both sets of WiFi SSID/PWD](#92-if-you-need-to-use-both-sets-of-wifi-ssidpwd)
  * [10. To enable auto-scan of WiFi networks for selection in Configuration Portal](#10-to-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [10.1 Enable auto-scan of WiFi networks for selection in Configuration Portal](#101-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [10.2 Disable manually input SSIDs](#102-disable-manually-input-ssids)
    * [10.3 Select maximum number of SSIDs in the list](#103-select-maximum-number-of-ssids-in-the-list)
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
  * [13. **ESP32WM_ForcedConfig**](examples/ESP32WM_ForcedConfig)
  * [14. **ESP8266WM_ForcedConfig**](examples/ESP8266WM_ForcedConfig)
  * [15. **ESP32WM_MRD_ForcedConfig**](examples/ESP32WM_MRD_ForcedConfig)
  * [16. **ESP8266WM_MRD_ForcedConfig**](examples/ESP8266WM_MRD_ForcedConfig)
* [So, how it works?](#so-how-it-works)
  * [ 1. Without SCAN_WIFI_NETWORKS](#1-without-scan_wifi_networks)
  * [ 2. With SCAN_WIFI_NETWORKS](#2-with-scan_wifi_networks)
* [Example ESP32WM_MRD_ForcedConfig](#example-esp32wm_mrd_forcedconfig)
  * [1. File ESP32WM_MRD_ForcedConfig.ino](#1-file-esp32wm_mrd_forcedconfigino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU](#1-esp8266wm_mrd_config-using-littlefs-with-ssl-on-esp8266_nodemcu)
    * [1.1. No MultiReset Detected => Running normally](#11-no-multireset-detected--running-normally)
    * [1.2. MultiReset Detected => Enter Config Portal](#12-multireset-detected--enter-config-portal)
  * [2. DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU](#2-dht11esp8266_ssl-using-littlefs-with-ssl-on-esp8266_nodemcu)
  * [3. ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV](#3-esp32wm_mrd_config-using-littlefs-without-ssl-on-esp32_dev)
    * [3.1. No MultiReset Detected => Running normally](#31-no-multireset-detected--running-normally)
    * [3.2. MultiReset Detected => Enter Config Portal](#32-multireset-detected--enter-config-portal)
    * [3.3. Exit Config Portal with Data](#33-exit-config-portal-with-data)
    * [3.4. WiFi Lost => AutoReconnect WiFi and Blynk.](#34-wifi-lost--autoreconnect-wifi-and-blynk)
  * [4. DHT11ESP32_SSL using LittleFS with SSL on ESP32_DEV](#4-dht11esp32_ssl-using-littlefs-with-ssl-on-esp32_dev)
  * [5. ESP8266WM_MRD_ForcedConfig using non-persistent ConfigPortal virtual button](#5-esp8266wm_mrd_forcedconfig-using-non-persistent-configportal-virtual-button)
    * [5.1. Start normally then press non-persistent ConfigPortal virtual button](#51-start-normally-then-press-non-persistent-configportal-virtual-button)
    * [5.2. Enter non-persistent ConfigPortal](#52-enter-non-persistent-configportal)
  * [6. ESP8266WM_MRD_ForcedConfig using persistent ConfigPortal virtual button](#6-esp8266wm_mrd_forcedconfig-using-persistent-configportal-virtual-button)
    * [6.1. Start normally then press persistent ConfigPortal virtual button](#61-start-normally-then-press-persistent-configportal-virtual-button)
    * [6.2. Enter persistent ConfigPortal](#62-enter-persistent-configportal)
  * [7. ESP8266WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP8266_NODEMCU](#7-esp8266wm_mrd_forcedconfig-using-littlefs-with-ssl-on-esp8266_nodemcu)
  * [8. ESP32WM_MRD_Config using LITTLEFS with SSL on ESP32S2_DEV](#8-esp32wm_mrd_config-using-littlefs-with-ssl-on-esp32s2_dev)
  * [9. ESP32WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP32_DEV to demo WiFi Scan](#9-esp32wm_mrd_forcedconfig-using-littlefs-with-ssl-on-esp32_dev-to-demo-wifi-scan)
    * [9.1 MRD/DRD => Open Config Portal](#91-mrddrd--open-config-portal)
    * [9.2 Config Data Saved => Connection to Blynk](#92-config-data-saved--connection-to-blynk)
  * [10. ESP8266WM_MRD_Config using LITTLEFS with SSL on ESP8266_NODEMCU_ESP12E using new ESP8266 core v3.0.2](#10-esp8266wm_mrd_config-using-littlefs-with-ssl-on-esp8266_nodemcu_esp12e-using-new-esp8266-core-v302)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
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

With version `v1.6.0` or later, you can use:

1. `New ESP8266 core v3.0.0+`

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

This [**Blynk_WM** library](https://github.com/khoih-prog/Blynk_WM) currently supports these following boards:

 1. **ESP8266 and ESP32-based boards using EEPROM, SPIFFS or LittleFS**.
 2. **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using EEPROM, SPIFFS or LittleFS**.
 3. **ESP32-C3 (ARDUINO_ESP32C3_DEV) using EEPROM or SPIFFS**.


---
---


## Prerequisites

1. [`Arduino IDE 1.8.16+`](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 1.0.1+`](https://github.com/blynkkk/blynk-library/releases). [![Latest release](https://img.shields.io/github/release/blynkkk/blynk-library.svg)](https://github.com/blynkkk/blynk-library/releases/latest/). Never use the `Blynk beta` versions.
3. [`ESP32 Core 2.0.0+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
4. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS. 
5. [`ESP_DoubleResetDetector library 1.1.1+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to use DRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).
6. [`ESP_MultiResetDetector library 1.1.1+`](https://github.com/khoih-prog/ESP_MultiResetDetector) to use MRD feature. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_MultiResetDetector.svg?)](https://www.ardu-badge.com/ESP_MultiResetDetector).
7. [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32). **Notice**: This [`LittleFS_esp32 library`](https://github.com/lorol/LITTLEFS) has been integrated to Arduino [esp32 core v1.0.6+](https://github.com/espressif/arduino-esp32/tree/master/libraries/LITTLEFS).

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
3. Install [**Blynk_WM** library](https://platformio.org/lib/show/11638/Blynk_WM) by using [Library Manager](https://platformio.org/lib/show/11638/Blynk_WiFiManager/installation). Search for **Blynk_WM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---


### Note for Platform IO using ESP32 LittleFS

#### Necessary only for esp32 core v1.0.6-

From esp32 core v1.0.6+, [`LittleFS_esp32 v1.0.6`](https://github.com/lorol/LITTLEFS) has been included and this step is not necessary anymore.

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

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

#### 6. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

Blynk.setCustomsStyle(NewCustomsStyle);
```

#### 7. To use custom Head Elements


```
Blynk.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 8. To use CORS Header

```
Blynk.setCORSHeader("Your Access-Control-Allow-Origin");
```


#### 9. To use and input only one set of WiFi SSID and PWD

#### 9.1 If you need to use and input only one set of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       true
```
But it's always advisable to use and input both sets for reliability.
 
#### 9.2 If you need to use both sets of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false
```

#### 10. To enable auto-scan of WiFi networks for selection in Configuration Portal

#### 10.1 Enable auto-scan of WiFi networks for selection in Configuration Portal


```
#define SCAN_WIFI_NETWORKS                  true
```

The manual input of SSIDs is default enabled, so that users can input arbitrary SSID, not only from the scanned list. This is for the sample use-cases in which users can input the known SSIDs of another place, then send the boards to that place. The boards can connect to WiFi without users entering Config Portal to re-configure.

#### 10.2 Disable manually input SSIDs

```
// To disable manually input SSID, only from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           false
```

This is for normal use-cases in which users can only select an SSID from a scanned list of SSIDs to avoid typo mistakes and/or security.

#### 10.3 Select maximum number of SSIDs in the list

The maximum number of SSIDs in the list is seletable from 2 to 15. If invalid number of SSIDs is selected, the default number of 10 will be used.


```
// From 2-15
#define MAX_SSID_IN_LIST                    8
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
13. [**ESP32WM_ForcedConfig**](examples/ESP32WM_ForcedConfig)
14. [**ESP8266WM_ForcedConfig**](examples/ESP8266WM_ForcedConfig)
15. [**ESP32WM_MRD_ForcedConfig**](examples/ESP32WM_MRD_ForcedConfig)
16. [**ESP8266WM_MRD_ForcedConfig**](examples/ESP8266WM_MRD_ForcedConfig)

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

### 1. Without SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/ConfigPortal.png">
</p>


### 2. With SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Input_With_Scan.png">
</p>


Then click **Save**. The system will auto-restart. You will see the board's built-in LED turned OFF. That means, it's already connected to your Blynk server successfully.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Saved.png">
</p>

---
---

## Example [ESP32WM_MRD_ForcedConfig](examples/ESP32WM_MRD_ForcedConfig)

#### 1. File [ESP32WM_MRD_ForcedConfig.ino](examples/ESP32WM_MRD_ForcedConfig/ESP32WM_MRD_ForcedConfig.ino)

```
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#include <Ticker.h>
#include <DHT.h>        // https://github.com/adafruit/DHT-sensor-library

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;
Ticker     led_ticker;

#define BLYNK_PIN_FORCED_CONFIG           V10
#define BLYNK_PIN_FORCED_PERS_CONFIG      V20

// Use button V10 (BLYNK_PIN_FORCED_CONFIG) to forced Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nCP Button Hit. Rebooting") ); 

    // This will keep CP once, clear after reset, even you didn't enter CP at all.
    Blynk.resetAndEnterConfigPortal(); 
    
    delay ( 8000 );  
    ESP.restart();
  }
}

// Use button V20 (BLYNK_PIN_FORCED_PERS_CONFIG) to forced Persistent Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_PERS_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nPersistent CP Button Hit. Rebooting") ); 
   
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    Blynk.resetAndEnterConfigPortalPersistent();
    
    delay ( 8000 );  
    ESP.restart();
  }
}

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
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if (USE_LITTLEFS)
  Serial.print(F("\nStarting ESP32WM_MRD_ForcedConfig using LITTLEFS"));
#elif (USE_SPIFFS)
  Serial.print(F("\nStarting ESP32WM_MRD_ForcedConfig using SPIFFS"));  
#else
  Serial.print(F("\nStarting ESP32WM_MRD_ForcedConfig using EEPROM"));
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
  //Blynk.setConfigPortalIP(IPAddress(192, 168, 220, 1));
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
```

#### 2. File [defines.h](examples/ESP32WM_MRD_ForcedConfig/defines.h)

```cpp
/*
  // To add something similar to this for ESP32-C3
  #if CONFIG_IDF_TARGET_ESP32
  const int8_t esp32_adc2gpio[20] = {36, 37, 38, 39, 32, 33, 34, 35, -1, -1, 4, 0, 2, 15, 13, 12, 14, 27, 25, 26};
  #elif CONFIG_IDF_TARGET_ESP32S2
  const int8_t esp32_adc2gpio[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  #elif CONFIG_IDF_TARGET_ESP32C3
  const int8_t esp32_adc2gpio[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  #endif 
 */
 
#ifndef defines_h
#define defines_h

#if !( defined(ESP32) )
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#elif ( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
        ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
        ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #define BOARD_TYPE      "ESP32-S2"
#elif ( ARDUINO_ESP32C3_DEV )
  // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-gpio.c
  #warning ESP32-C3 boards not fully supported yet. Only SPIFFS and EEPROM OK. Tempo esp32_adc2gpio to be replaced
  const int8_t esp32_adc2gpio[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  #define BOARD_TYPE      "ESP32-C3"
#else
  #define BOARD_TYPE      "ESP32"
#endif

#define BLYNK_PRINT Serial

#define BLYNK_WM_DEBUG                3

#define USING_MRD     true

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

#if ( ARDUINO_ESP32C3_DEV )
  // Currently, ESP32-C3 only supporting SPIFFS and EEPROM. Will fix to support LittleFS
  #define USE_LITTLEFS          false
  #define USE_SPIFFS            true
#else
  #define USE_LITTLEFS          false
  #define USE_SPIFFS            false
#endif

#if !( USE_SPIFFS || USE_LITTLEFS)
  // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
  #define EEPROM_SIZE    (2 * 1024)
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

/////////////////////////////////////////////

// Add customs headers from v1.2.0
#define USING_CUSTOMS_STYLE                 true
#define USING_CUSTOMS_HEAD_ELEMENT          true
#define USING_CORS_FEATURE                  true

/////////////////////////////////////////////

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true

#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                            120000L

#define USE_DYNAMIC_PARAMETERS                    true

/////////////////////////////////////////////

#define REQUIRE_ONE_SET_SSID_PW             false

#define SCAN_WIFI_NETWORKS                  true

// To be able to manually input SSID, not from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           true

// From 2-15
#define MAX_SSID_IN_LIST                    8
  
/////////////////////////////////////////////

// Those above #define's must be placed before #include <BlynkSimpleEsp32_WM.h> and <BlynkSimpleEsp32_SSL_WM.h>
//////////////////////////////////////////

#define USE_SSL   true
//#define USE_SSL   false

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

#### 3. File [Credentials.h](examples/ESP32WM_MRD_ForcedConfig/Credentials.h)

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

#### 4. File [dynamicParams.h](examples/ESP32WM_MRD_ForcedConfig/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

// USE_DYNAMIC_PARAMETERS defined in defined.h

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

### 1. ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU

The following is the sample terminal output when running example [ESP8266WM_MRD_Config](examples/ESP8266WM_MRD_Config) on **ESP8266_NODEMCU**

#### 1.1 No MultiReset Detected => Running normally


```
Starting ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM SSL for ESP8266 v1.6.2
ESP8266 core v3.0.2
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
        /___/ v1.0.1 on NodeMCU

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
Blynk_WM SSL for ESP8266 v1.6.2
ESP8266 core v3.0.2
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

### 2. DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU

The following is the sample terminal output when running example [DHT11ESP8266_SSL](examples/DHT11ESP8266_SSL) on **ESP8266_NODEMCU**


```
Starting DHT11ESP8266_SSL using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM SSL for ESP8266 v1.6.2
ESP8266 core v3.0.2
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
        /___/ v1.0.1 on NodeMCU

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

### 3. ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV

The following is the sample terminal output when running example [ESP32WM_MRD_Config](examples/ESP32WM_MRD_Config) on **ESP32_DEV**

#### 3.1 No MultiReset Detected => Running normally


```
Starting ESP32WM_MRD_Config using LITTLEFS without SSL on ESP32_DEV
Blynk_WM for ESP32 v1.6.2
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
        /___/ v1.0.1 on ESP32

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
Blynk_WM for ESP32 v1.6.2
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
Blynk_WM for ESP32 v1.6.2
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
        /___/ v1.0.1 on ESP32

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
        /___/ v1.0.1 on ESP32

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
        /___/ v1.0.1 on ESP32

[3984637] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[3984791] Ready (ping: 6ms).
[3984859] Connected to Blynk Server = account.duckdns.org, Token = token1
[3984859] run: WiFi+Blynk reconnected

```

---

### 4. DHT11ESP32_SSL using LITTLEFS with SSL on ESP32_DEV

The following is the sample terminal output when running example [DHT11ESP8266_SSL](examples/DHT11ESP8266_SSL) on **ESP8266_NODEMCU**


```
Starting DHT11ESP32_SSL using LITTLEFS with SSL on ESP32_DEV
Blynk_WM SSL for ESP32 v1.6.2
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
        /___/ v1.0.1 on ESP32

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

### 5. ESP8266WM_MRD_ForcedConfig using non-persistent ConfigPortal virtual button

The following is the sample terminal output when running example [ESP8266WM_MRD_ForcedConfig](examples/ESP8266WM_MRD_ForcedConfig) on **ESP8266_NODEMCU**

The function to call is 

```
// This will keep CP once, clear after reset, even you didn't enter CP at all.
Blynk.resetAndEnterConfigPortal();
```

#### 5.1 Start normally then press non-persistent ConfigPortal virtual button

```
Starting ESP8266WM_MRD_ForcedConfig using LittleFS without SSL on ESP8266_NODEMCU
Blynk_WM for ESP8266 v1.6.2
ESP8266 core v3.0.2
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[293] Hostname=8266-Master-Controller
[302] LoadCfgFile 
[303] OK
[303] ======= Start Stored Config Data =======
[303] Hdr=ESP8266,BrdName=Air-Control
[303] SSID=HueNet1,PW=12345678
[304] SSID1=HueNet2,PW1=12345678
[307] Server=account.duckdns.org,Token=token
[313] Server1=account.duckdns.org,Token1=token1
[320] Port=8080
[321] ======= End Config Data =======
[325] CCSum=0x351f,RCSum=0x351f
[329] LoadCredFile 
[329] CrR:pdata=new-mqtt-server,len=34
[333] CrR:pdata=1883,len=6
[335] CrR:pdata=new-mqtt-username,len=34
[339] CrR:pdata=default-mqtt-password,len=34
[344] CrR:pdata=default-mqtt-SubTopic,len=34
[347] CrR:pdata=default-mqtt-PubTopic,len=34
[351] OK
[352] CrCCsum=0x2670,CrRCsum=0x2670
[355] Valid Stored Dynamic Data
[358] Hdr=ESP8266,BrdName=Air-Control
[361] SSID=HueNet1,PW=12345678
[364] SSID1=HueNet2,PW1=12345678
[367] Server=account.duckdns.org,Token=token
[373] Server1=account.duckdns.org,Token1=token1
[379] Port=8080
[381] ======= End Config Data =======
[384] Check if isForcedCP
[389] LoadCPFile 
[389] OK
[389] bg: noConfigPortal = true
[392] Connecting MultiWifi...
[6648] WiFi connected after time: 1
[6648] SSID=HueNet1,RSSI=-37
[6648] Channel=2,IP=192.168.2.87
[6648] bg: WiFi OK. Try Blynk
[6648] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on NodeMCU

[6661] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6765] Ready (ping: 7ms).
[6832] Connected to BlynkServer=account.duckdns.org,Token=token
[6832] bg: WiFi+Blynk OK

Blynk ESP8266 using LittleFS connected.
Board Name : Air-Control
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK
BCP Button Hit. Rebooting
[19414] setForcedCP non-Persistent  <========== Non-Persistent CP requested
[19419] SaveCPFile 
[19423] OK
[19429] SaveBkUpCPFile 
[19433] OK
```

#### 5.2 Enter non-persistent ConfigPortal

Non-Persistent CP will be removed after first reset, even you didn't enter the CP. You can optionally enter CP, input and `Save` config data.

```
Starting ESP8266WM_MRD_ForcedConfig using LittleFS without SSL on ESP8266_NODEMCU
Blynk_WM for ESP8266 v1.6.2
ESP8266 core v3.0.2
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[287] Hostname=8266-Master-Controller
[300] LoadCfgFile 
[300] OK
[300] ======= Start Stored Config Data =======
[300] Hdr=ESP8266,BrdName=Air-Control
[300] SSID=HueNet1,PW=12345678
[302] SSID1=HueNet2,PW1=12345678
[305] Server=account.duckdns.org,Token=token
[311] Server1=account.duckdns.org,Token1=token1
[317] Port=8080
[319] ======= End Config Data =======
[322] CCSum=0x351f,RCSum=0x351f
[327] LoadCredFile 
[327] CrR:pdata=new-mqtt-server,len=34
[330] CrR:pdata=1883,len=6
[333] CrR:pdata=new-mqtt-username,len=34
[336] CrR:pdata=default-mqtt-password,len=34
[341] CrR:pdata=default-mqtt-SubTopic,len=34
[344] CrR:pdata=default-mqtt-PubTopic,len=34
[348] OK
[349] CrCCsum=0x2670,CrRCsum=0x2670
[352] Valid Stored Dynamic Data
[355] Hdr=ESP8266,BrdName=Air-Control
[358] SSID=HueNet1,PW=12345678
[361] SSID1=HueNet2,PW1=12345678
[364] Server=account.duckdns.org,Token=token
[370] Server1=account.duckdns.org,Token1=token1
[377] Port=8080
[378] ======= End Config Data =======
[382] Check if isForcedCP
[387] LoadCPFile 
[387] OK
[387] bg: isForcedConfigPortal = true
[390] bg:Stay forever in CP:Forced-non-Persistent  <========== Non-Persistent CP will clear after reset
[394] clearForcedCP
[401] SaveCPFile 
[405] OK
[411] SaveBkUpCPFile 
[415] OK
[2467] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[2467] IP=192.168.4.1,ch=7
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK

```

---

### 6. ESP8266WM_MRD_ForcedConfig using persistent ConfigPortal virtual button

The following is the sample terminal output when running example [ESP8266WM_MRD_ForcedConfig](examples/ESP8266WM_MRD_ForcedConfig) on **ESP8266_NODEMCU**

The function to call is 

```
// This will keep CP once, clear after reset, even you didn't enter CP at all.
Blynk.resetAndEnterConfigPortalPersistent();
```

#### 6.1 Start normally then press persistent ConfigPortal virtual button

```
Starting ESP8266WM_MRD_ForcedConfig using LittleFS without SSL on ESP8266_NODEMCU
Blynk_WM for ESP8266 v1.6.2
ESP8266 core v3.0.2
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[388] Hostname=8266-Master-Controller
[403] LoadCfgFile 
[404] OK
[404] ======= Start Stored Config Data =======
[404] Hdr=ESP8266,BrdName=Air-Control
[404] SSID=HueNet1,PW=12345678
[405] SSID1=HueNet2,PW1=12345678
[408] Server=account.duckdns.org,Token=token
[414] Server1=account.duckdns.org,Token1=token1
[421] Port=8080
[422] ======= End Config Data =======
[426] CCSum=0x351f,RCSum=0x351f
[431] LoadCredFile 
[431] CrR:pdata=new-mqtt-server,len=34
[434] CrR:pdata=1883,len=6
[436] CrR:pdata=new-mqtt-username,len=34
[440] CrR:pdata=default-mqtt-password,len=34
[444] CrR:pdata=default-mqtt-SubTopic,len=34
[448] CrR:pdata=default-mqtt-PubTopic,len=34
[452] OK
[453] CrCCsum=0x2670,CrRCsum=0x2670
[456] Valid Stored Dynamic Data
[459] Hdr=ESP8266,BrdName=Air-Control
[462] SSID=HueNet1,PW=12345678
[465] SSID1=HueNet2,PW1=12345678
[468] Server=account.duckdns.org,Token=token
[474] Server1=account.duckdns.org,Token1=token1
[480] Port=8080
[482] ======= End Config Data =======
[485] Check if isForcedCP
[490] LoadCPFile 
[490] OK
[490] bg: noConfigPortal = true
[493] Connecting MultiWifi...
[6757] WiFi connected after time: 1
[6757] SSID=HueNet1,RSSI=-37
[6757] Channel=2,IP=192.168.2.87
[6757] bg: WiFi OK. Try Blynk
[6757] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on NodeMCU

[6770] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6874] Ready (ping: 9ms).
[6941] Connected to BlynkServer=account.duckdns.org,Token=token
[6942] bg: WiFi+Blynk OK

Blynk ESP8266 using LittleFS connected.
Board Name : Air-Control
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK
BPersistent CP Button Hit. Rebooting
[23500] setForcedCP Persistent     <========== Persistent CP requested
[23507] SaveCPFile 
[23513] OK
[23520] SaveBkUpCPFile 
[23526] OK

```

#### 6.2 Enter persistent ConfigPortal

Persistent CP will remain after resets. The only way to get rid of Config Portal is to enter CP, input (even fake data or none) and `Save` config data.

```
Starting ESP8266WM_MRD_ForcedConfig using LittleFS without SSL on ESP8266_NODEMCU
Blynk_WM for ESP8266 v1.6.2
ESP8266 core v3.0.2
ESP_MultiResetDetector v1.1.1
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[292] Hostname=8266-Master-Controller
[310] LoadCfgFile 
[310] OK
[310] ======= Start Stored Config Data =======
[310] Hdr=ESP8266,BrdName=Air-Control
[310] SSID=HueNet1,PW=12345678
[312] SSID1=HueNet2,PW1=12345678
[315] Server=account.duckdns.org,Token=token
[321] Server1=account.duckdns.org,Token1=token1
[327] Port=8080
[329] ======= End Config Data =======
[332] CCSum=0x351f,RCSum=0x351f
[339] LoadCredFile 
[340] CrR:pdata=new-mqtt-server,len=34
[340] CrR:pdata=1883,len=6
[343] CrR:pdata=new-mqtt-username,len=34
[346] CrR:pdata=default-mqtt-password,len=34
[350] CrR:pdata=default-mqtt-SubTopic,len=34
[354] CrR:pdata=default-mqtt-PubTopic,len=34
[358] OK
[359] CrCCsum=0x2670,CrRCsum=0x2670
[362] Valid Stored Dynamic Data
[365] Hdr=ESP8266,BrdName=Air-Control
[368] SSID=HueNet1,PW=12345678
[371] SSID1=HueNet2,PW1=12345678
[374] Server=account.duckdns.org,Token=token
[380] Server1=account.duckdns.org,Token1=token1
[387] Port=8080
[388] ======= End Config Data =======
[392] Check if isForcedCP
[397] LoadCPFile 
[398] OK
[398] bg: isForcedConfigPortal = true
[400] bg:Stay forever in CP:Forced-Persistent     <========== Persistent CP will remain after reset
[697] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[697] IP=192.168.4.1,ch=6
F
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop multiResetDetecting
Saving config file...
Saving config file OK

```

---

### 7. ESP8266WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP8266_NODEMCU

The following is the sample terminal output when running example [ESP8266WM_MRD_ForcedConfig](examples/ESP8266WM_MRD_ForcedConfig) on **ESP8266_NODEMCU**. Please note that this fix the SSL issue with Blynk Cloud Server.

```
Starting ESP8266WM_MRD_ForcedConfig using LittleFS with SSL on ESP8266_NODEMCU
Blynk_WM SSL for ESP8266 v1.6.2
ESP8266 core v3.0.2
ESP_MultiResetDetector v1.1.1
[267] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[289] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[296] Set CORS Header to : Your Access-Control-Allow-Origin
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[339] Hostname=8266-Master-Controller
[361] LoadCfgFile 
[361] OK
[361] ======= Start Stored Config Data =======
[361] Hdr=SSL_ESP8266,BrdName=ESP8266
[361] SSID=HueNet1,PW=12345678
[363] SSID1=HueNet2,PW1=12345678
[366] Server=blynk-cloud.com,Token=token1
[372] Server1=blynk-cloud.com,Token1=token2
[378] Port=9443
[379] ======= End Config Data =======
[383] CCSum=0x2fa3,RCSum=0x2fa3
[390] LoadCredFile 
[391] CrR:pdata=default-mqtt-server,len=34
[391] CrR:pdata=1883,len=6
[393] CrR:pdata=default-mqtt-username,len=34
[397] CrR:pdata=default-mqtt-password,len=34
[401] CrR:pdata=default-mqtt-SubTopic,len=34
[405] CrR:pdata=default-mqtt-PubTopic,len=34
[409] OK
[410] CrCCsum=0x29a6,CrRCsum=0x29a6
[413] Valid Stored Dynamic Data
[416] Hdr=SSL_ESP8266,BrdName=ESP8266
[420] SSID=HueNet1,PW=12345678
[423] SSID1=HueNet2,PW1=12345678
[425] Server=blynk-cloud.com,Token=token1
[431] Server1=blynk-cloud.com,Token1=token2
[438] Port=9443
[439] ======= End Config Data =======
[442] Check if isForcedCP
[450] LoadCPFile 
[450] OK
[450] bg: noConfigPortal = true
[450] Connecting MultiWifi...
[6667] WiFi connected after time: 1
[6667] SSID: HueNet1, RSSI = -46
[6667] Channel: 2, IP address: 192.168.2.92
[6668] bg: WiFi OK. Try Blynk
[6669] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on NodeMCU

[22695] NTP time: Mon Apr 19 06:36:31 2021
[22695] BlynkArduinoClient.connect: Connecting to blynk-cloud.com:9443
[23153] Ready (ping: 1ms).
[23245] Connected to Blynk Server = blynk-cloud.com, Token = token1
[23245] bg: WiFi+Blynk OK

Blynk ESP8266 using LittleFS connected.
Board Name : ESP8266
Stop multiResetDetecting
Saving config file...
Saving config file OK
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
BBBB
```

---

### 8. ESP32WM_MRD_Config using LITTLEFS with SSL on ESP32S2_DEV

The following is the sample terminal output when running example [ESP32WM_MRD_Config](examples/ESP32WM_MRD_Config) on **ESP8266_NODEMCU**. Please note that this fix the SSL issue with Blynk Cloud Server and runs on new **ESP32-S2 using LittleFS** using esp32 core v1.0.6+ (not official release v1.0.6, but master release as of 2021/04/19).


```
Starting ESP32WM_MRD_Config using LITTLEFS with SSL on ESP32S2_DEV
Blynk_WM SSL for ESP32 v1.6.2
ESP_MultiResetDetector v1.1.1
[134394] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[134417] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[134424] Set CORS Header to : Your Access-Control-Allow-Origin
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[134657] Hostname=ESP32-Master-Controller
[134695] LoadCfgFile 
[134700] OK
[134700] ======= Start Stored Config Data =======
[134700] Hdr=SSL_ESP32,BrdName=ESP8266
[134700] SSID=HueNet1,PW=12345678
[134701] SSID1=HueNet2,PW1=12345678
[134704] Server=account.duckdns.org,Token=token1
[134710] Server1=account.duckdns.org,Token1=token2
[134717] Port=9443
[134719] ======= End Config Data =======
[134722] CCSum=0x33eb,RCSum=0x33eb
[134738] LoadCredFile 
[134742] CrR:pdata=default-mqtt-server,len=34
[134743] CrR:pdata=1883,len=6
[134743] CrR:pdata=default-mqtt-username,len=34
[134743] CrR:pdata=default-mqtt-password,len=34
[134747] CrR:pdata=default-mqtt-SubTopic,len=34
[134751] CrR:pdata=default-mqtt-PubTopic,len=34
[134755] OK
[134756] CrCCsum=0x29a6,CrRCsum=0x29a6
[134760] Valid Stored Dynamic Data
[134763] Hdr=SSL_ESP32,BrdName=ESP8266
[134766] SSID=HueNet1,PW=12345678
[134769] SSID1=HueNet2,PW1=12345678
[134773] Server=account.duckdns.org,Token=token1
[134779] Server1=account.duckdns.org,Token1=token2
[134786] Port=9443
[134787] ======= End Config Data =======
[134791] Check if isForcedCP
[134806] LoadCPFile 
[134811] OK
[134811] bg: noConfigPortal = true
[134811] Connecting MultiWifi...
[144534] WiFi connected after time: 1
[144534] SSID: HueNet1, RSSI = -38
[144534] Channel: 2, IP address: 192.168.2.157
[144535] bg: WiFi OK. Try Blynk
[144536] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on ESP32

[145549] NTP time: Mon Apr 19 05:11:59 2021
[145549] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[146810] Certificate OK
[146826] Ready (ping: 15ms).
[146895] Connected to Blynk Server = account.duckdns.org, Token = token1
[146895] bg: WiFi+Blynk OK

Blynk ESP32 using LittleFS connected
Board Name : ESP8266
Stop multiResetDetecting
Saving config file...
Saving config file OK
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
```

---

### 9. ESP32WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP32_DEV to demo WiFi Scan

The following is the sample terminal output when running example [ESP32WM_MRD_ForcedConfig](examples/ESP32WM_MRD_ForcedConfig) on **ESP32_DEV**  with WiFi Scan for selection in Configuration Portal.

#### 9.1 MRD/DRD => Open Config Portal

```
Starting ESP32WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP32_DEV
Blynk_WM SSL for ESP32 v1.6.2
ESP_MultiResetDetector v1.1.1
[228] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[250] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[257] Set CORS Header to : Your Access-Control-Allow-Origin
LittleFS Flag read = 0xFFFC0003
multiResetDetectorFlag = 0xFFFC0003
lowerBytes = 0x0003, upperBytes = 0x0003
multiResetDetected, number of times = 3
Saving config file...
Saving config file OK
[332] Multi or Double Reset Detected
[488] Hostname=ESP32-Master-Controller
[558] LoadCfgFile 
[571] OK
[571] ======= Start Stored Config Data =======
[571] Hdr=SSL_ESP32,BrdName=ESP8266
[571] SSID=HueNet1,PW=password
[571] SSID1=HueNet2,PW1=password
[574] Server=blynk-cloud.com,Token=token
[577] Server1=blynk-cloud.com,Token1=token2
[581] Port=9443
[583] ======= End Config Data =======
[586] CCSum=0x2185,RCSum=0x2185
[620] LoadCredFile 
[632] CrR:pdata=default-mqtt-server,len=34
[632] CrR:pdata=1883,len=6
[632] CrR:pdata=default-mqtt-username,len=34
[632] CrR:pdata=default-mqtt-password,len=34
[635] CrR:pdata=default-mqtt-SubTopic,len=34
[639] CrR:pdata=default-mqtt-PubTopic,len=34
[643] OK
[644] CrCCsum=0x29a6,CrRCsum=0x29a6
[647] Valid Stored Dynamic Data
[650] Hdr=SSL_ESP32,BrdName=ESP8266
[653] SSID=HueNet1,PW=password
[656] SSID1=HueNet2,PW1=password
[659] Server=blynk-cloud.com,Token=token
[663] Server1=blynk-cloud.com,Token1=token2
[667] Port=9443
[668] ======= End Config Data =======
[671] Check if isForcedCP
[702] LoadCPFile 
[713] OK
[713] bg: isForcedConfigPortal = false
[713] bg:Stay forever in CP:DRD/MRD
[713] clearForcedCP
[746] SaveCPFile 
[758] OK
[790] SaveBkUpCPFile 
[802] OK
[802] Scanning Network
[6310] scanWifiNetworks: Done, Scanned Networks n = 11
[6310] Sorting
[6310] Removing Dup
[6311] WiFi networks found:
[6312] 1: HueNet, -26dB
[6312] 2: HueNet1, -30dB
[6314] 3: HueNetTek, -32dB
[6316] 4: dragino-1ed63c, -35dB
[6319] 5: HueNet2, -57dB
[6322] 6: bacau, -68dB
[6324] 7: guest_24, -69dB
[6326] 8: rogers786, -87dB
[6328] 9: Rogers 786, -87dB
[6331] 10: Access 2.0, -92dB
[6334] 11: Family Room speaker.o, -96dB
[7197] 
stConf:SSID=TestPortal-ESP32,PW=TestPortalPass
[7197] IP=192.168.4.1,ch=6
[7299] s:millis() = 7299, configTimeout = 127299
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
[19720] h: Init menuItemUpdated
[19863] h:mqtt=default-mqtt-server
[19863] h2:myMenuItems[0]=default-mqtt-server
[19877] h:mqpt=1883
[19877] h2:myMenuItems[1]=1883
[19891] h:user=default-mqtt-username
[19891] h2:myMenuItems[2]=default-mqtt-username
[19911] h:mqpw=default-mqtt-password
[19911] h2:myMenuItems[3]=default-mqtt-password
[19925] h:subs=default-mqtt-SubTopic
[19925] h2:myMenuItems[4]=default-mqtt-SubTopic
[19939] h:pubs=default-mqtt-PubTopic
[19939] h2:myMenuItems[5]=default-mqtt-PubTopic
[19942] h:Updating LittleFS:/wmssl_conf.dat
[19982] SaveCfgFile 
[19982] WCSum=0x34ef
[19996] OK
[20173] SaveBkUpCfgFile 
[20184] OK
[20217] SaveCredFile 
[20217] CW1:pdata=default-mqtt-server,len=34
[20228] CW1:pdata=1883,len=6
[20228] CW1:pdata=default-mqtt-username,len=34
[20228] CW1:pdata=default-mqtt-password,len=34
[20228] CW1:pdata=default-mqtt-SubTopic,len=34
[20232] CW1:pdata=default-mqtt-PubTopic,len=34
[20237] OK
[20237] CrWCSum=0x29a6
[20275] SaveBkUpCredFile 
[20276] CW2:pdata=default-mqtt-server,len=34
[20288] CW2:pdata=1883,len=6
[20288] CW2:pdata=default-mqtt-username,len=34
[20288] CW2:pdata=default-mqtt-password,len=34
[20288] CW2:pdata=default-mqtt-SubTopic,len=34
[20292] CW2:pdata=default-mqtt-PubTopic,len=34
[20297] OK
[20297] h:Rst
```

#### 9.2 Config Data Saved => Connection to Blynk


```
Starting ESP32WM_MRD_ForcedConfig using LITTLEFS with SSL on ESP32_DEV
Blynk_WM SSL for ESP32 v1.6.2
ESP_MultiResetDetector v1.1.1
[227] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[249] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[256] Set CORS Header to : Your Access-Control-Allow-Origin
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[635] Hostname=ESP32-Master-Controller
[704] LoadCfgFile 
[716] OK
[717] ======= Start Stored Config Data =======
[717] Hdr=SSL_ESP32,BrdName=ESP32-SSL
[717] SSID=HueNet,PW=password
[717] SSID1=HueNet1,PW1=password
[719] Server=account.duckdns.org,Token=token
[726] Server1=account.duckdns.org,Token1=token1
[732] Port=9443
[733] ======= End Config Data =======
[737] CCSum=0x34ef,RCSum=0x34ef
[768] LoadCredFile 
[779] CrR:pdata=default-mqtt-server,len=34
[779] CrR:pdata=1883,len=6
[779] CrR:pdata=default-mqtt-username,len=34
[780] CrR:pdata=default-mqtt-password,len=34
[783] CrR:pdata=default-mqtt-SubTopic,len=34
[787] CrR:pdata=default-mqtt-PubTopic,len=34
[791] OK
[791] CrCCsum=0x29a6,CrRCsum=0x29a6
[795] Valid Stored Dynamic Data
[797] Hdr=SSL_ESP32,BrdName=ESP32-SSL
[801] SSID=HueNet,PW=password
[804] SSID1=HueNet1,PW1=password
[806] Server=account.duckdns.org,Token=token
[813] Server1=account.duckdns.org,Token1=token1
[819] Port=9443
[820] ======= End Config Data =======
[824] Check if isForcedCP
[858] LoadCPFile 
[871] OK
[871] bg: noConfigPortal = true
[871] Connecting MultiWifi...
[19266] WiFi connected after time: 1
[19266] SSID: HueNet, RSSI = -29
[19266] Channel: 10, IP address: 192.168.2.45
[19267] bg: WiFi OK. Try Blynk
[19268] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on ESP32

[20282] NTP time: Sun Apr 25 04:52:35 2021
[20282] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[22407] Certificate OK
[22412] Ready (ping: 4ms).
[22480] Connected to Blynk Server = account.duckdns.org, Token = token
[22480] bg: WiFi+Blynk OK

Blynk ESP32 using LittleFS connected
Board Name : ESP32-SSL
Stop multiResetDetecting
Saving config file...
Saving config file OK
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
RBRBRBRBRBRBRBRB
```

---

### 10. ESP8266WM_MRD_Config using LITTLEFS with SSL on ESP8266_NODEMCU_ESP12E using new ESP8266 core v3.0.2

The following is the sample terminal output when running example [ESP8266WM_MRD_Config](examples/ESP8266WM_MRD_Config) on **ESP8266_NODEMCU_ESP12E** using new **ESP8266 core v3.0.0+**


```
Starting ESP8266WM_MRD_Config using LittleFS with SSL on ESP8266_NODEMCU_ESP12E
ESP8266 core v3.0.2
Blynk_WM SSL for ESP8266 v1.6.2
ESP_MultiResetDetector v1.1.1
[274] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[296] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[303] Set CORS Header to : Your Access-Control-Allow-Origin
LittleFS Flag read = 0xFFFE0001
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x0001, upperBytes = 0x0001
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xFFFE0001
Saving config file...
Saving config file OK
[337] Hostname=8266-Master-Controller
[349] LoadCfgFile 
[349] OK
[349] ======= Start Stored Config Data =======
[349] Hdr=SSL_ESP8266,BrdName=ESP32
[350] SSID=HueNet1,PW=password
[351] SSID1=HueNet2,PW1=password
[354] Server=account.duckdns.org,Token=token
[360] Server1=account.duckdns.org,Token1=token1
[366] Port=9443
[368] ======= End Config Data =======
[371] CCSum=0x3473,RCSum=0x3473
[376] LoadCredFile 
[376] CrR:pdata=default-mqtt-server,len=34
[380] CrR:pdata=1883,len=6
[382] CrR:pdata=default-mqtt-username,len=34
[386] CrR:pdata=default-mqtt-password,len=34
[390] CrR:pdata=default-mqtt-SubTopic,len=34
[394] CrR:pdata=default-mqtt-PubTopic,len=34
[398] OK
[399] CrCCsum=0x29a6,CrRCsum=0x29a6
[402] Valid Stored Dynamic Data
[405] Hdr=SSL_ESP8266,BrdName=ESP32
[408] SSID=HueNet1,PW=password
[411] SSID1=HueNet2,PW1=password
[414] Server=account.duckdns.org,Token=token
[420] Server1=account.duckdns.org,Token1=token1
[426] Port=9443
[428] ======= End Config Data =======
[431] Check if isForcedCP
[436] LoadCPFile 
[436] OK
[436] bg: noConfigPortal = true
[439] Connecting MultiWifi...
[5576] WiFi connected after time: 1
[5577] SSID: HueNet1, RSSI = -43
[5577] Channel: 2, IP address: 192.168.2.135
[5577] bg: WiFi OK. Try Blynk
[5578] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.0.1 on ESP8266_NODEMCU_ESP12E

[6592] NTP time: Thu May 20 02:13:51 2021
[6624] BlynkArduinoClient.connect: Connecting to account.duckdns.org:9443
[7360] Certificate OK
[7387] Ready (ping: 20ms).
[7457] Connected to Blynk Server = account.duckdns.org, Token = token
[7458] bg: WiFi+Blynk OK

Blynk ESP8288 using LittleFS connected.
Board Name : ESP8266
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
BBBBBRBBBB BBRBBBBBBRBB BBBBRBBBBBB
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
21. Add **LittleFS** support to ESP32 using [LITTLEFS](https://github.com/lorol/LITTLEFS) Library.
22. Add support to MultiDetectDetector and MRD-related examples
23. Clean-up all compiler warnings possible.
24. Add Table of Contents
25. Add Version String
26. Add functions to control Config Portal from software or Virtual Switches.
27. Add support to **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using EEPROM, LittleFS and SPIFFS**
28. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
29. Add support to **ESP32-C3 using EEPROM and SPIFFS**
30. Fix SSL issue with Blynk Cloud Server by using SSL in unsecured mode.
31. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
32. Enforce WiFi PWD minimum length of 8 chars
33. Enable **scan of WiFi networks** for selection in Configuration Portal
34. Drastically update code to work with either ESP8266 new breaking ESP8266 core v3.0.0+ or old core ESP8266 v2.7.4-
35. Make SSL working using `BearSSL`, not deprecated `axTLS`

---
---

### Contributions and thanks

1. Thanks to [lorol](https://github.com/lorol) for useful [LittleFS_esp32 Library](https://github.com/lorol/LITTLEFS)
2. Thanks to [chriskio](https://github.com/chriskio) to report [AP-staying-open bug](https://github.com/khoih-prog/Blynk_WM/issues/2). 
3. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
4. Thanks to [Thor Johnson](https://github.com/thorathome) and [Thor Johnson in Blynk](https://community.blynk.cc/u/thorathome) to test, find bug, suggest and encourage to add those new features in v1.0.13, such as Default Credentials/Dynamic Parms, Configurable Config Portal Title, DRD. The powerful [Blynk_WM_Template](examples/Blynk_WM_Template) is written by [Thor Johnson](https://github.com/thorathome) and is included in the examples with his permission. Check these new features thanks to his direct contribution and/or enhancement requests :
  * [WM Config Portal using BlynkSimpleEsp32/8266_WM.h](https://community.blynk.cc/t/wm-config-portal-using-blynksimpleesp32-8266-wm-h/45402).
  * [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
  * [Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27](https://github.com/khoih-prog/Blynk_WM/issues/27)
5. Thanks to [Thor Johnson](https://github.com/thorathome) and [kevinleberge](https://github.com/kevinleberge) to help locate the bugs, discuss the USE_DEFAULT_CONFIG_DATA solution leading to release v1.0.16. See [Can’t load defaults](https://github.com/khoih-prog/Blynk_WM/issues/15) and [Setting "#define USE_DYNAMIC_PARAMETERS false" on Blynk_WM_Template.ino results in compile error](https://github.com/khoih-prog/Blynk_WM/issues/16)
6. Thanks to [komaneko](https://github.com/jjskaife) to report bugs in [Custom Blynk port not working for BlynkSimpleEsp32_Async_WM.h #4](https://github.com/khoih-prog/Blynk_Async_WM/issues/4) leading to v1.3.1
7. Thanks to [Michael H. "bizprof"](https://github.com/bizprof). With the impressive new feature :
  - `Enable scan of WiFi networks for selection in Configuration Portal`. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10) leading to v1.4.0
  

<table>
  <tr>
    <td align="center"><a href="https://github.com/lorol"><img src="https://github.com/lorol.png" width="100px;" alt="lorol"/><br /><sub><b>⭐️ lorol</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/chriskio"><img src="https://github.com/chriskio.png" width="100px;" alt="chriskio"/><br /><sub><b>chriskio</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/brondolin"><img src="https://github.com/brondolin.png" width="100px;" alt="brondolin"/><br /><sub><b>brondolin</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/thorathome"><img src="https://github.com/thorathome.png" width="100px;" alt="thorathome"/><br /><sub><b>⭐️ Thor Johnson</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kevinleberge"><img src="https://github.com/kevinleberge.png" width="100px;" alt="kevinleberge"/><br /><sub><b>kevinleberge</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/jjskaife"><img src="https://github.com/jjskaife.png" width="100px;" alt="jjskaife"/><br /><sub><b>komaneko</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/bizprof"><img src="https://github.com/bizprof.png" width="100px;" alt="bizprof"/><br /><sub><b>⭐️⭐️ Michael H. "bizprof"</b></sub></a><br /></td>
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

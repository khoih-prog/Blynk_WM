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

* [Changelog](#changelog)
  * [Releases v1.6.2](#releases-v162)
  * [Releases v1.6.1](#releases-v161)
  * [Major Releases v1.6.0](#major-releases-v160)
  * [Releases v1.5.0](#releases-v150)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Major Releases v1.3.0](#major-releases-v130)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Releases v1.1.3](#releases-v113)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.16](#releases-v1016)
  * [Releases v1.0.15](#releases-v1015)
  * [Releases v1.0.14](#releases-v1014)
  * [Releases v1.0.13](#releases-v1013)
  * [Releases v1.0.12](#releases-v1012)
  * [Releases v1.0.11](#releases-v1011)
  * [Releases v1.0.10](#releases-v1010)

---
---

## Changelog

### Releases v1.6.2

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Releases v1.6.1

1. Fix issue with new **ESP8266 core v3.0.1**


### Major Releases v1.6.0

1. Fix AP connect issue caused by **breaking ESP8266 core v3.0.0**. Caused by multiple core changes, but the new solution results a better and faster connection to AP.
2. Fix SSL issue caused by breaking ESP8266 core v3.0.0. Now the better **BearSSL** is used in both ESP32 and ESP8266 to replace the ESP8266 deprecated `axTLS`. Check [Remove axTLS from code and documentation #7437](https://github.com/esp8266/Arduino/pull/7437)
3. Fix the `BLYNK_INFO_DEVICE`displaying the generic ESP8266 board with Blynk logo. Caused by new ESP8266 core changes of `build.board`. For example from `ESP8266_NODEMCU` in core v2.7.4 to `ESP8266_NODEMCU_ESP12E` in core v3.0.0
4. Fix many warnings only displayed in new core ESP8266 v3.0.0
5. Make code compatible for either new ESP8266 core v3.0.0+ or ealier cores v2.7.4-

### Releases v1.5.0

1. Fix bug. 
2. Optimize and sync with [**Blynk_Async_WM library v1.5.0**](https://github.com/khoih-prog/Blynk_Async_WM) 


### Major Releases v1.4.0

1. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10). Now you can select optional **SCAN_WIFI_NETWORKS**, **MANUAL_SSID_INPUT_ALLOWED** to be able to manually input SSID, not only from a scanned SSID lists and **MAX_SSID_IN_LIST** (from 2-15)
2. Fix invalid "blank" Config Data treated as Valid.
3. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
4. Enforce WiFi PWD minimum length of 8 chars
5. Minor enhancement to not display garbage when data is invalid

### Releases v1.3.1

1. Fix issue of custom Blynk port (different from 8080 or 9443) not working on ESP32. Check [Custom Blynk port not working for BlynkSimpleEsp32_Async_WM.h #4](https://github.com/khoih-prog/Blynk_Async_WM/issues/4)

### Major Releases v1.3.0

1. Add **LittleFS and SPIFFS** support to new **ESP32-S2** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).
2. Add **EEPROM and SPIFFS** support to new **ESP32-C3** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).
3. Fix SSL issue with Blynk Cloud Server
4. Update examples

### Major Releases v1.2.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Add support to **ESP32-S2 (ESP32-S2 Saola and AI-Thinker ESP-12K)**. Currently using EEPROM only. To add support to LittleFS and SPIFFS in future releases.
3. Fix Config Portal Bug.
4. Tested with [**Latest ESP32 Core 1.0.5**](https://github.com/espressif/arduino-esp32) for ESP32-based boards.
5. Update examples

### Releases v1.1.3

1. To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)

### Releases v1.1.2

1. Fix rare Config Portal bug not updating Config and dynamic Params data successfully in very noisy or weak WiFi situation

### Releases v1.1.1

1. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
2. Add examples to demo the new Virtual ConfigPortal SW feature
3. Optimize code

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

#### Releases v1.0.12

1. Fix severe bug in v1.0.11

#### Releases v1.0.11

##### Severe connecting bug. Don't use

1. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved **automatically in EEPROM, or SPIFFS**.

#### Releases v1.0.10

1. WiFi Password max length is 63, according to WPA2 standard
2. Permit to input special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.



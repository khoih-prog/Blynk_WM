## Blynk_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_WM.svg)](https://github.com/khoih-prog/Blynk_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_WM.svg)](http://github.com/khoih-prog/Blynk_WM/issues)

I'm inspired by [`EasyBlynk8266`](https://github.com/Barbayar/EasyBlynk8266)

This is a Blynk and WiFiManager Library for configuring/auto(re)connecting ESP8266/ESP32 modules to the best or available MultiWiFi APs and MultiBlynk servers at runtime. Connection is with or without SSL. Configuration data to be saved in either SPIFFS or EEPROM. Default Credentials as well as Dynamic custom parameters can be added and modified easily without coding knowledge. DoubleResetDetector is used to force Config Portal opening even if the Credentials are still valid.
 
This library is designed to help you to eliminate `hardcoding` your Wifi and Blynk credentials for ESP8266 and ESP32 (with/without SSL), and updating/reflashing every time you need to change them.

### Releases v1.0.15

1. Update to use LittleFS for ESP8266 core 2.7.1+.
2. Fix SSL connection bug.
3. Fix dynamicParams loading bug in v1.0.14. 
4. Add [Blynk_WM_Template example](examples/Blynk_WM_Template) contributed by [thorathome](https://github.com/thorathome).

Again thanks to [thorathome in GitHub](https://github.com/thorathome) and [thorathome in Blynk](https://community.blynk.cc/u/thorathome) for testing, bug finding, feature adding, README rewriting, collaborating, etc..

### Releases v1.0.14

1. Fix dynamicParams bug in v1.0.13. Again thanks to [thorathome in GitHub](https://github.com/thorathome) and [thorathome in Blynk](https://community.blynk.cc/u/thorathome)

### Releases v1.0.13

1. Optional default ***Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal*** to use or change instead of manually input.
2. ***DoubleDetectDetector*** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
3. Configurable ***Config Portal Title*** to be either HostName, BoardName or default undistinguishable names.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.

Thanks to [thorathome in GitHub](https://github.com/thorathome) to test, suggest and encourage to add those new features in v1.0.13, such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD.

### Releases v1.0.12

1. Fix severe bug in v1.0.11

### Releases v1.0.11

#### Severe connecting bug. Don't use

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.

### Releases v1.0.10

1. WiFi Password max length is 63, according to WPA2 standard
2. Permit to input special chars such as ***~, !, @, #, $, %, ^, &, _, -, space,etc.*** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

With version `v1.0.7` or later, you now can configure:

1. `Multiple WiFi Credentials (SSID, Password) and system will autoconnect to the best and available WiFi SSID.`
2. `Multiple Blynk Credentials (Server, Token) and system will autoconnect to the available Blynk Servers.`

With version `v1.0.5` or later, you now can configure:

1. `Config Portal Static IP address, Name and Password.`
2. `Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.`

## Prerequisite
1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1 or later`](https://github.com/blynkkk/blynk-library/releases)
3. [`ESP32 core 1.0.4 or later`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
4. [`ESP8266 core 2.6.3 or later` for Arduino](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards. To use ESP8266 core 2.7.1+ for LittleFS.
5. [`ESP_DoubleResetDetector library 1.0.3 or later`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to use LittleFS. 

### Installation

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


### How to use

In your code, replace
1. `BlynkSimpleEsp8266.h`     with `BlynkSimpleEsp8266_WM.h`      for ESP8266 `without SSL`
2. `BlynkSimpleEsp8266_SSL.h` with `BlynkSimpleEsp8266_SSL_WM.h`  for ESP8266 `with SSL`
3. `BlynkSimpleEsp32.h`       with `BlynkSimpleEsp32_WM.h`        for ESP32 `without SSL`
4. `BlynkSimpleEsp32_SSL.h`   with `BlynkSimpleEsp32_SSL_WM.h`    for ESP32 `with SSL`
5. then add

```
#define USE_SPIFFS    true
```
to use SPIFFS or

```
#define USE_SPIFFS    false
```
to use EEPROM, currently, data size in v1.0.13, with DRD and not including dynamic params, is 380  bytes from address EEPROM_START ) to save your configuration data.
EEPROM_SIZE can be specified from 512 to 4096 (2048 for ESP32) bytes. See examples [ESP32WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP32WM_Config) and [ESP8266WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP8266WM_Config).


```
// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

```

To use personalized Config Portal AP SSID and Password, as well as IP Address, channel e.g. call :

```
// Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP8266", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 200, 1));
  // Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);
```

You can specify STA-mode Static IP address,  Gateway, Subnet Mask, as well as DNS server 1 and 2:

```
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

Also see examples: 
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


## So, how it works?

If it cannot connect to the Blynk server in 30 seconds, no valid stored Credentials or Double Reset is detected within 10s, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an AP with default name `ESP_xxxxxx` and password `MyESP_xxxxxx` or configurable name and password you specified. The AP IP address is default at `192.168.4.1` or configured IP (e.g. `192.168.200.1`).

First, connect your (PC, Laptop, Tablet, phone, etc.) WiFi to Config Portal AP, then enter the WiFi password :

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/PortalAuth.jpg">
</p>

1. If you choose ***not to load*** default Credentials and Dynamic Parameters

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The following Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Main.png">
</p>

2. If you choose ***to load*** default Credentials and Dynamic Parameters

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The following  Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Default_Main.png">
</p>

Enter your WiFi and Blynk Credentials:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/ConfigPortal.png">
</p>

Then click ***Save***. The system will auto-restart. You will see the board's built-in LED turned OFF. That means, it's already connected to your Blynk server successfully.

### Important notes
1. Now you can use special chars such as ***~, !, @, #, $, %, ^, &, _, -, space,etc.*** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as ***%*** and ***#*** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords, BlynkServers and Tokens must be input (or to make them different from ***nothing***). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.
4. Sometimes, it's hard or not possible to connect to Config Portal WiFi AP, the majority cases are caused by WiFi channel conflict if there are too many WiFi APs running around. Please use ***random ConfigPortal WiFi AP channel*** in sketch (see code snippet below) and reset the board so that another channel is used. Repeat until connection is OK

```
// Set config portal channel, default = 1. Use 0 => random channel from 1-13 to avoid conflict
  Blynk.setConfigPortalChannel(0);
```

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

1. To load [Default Credentials](examples/ESP32WM_Config/Credentials.h)
```
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

2. To use system default to load "blank" when there is no valid Credentials
```
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

3. Example of [Default Credentials](examples/ESP32WM_Config/Credentials.h)

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

### How to add dynamic parameters from sketch

- To add custom parameters, just modify the example below

```
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
- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

or

```
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be ***unique***.

Please be noted that the following ***reserved names are already used in library***:

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


The following is the sample terminal output when running example [ESP8266WM_Config](examples/ESP8266WM_Config)

1. No Config Data with ***LOAD_DEFAULT_CONFIG_DATA = true*** => Config Portal loads default Credentials and dynamic Params

```
Starting ...
[61] ======= Start Default Config Data =======
[61] Hdr=,BrdName=Air-Control
[61] SSID=HueNet1,PW=****
[61] SSID1=HueNet2,PW1=****
[64] Server=account.ddns.net,Token=token
[69] Server1=account.duckdns.org,Token1=token1
[76] Port=8080
[77] ======= End Config Data =======
[134] Hostname=Master-Controller
[135] CCSum=0x147fc,RCSum=0xffffffff
[136] InitEEPROM,sz=4096,Datasz=0
[136] g:myMenuItems[0]=default-mqtt-server
[137] g:myMenuItems[1]=1883
[139] g:myMenuItems[2]=default-mqtt-username
[143] g:myMenuItems[3]=default-mqtt-password
[147] g:myMenuItems[4]=default-mqtt-SubTopic
[151] g:myMenuItems[5]=default-mqtt-PubTopic
[155] CrCCSum=10662
[185] bg: No configdat. Stay forever in config portal
[345] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[345] IP=192.168.200.1,ch=1
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
RF
[66057] g:myMenuItems[0]=default-mqtt-server
[66058] g:myMenuItems[1]=1883
[66059] g:myMenuItems[2]=default-mqtt-username
[66060] g:myMenuItems[3]=default-mqtt-password
[66062] g:myMenuItems[4]=default-mqtt-SubTopic
[66066] g:myMenuItems[5]=default-mqtt-PubTopic
[103213] h2:myMenuItems[0]=default-mqtt-server
[103224] h2:myMenuItems[1]=1883
[103245] h2:myMenuItems[2]=default-mqtt-username
[103265] h2:myMenuItems[3]=default-mqtt-password
[103279] h2:myMenuItems[4]=default-mqtt-SubTopic
[103299] h2:myMenuItems[5]=default-mqtt-PubTopic
[103301] h:UpdEEPROM
[103301] SaveEEPROM,sz=4096,CSum=0x3446
[103301] CrCCSum=10662
[103329] h:Rst
```

2. Input valid credentials with ***LOAD_DEFAULT_CONFIG_DATA = true*** => reboot

```
Starting ...
[57] ======= Start Default Config Data =======
[58] Hdr=,BrdName=Air-Control
[58] SSID=HueNet1,PW=****
[58] SSID1=HueNet2,PW1=j****nniqqs
[60] Server=account.ddns.net,Token=token
[66] Server1=account.duckdns.org,Token1=token1
[72] Port=8080
[73] ======= End Config Data =======
[131] Hostname=Master-Controller
[132] CCSum=0x3446,RCSum=0x3446
[132] Hdr=ESP8266,BrdName=Air-Control
[132] SSID=HueNet1,PW=****
[132] SSID1=HueNet2,PW1=****
[135] Server=account.ddns.net,Token=token
[141] Server1=account.duckdns.org,Token1=token1
[147] Port=8080
[149] ======= End Config Data =======
[152] Connecting MultiWifi...
[6290] WiFi connected after time: 1
[6290] SSID=HueNet1,RSSI=-39
[6291] Channel=2,IP=192.168.2.99
[6291] bg: WiFi OK. Try Blynk
[6291] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[6304] BlynkArduinoClient.connect: Connecting to account.ddns.net:8080
[6410] Ready (ping: 8ms).
[6477] Connected to BlynkServer=account.ddns.net,Token=token
[6477] bg: WiFi+Blynk OK

Blynk ESP8288 using EEPROM connected. Board Name : Air-Control
EEPROM size = 4096 bytes, EEPROM start address = 1024 / 0x400
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
```

3. No Config Data with ***LOAD_DEFAULT_CONFIG_DATA = false*** => Config Portal loads "blank" to all fields

```
Starting ...
[61] ======= Start Default Config Data =======
[61] Hdr=,BrdName=Air-Control
[61] SSID=HueNet1,PW=****
[61] SSID1=HueNet2,PW1=****
[63] Server=account.ddns.net,Token=token
[69] Server1=account.duckdns.org,Token1=token1
[75] Port=8080
[77] ======= End Config Data =======
[80] Hostname=Master-Controller
[84] CCSum=0x1728c,RCSum=0xffffffff
[86] CrCCsum=44880,CrRCsum=-1
[89] InitEEPROM,sz=4096,Datasz=556
[92] g:myMenuItems[0]=blank
[94] g:myMenuItems[1]=blank
[97] g:myMenuItems[2]=blank
[99] g:myMenuItems[3]=blank
[102] g:myMenuItems[4]=blank
[105] g:myMenuItems[5]=blank
[107] CrCCSum=3120
[137] bg: No configdat. Stay forever in config portal
[296] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[296] IP=192.168.200.1,ch=1
F
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
RFRF
[177928] g:myMenuItems[0]=blank
[177928] g:myMenuItems[1]=blank
[177929] g:myMenuItems[2]=blank
[177929] g:myMenuItems[3]=blank
[177930] g:myMenuItems[4]=blank
[177931] g:myMenuItems[5]=blank
RF[186385] h2:myMenuItems[0]=default-mqtt-server
[186399] h2:myMenuItems[1]=1883
[186411] h2:myMenuItems[2]=default-mqtt-username
[186428] h2:myMenuItems[3]=default-mqtt-password
[186450] h2:myMenuItems[4]=default-mqtt-SubTopic
[186465] h2:myMenuItems[5]=default-mqtt-PubTopic
[186466] h:UpdEEPROM
[186466] SaveEEPROM,sz=4096,CSum=0x3446
[186467] CrCCSum=10662
[186495] h:Rst
```

4. Input valid credentials with ***LOAD_DEFAULT_CONFIG_DATA = false*** => reboot

```
Starting ...
[54] ======= Start Default Config Data =======
[55] Hdr=,BrdName=Air-Control
[55] SSID=HueNet1,PW=****
[55] SSID1=HueNet2,PW1=****
[57] Server=account.ddns.net,Token=token
[63] Server1=account.duckdns.org,Token1=token1
[69] Port=8080
[70] ======= End Config Data =======
[128] Hostname=Master-Controller
[129] CCSum=0x3446,RCSum=0x3446
[129] CrCCsum=10662,CrRCsum=10662
[129] Hdr=ESP8266,BrdName=Air-Control
[129] SSID=HueNet1,PW=****
[132] SSID1=HueNet2,PW1=****
[135] Server=account.ddns.net,Token=token
[141] Server1=account.duckdns.org,Token1=token1
[147] Port=8080
[148] ======= End Config Data =======
[152] Connecting MultiWifi...
[6315] WiFi connected after time: 1
[6315] SSID=HueNet1,RSSI=-39
[6315] Channel=2,IP=192.168.2.99
[6316] bg: WiFi OK. Try Blynk
[6316] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[6329] BlynkArduinoClient.connect: Connecting to account.ddns.net:8080
[6361] Ready (ping: 8ms).
[6428] Connected to BlynkServer=account.ddns.net,Token=token
[6428] bg: WiFi+Blynk OK

Blynk ESP8288 using EEPROM connected. Board Name : Air-Control
EEPROM size = 4096 bytes, EEPROM start address = 2048 / 0x800
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
```

5. ***No DRD detected*** => no Config Portal with valid Credentials

```
Starting ...
SPIFFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[77] ======= Start Default Config Data =======
[77] Hdr=NonSSL,BrdName=Air-Control
[78] SSID=HueNet1,PW=****
[80] SSID1=HueNet2,PW1=****
[82] Server=account.ddns.net,Token=token
[88] Server1=account.duckdns.org,Token1=token1
[95] Port=8080
[96] ======= End Config Data =======
[154] Hostname=8266-Master-Controller
[155] LoadCfgFile 
[155] OK
[156] CCSum=0x33b2,RCSum=0x33b2
[156] Hdr=ESP8266,BrdName=ESP8266-WM-v13
[156] SSID=HueNet1,PW=****
[158] SSID1=HueNet2,PW1=****
[161] Server=account.ddns.net,Token=token
[167] Server1=account.duckdns.org,Token1=token1
[173] Port=8080
[174] ======= End Config Data =======
[178] Connecting MultiWifi...
[6326] WiFi connected after time: 1
[6326] SSID=HueNet1,RSSI=-45
[6326] Channel=2,IP=192.168.2.99
[6327] bg: WiFi OK. Try Blynk
[6327] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[6340] BlynkArduinoClient.connect: Connecting to account.ddns.net:8080
[6456] Ready (ping: 7ms).
[6523] Connected to BlynkServer=account.ddns.net,Token=token
[6523] bg: WiFi+Blynk OK

Blynk ESP8288 using SPIFFS connected. Board Name : ESP8266-WM-v13
B
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
Saving config file...
Saving config file OK
```

6. ***DRD detected*** => Config Portal even with valid Credentials

```
Starting ...
SPIFFS Flag read = 0xd0d01234
doubleResetDetected
Saving config file...
Saving config file OK
[80] Double Reset Detected
[80] ======= Start Default Config Data =======
[80] Hdr=NonSSL,BrdName=Air-Control
[82] SSID=HueNet1,PW=****
[85] SSID1=HueNet2,PW1=****
[88] Server=account.ddns.net,Token=token
[93] Server1=account.duckdns.org,Token1=token1
[100] Port=8080
[101] ======= End Config Data =======
[105] Hostname=8266-Master-Controller
[124] LoadCfgFile 
[124] OK
[124] CCSum=0x33b2,RCSum=0x33b2
[125] Hdr=ESP8266,BrdName=ESP8266-WM-v13
[125] SSID=HueNet1,PW=****
[125] SSID1=HueNet2,PW1=****
[128] Server=account.ddns.net,Token=token
[134] Server1=account.duckdns.org,Token1=token1
[140] Port=8080
[141] ======= End Config Data =======
[145] bg: No configdat. Stay forever in config portal
[311] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[311] IP=192.168.200.1,ch=1
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
RF
```

7. Testing WiFi and Blynk Server lost to verify auto-reconnection

```
Starting ...
[143] Hostname=ESP8266-WM-Config
[143] CCSum=0x32c1,RCSum=0x32c1
[144] CrCCsum=6078,CrRCsum=6078
[144] Hdr=ESP8266,BrdName=ESP8266-BlynkWM-v1.0.11
[145] SSID=HueNet1,PW=****
[147] SSID1=HueNet2,PW1=****
[150] Server=account.duckdns.org,Token=token
[157] Server1=192.168.2.112,Token1=token1
[162] Port=8080
[164] Connecting MultiWifi...
[167] UseStatIP
[168] con2WF:start
[4415] WiFi connected after time: 1
[4416] SSID: HueNet1, RSSI = -51
[4416] Channel: 2, IP address: 192.168.2.220
[4416] bg: WiFi OK. Try Blynk
[4417] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[4431] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080  <= Try Server
[5125] Ready (ping: 5ms).                                           <= Connected to Server
[5125] Free RAM: 41024
[5192] Connected to Blynk Server = account.duckdns.org, Token = token
[5192] bg: WiFi+Blynk OK

Blynk ESP8288 using EEPROM connected. Board Name : ESP8266-BlynkWM-v1.0.11
EEPROM size = 4096 bytes, EEPROM start address = 0 / 0x0
Your stored Credentials :
MQTT Server = mqtt.duckdns.org
Port = 1883
MQTT UserName = mqtt-username
MQTT PWD = mqtt-pass
Subs Topics = SubsTopic1
Pubs Topics = PubsTopic1
BRBRBRBRBRBRBRBRBRBR BRBRBRBRBR
[101232] run: WiFi lost. Reconnect WiFi+Blynk                           <= Lost SSID
[101232] Connecting MultiWifi...
[106316] WiFi connected after time: 1
[106317] SSID: ****1, RSSI = -62                                        <= Connected to SSID1
[106317] Channel: 4, IP address: 192.168.2.91
[106317] run: WiFi reconnected. Connect to Blynk
[106320] BlynkArduinoClient.connect: Connecting to 192.168.2.112:8080   <= Try Server
[106352] Ready (ping: 11ms).                                            <= Connected to Server
[106419] run: WiFi+Blynk reconnected
RB
[165434] Heartbeat timeout                                              <= Lost Server
[165735] run: Blynk lost. Connect Blynk
[165735] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[165741] BlynkArduinoClient.connect: Connecting to 192.168.2.112:8080        <= Try Server not OK
[170741] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU

[170743] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080   <= Try Server1
[170781] Ready (ping: 9ms).
[170848] Connected to Blynk Server = account.duckdns.org, Token  = ****       <= Connected to Server1
[170848] run: Blynk reconnected
RBRBRBRBRBRBRB RBRB

```

You can see that the system automatically detects and connects to the best or avaiable WiFi APs and/or Blynk Servers, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, this `Blynk.begin()` is ***not a blocking call***, so you can use it for critical functions requiring in loop(). 
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

## Example [ESP32WM_Config](examples/ESP32WM_Config)

Please take a look at other examples, as well.

1. File [ESP32WM_Config.ino](examples/ESP32WM_Config/ESP32WM_Config.ino)

```cpp
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
  Serial.print("R");
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

  if (num == 40)
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
  // Debug console
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("\nStarting ...");

  dht.begin();

  // From v1.0.5
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP32", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 220, 1));
  // Set config portal channel, defalut = 1. Use 0 => random channel from 1-13
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
#if USE_SPIFFS
    Serial.println("\nBlynk ESP32 using SPIFFS connected. Board Name : " + Blynk.getBoardName());
#else
    Serial.println("\nBlynk ESP32 using EEPROM connected. Board Name : " + Blynk.getBoardName());
    Serial.printf("EEPROM size = %d bytes, EEPROM start address = %d / 0x%X\n", EEPROM_SIZE, EEPROM_START, EEPROM_START);
#endif
  }
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

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

2. File [defines.h](examples/ESP32WM_Config/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_PRINT Serial

#define DOUBLERESETDETECTOR_DEBUG     false
#define BLYNK_WM_DEBUG                0

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    false => using EEPROM for configuration data in WiFiManager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in WiFiManager
// Be sure to define USE_SPIFFS before #include <BlynkSimpleEsp8266_WM.h>

#define USE_SPIFFS                  true
//#define USE_SPIFFS                  false

#if (!USE_SPIFFS)
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

3. File [Credentials.h](examples/ESP32WM_Config/Credentials.h)

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


#endif    //Credentials_h
```


4. File [dynamicParams.h](examples/ESP32WM_Config/dynamicParams.h)

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
14. Permit to input special chars such as ***%*** and ***#*** into data fields.
15. Add Dynamic Parameters with checksum
16. Default Credentials and dynamic parameters
17. DoubleDetectDetector to force Config Portal when double reset is detected within predetermined time, default 10s.
18. Configurable Config Portal Title
19. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
20. Add LittleFS support to ESP8266 as SPIFFS deprecated since ESP8266 core 2.7.1.


### Releases v1.0.15

1. Update to use LittleFS for ESP8266 core 2.7.1+.
2. Fix SSL connection bug.
3. Fix dynamicParams loading bug in v1.0.14. 
4. Add [Blynk_WM_Template example](examples/Blynk_WM_Template) contributed by [thorathome](https://github.com/thorathome).

Again thanks to [thorathome in GitHub](https://github.com/thorathome) and [thorathome in Blynk](https://community.blynk.cc/u/thorathome) for testing, bug finding, feature adding, README rewriting, collaborating, etc..

### Releases v1.0.14

1. Fix dynamicParams bug in v1.0.13. Again thanks to [thorathome in GitHub](https://github.com/thorathome) and [thorathome in Blynk](https://community.blynk.cc/u/thorathome)

### Releases v1.0.13

1. Optional default ***Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal*** to use or change instead of manually input.
2. ***DoubleDetectDetector*** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
3. Configurable ***Config Portal Title*** to be either Hostname, BoardName or default undistinguishable names.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

### Releases v1.0.12

1. Fix severe bug in v1.0.11

### Releases v1.0.11

#### Severe connecting bug. Don't use

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.

### Releases v1.0.10

***Why this version***

1. WiFi Password max length is 63, according to WPA2 standard.
2. Permit to input special chars such as ***~, !, @, #, $, %, ^, &, *, (, ), _, -, space,etc"*** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

### Releases v1.0.9

1. Enhance Config Portal GUI. Not using the terrible GUI of the original version. Finally had some time to get this out of the bucket list.

### Releases v1.0.8

1. Fix [AP-staying-open bug](https://github.com/khoih-prog/Blynk_WM/issues/2). Thanks to [chriskio](https://github.com/chriskio) to report.
2. Add clearConfigData().

### Releases v1.0.7

***Why this version***

1. Add checksum for more reliable data
2. Add MultiWiFi feature to enable reconnect to the best / available WiFi AP.
3. Add MultiBlynk feature to enable reconnect to the best / available Blynk Server.

### Releases v1.0.6

Optimize, fix ESP32 EEPROM size to 2K from 4K, shorten code size, add functions, use dynamically allocated Config Portal WebServer.

### Releases v1.0.5

Normally, the `default Portal IP (192.168.4.1)`, SSID and PW as well as the `dynamically allocated` board's IP address are good enough.
In special cases where there is conflict, if static IP is required or bad router's DNS settings, you can use the new features to force the configurable IP addresses. ***But please use with care to avoid potential issues.***

***New in this version***

Add new features to enable :

1. configuring Portal Static IP address, Name and Password.
2. configuring Static IP address, Gateway, Subnet Mask and 2 DNS Servers IP addresses.

### Releases v1.0.4

I'm really fed-up with the unfriendly, confusing and cryptic DHCP hostnames such as `ESP_XXXXXX`, `espressif` using ChipID. Thanks to an issue opened in library [ESP_WiFiManager](https://github.com/khoih-prog/ESP_WiFiManager), I decided to add this option to have built-in, yet configurable DHCP hostname to these libraries.

Now you can easily specify and have the friendly, identifiable, RFC-952-conformed DHCP hostnames associated with your boards, such as `SmartFarm-1`, `Irrigation`, `Master-Controller`, etc. You'll be happier to have a look at your WiFi Router DHCP list.

***New in this version***

1. Add configurable personalized RFC-952 DHCP hostname and setHostname()

2. Modify examples to use new feature

### Releases v1.0.3

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

### Contributions and thanks

1. Thanks to [chriskio](https://github.com/chriskio) to report [AP-staying-open bug](https://github.com/khoih-prog/Blynk_WM/issues/2). 
2. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as ***%*** and ***#*** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
3. Thanks to [thorathome in GitHub](https://github.com/thorathome) and [thorathome in Blynk](https://community.blynk.cc/u/thorathome) to test, find bug, suggest and encourage to add those new features in v1.0.13, such as Default Credentials/Dynamic Parms, Configurable Config Portal Title, DRD. The powerful [Blynk_WM_Template](examples/Blynk_WM_Template) is written by [thorathome](https://github.com/thorathome) and is included in the examples with his permission. See [WM Config Portal using BlynkSimpleEsp32/8266_WM.h](https://community.blynk.cc/t/wm-config-portal-using-blynksimpleesp32-8266-wm-h/45402).

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2020- Khoi Hoang

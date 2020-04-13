## Blynk_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager)

I'm inspired by [`EasyBlynk8266`](https://github.com/Barbayar/EasyBlynk8266)
This is a Blynk and WiFiManager Library for configuring/auto(re)connecting ESP8266/ESP32 modules to the best or available MultiWiFi APs and MultiBlynk servers at runtime. Connection is with or without SSL. Configuration data to be saved in either SPIFFS or EEPROM.
 
To help you to eliminate `hardcoding` your Wifi and Blynk credentials for ESP8266 and ESP32 (with / wwithout SSL), and updating/reflashing every time when you need to change them.

### Releases v1.0.12

1. Fix severe bug in v1.0.11

### Releases v1.0.11

#### Severe connecting bug. Don't use

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.

### Releases v1.0.10

1. WiFi Password max length is 63, according to WPA2 standard
2. Permit to input special chars such as ***%*** and ***#*** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

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
4. [`ESP8266 core 2.6.3 or later` for Arduino](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards

### Installation

The suggested way to install is to:

1. Navigate to [Blynk_WM](https://github.com/khoih-prog/Blynk_WM) page.
2. Download the latest release `Blynk_WM-master.zip`.
3. Extract the zip file to `Blynk_WM-master` directory 
4. Copy whole `Blynk_WM-master/src` folder to Arduino libraries' `src` directory such as `~/Arduino/libraries/Blynk/src`.

The file BlynkSimpleEsp8266_WM.h, BlynkSimpleEsp8266_SSL_WM.h, BlynkSimpleEsp32_WM.h and BlynkSimpleEsp32_SSL_WM.h must be placed in Blynk libraries `src` directory (normally `~/Arduino/libraries/Blynk/src`)

Another way is to use `Arduino Library Manager`. 
1. Search for `Blynk_WiFiManager`, then select / install the latest version. 
2. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_WiFiManager.svg?)](https://www.ardu-badge.com/Blynk_WiFiManager) for more detailed instructions.
3. Then move the 2 files `BlynkSimpleEsp8266_SSL_WM.h` and `BlynkSimpleEsp32_SSL_WM.h` from directory `~/Arduino/libraries/Blynk_WiFiManager/src` into Blynk libraries `src` directory (normally `~/Arduino/libraries/Blynk/src`)

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
to use EEPROM ( 312 bytes from address EEPROM_START ) to save your configuration data.
EEPROM_SIZE can be specified from 512 to 4096 bytes. See examples [ESP32WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP32WM_Config) and [ESP8266WM_Config](https://github.com/khoih-prog/Blynk_WM/tree/master/examples/ESP8266WM_Config).


```
// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

```

To use personalized Config Portal AP SSID and Password, as well as IP Address, e.g. call :

```
// Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP8266", "TestPortalPass");
  // Set config portal IP address
  Blynk.setConfigPortalIP(IPAddress(192, 168, 200, 1));
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
9. [ESP82WM_Config](examples/ESP8266WM_Config)


## So, how it works?
If it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an AP with default name `ESP_xxxxxx` and password `MyESP_xxxxxx` or configurable name amd password you specified. The AP IP address is default at `192.168.4.1` or configured IP (e.g. `192.168.200.1`).

First, connect your (PC, Laptop, Tablet, phone, etc.) WiFi to Config Portal AP, then enter the WiFi password :

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/PortalAuth.jpg">
</p>

After you connected, please, go to http://192.168.4.1 or the configured AP IP. The Config Portal screen will appear:

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Main.png">
</p>

Enter your WiFi and Blynk Credentials:

### Important notes
1. Now you can use hash tag ***#*** or ***%*** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in v1.0.10 to permit input special chars such as ***%*** and ***#*** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords, BlynkServers and Tokens must be input (or to make them different from ***nothing***). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.

<p align="center">
    <img src="https://github.com/khoih-prog/Blynk_WM/blob/master/pics/ConfigPortal.png">
</p>

Then click `Save`. The system will auto-restart. You will see the board's built-in LED turned OFF. That means, it's already connected to your Blynk server successfully.

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```
#define USE_DYNAMIC_PARAMETERS     true

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp8266_WM.h> and <BlynkSimpleEsp8266_SSL_WM.h>
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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

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

The following is the sample terminal output when running example [ESP8266WM_Config](examples/ESP8266WM_Config)

1. No Config Data => Config Portal

```
Starting ...
[150] Hostname=ESP8266-WM-Config
[151] CCSum=0x58e0,RCSum=0xffffffff
[151] CrCCsum=44880,CrRCsum=-1
[151] InitEEPROM,sz=4096,Datasz=556
[151] pdata=blank,len=34
[153] pdata=blank,len=6
[155] pdata=blank,len=34
[158] pdata=blank,len=34
[160] pdata=blank,len=34
[162] pdata=blank,len=34
[164] CrCCSum=3120
[209] bg: No configdat. Stay forever in config portal
[401] 
stConf:SSID=TestPortal-ESP8266,PW=TestPortalPass
[401] IP=192.168.200.1,ch=1
FYour stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
RFRFRFRFRFRFRFRF
[523347] h:UpdEEPROM
[523347] SaveEEPROM,sz=4096,CSum=0x32c1
[523360] CrCCSum=6078
[523406] h:Rst
```

2. Input valid credentials => reboot

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

[4431] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[5125] Ready (ping: 5ms).
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
```

3. Testing WiFi and Blynk Server lost to verify auto-reconnection

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

You can see that the system automatically detect and connect to the best or avaiable WiFi APs and/or Blynk Servers, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, this `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
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

## Example
Please take a look at examples, as well.

```cpp
#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

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
#define EEPROM_START  0
#endif

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5
// Those above #define's must be placed before #include <BlynkSimpleEsp8266_WM.h>

//#define USE_SSL   true
#define USE_SSL   false

#if USE_SSL
#include <BlynkSimpleEsp8266_SSL_WM.h>
#else
#include <BlynkSimpleEsp8266_WM.h>
#endif

#define USE_DYNAMIC_PARAMETERS     true

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkSimpleEsp8266_WM.h> and <BlynkSimpleEsp8266_SSL_WM.h>
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
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

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

  if (Blynk.connected())
  {
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
    set_led(LOW);
    led_ticker.once_ms(111, set_led, (byte) HIGH);
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
  // Debug console
  Serial.begin(115200);
  while (!Serial);
  
  pinMode(PIN_LED, OUTPUT);

  Serial.println("\nStarting ...");

  dht.begin();

  // From v1.0.5
  // Set config portal SSID and Password
  Blynk.setConfigPortal("TestPortal-ESP8266", "TestPortalPass");
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
  Blynk.begin("ESP8266-WM-Config");

  timer.setInterval(60 * 1000, readAndSendData);

  if (Blynk.connected())
  {
#if USE_SPIFFS
    Serial.println("\nBlynk ESP8288 using SPIFFS connected. Board Name : " + Blynk.getBoardName());
#else
    {
      Serial.println("\nBlynk ESP8288 using EEPROM connected. Board Name : " + Blynk.getBoardName());
      Serial.printf("EEPROM size = %d bytes, EEPROM start address = %d / 0x%X\n", EEPROM_SIZE, EEPROM_START, EEPROM_START);
    }
#endif
  }
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("Your stored Credentials :");

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

### Releases v1.0.12

1. Fix severe bug in v1.0.11

### Releases v1.0.11

#### Severe connecting bug. Don't use

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, or SPIFFS***.

### Releases v1.0.10

***Why this version***

1. WiFi Password max length is 63, according to WPA2 standard.
2. Permit to input special chars such as ***%*** and ***#*** into data fields. Thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix.

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

Now you can easily specify and have the friendly, identifiable, RFC-952-conformed DHP hostnames associated with your boards, such as `SmartFarm-1`, `Irrigation`, `Master-Controller`, etc. You'll be happier to have a look at your WiFi Router DHCP list.

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

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2019- Khoi Hoang

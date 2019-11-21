/**
 * Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
 * configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
 * Licensed under MIT license
 * Version: 1.0.2
 * Original Blynk Library author:
 * @file       BlynkSimpleEsp32.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Oct 2016
 * @brief
 *
 */

#ifndef BlynkSimpleEsp32_WM_h
#define BlynkSimpleEsp32_WM_h

#ifndef ESP32
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define BLYNK_SEND_ATOMIC

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <WiFi.h>

#include <WebServer.h>

//default to use EEPROM, otherwise, use SPIFFS
#if USE_SPIFFS
#include <FS.h>
#include "SPIFFS.h"
#else
#include <EEPROM.h>
#endif

#include <esp_wifi.h>
#define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    6
struct Configuration 
{
    char header         [16];
    char wifi_ssid      [32];
    char wifi_passphrase[32];
    char blynk_server   [32];
    int  blynk_port;
    char blynk_token    [36];
    char board_name     [24];
};

String root_html_template = " \
<!DOCTYPE html> \
<meta name=\"robots\" content=\"noindex\"> \
<html> \
<head> \
  <meta charset=\"utf-8\"> \
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
  <title>BlynkSimpleEsp32_WM</title> \
</head> \
<body> \
  <div align=\"center\"> \
    <table> \
      <tbody> \
        <tr> \
          <th colspan=\"2\">WiFi</th> \
        </tr> \
        <tr> \
          <td>SSID</td> \
          <td><input type=\"text\" value=\"[[wifi_ssid]]\" size=20 maxlength=64 id=\"wifi_ssid\"></td> \
        </tr> \
        <tr> \
          <td>Passphrase</td> \
          <td><input type=\"text\" value=\"[[wifi_passphrase]]\" size=20 maxlength=64 id=\"wifi_passphrase\"></td> \
        </tr> \
        <tr> \
          <th colspan=\"2\">Blynk</th> \
        </tr> \
        <tr> \
          <td>Server</td> \
          <td><input type=\"text\" value=\"[[blynk_server]]\" size=20 maxlength=64 id=\"blynk_server\"></td> \
        </tr> \
        <tr> \
          <td>Port</td> \
          <td><input type=\"text\" value=\"[[blynk_port]]\" id=\"blynk_port\"></td> \
        </tr> \
        <tr> \
          <td>Token</td> \
          <td><input type=\"text\" value=\"[[blynk_token]]\" size=20 maxlength=64 id=\"blynk_token\"></td> \
        </tr> \
        <tr> \
          <th colspan=\"2\">Hardware</th> \
        </tr> \
        <tr> \
          <td>Name</td> \
          <td><input type=\"text\" value=\"[[board_name]]\" size=20 maxlength=32 id=\"board_name\"></td> \
        </tr> \
        <tr> \
          <td colspan=\"2\" align=\"center\"> \
            <button onclick=\"save()\">Save</button> \
          </td> \
        </tr> \
      </tbody> \
    </table> \
  </div> \
<script id=\"jsbin-javascript\"> \
function updateValue(key, value) { \
  var request = new XMLHttpRequest(); \
  var url = '/?key=' + key + '&value=' + value; \
  console.log('calling ' + url + '...'); \
  request.open('GET', url, false); \
  request.send(null); \
} \
function save() { \
  updateValue('wifi_ssid', document.getElementById('wifi_ssid').value); \
  updateValue('wifi_passphrase', document.getElementById('wifi_passphrase').value); \
  updateValue('blynk_server', document.getElementById('blynk_server').value); \
  updateValue('blynk_port', document.getElementById('blynk_port').value); \
  updateValue('blynk_token', document.getElementById('blynk_token').value); \
  updateValue('board_name', document.getElementById('board_name').value); \
  alert('Updated Configurations. Resetting board'); \
} \
</script> \
</body> \
</html>";
#define BLYNK_SERVER_HARDWARE_PORT    8080

class BlynkWifi
    : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
public:
    BlynkWifi(BlynkArduinoClient& transp)
        : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG2(BLYNK_F("Connecting to "), ssid);
        WiFi.mode(WIFI_STA);
        if (pass && strlen(pass)) {
            WiFi.begin(ssid, pass);
        } else {
            WiFi.begin(ssid);
        }
        while (WiFi.status() != WL_CONNECTED) {
            BlynkDelay(500);
        }
        BLYNK_LOG1(BLYNK_F("Connected to WiFi"));

        IPAddress myip = WiFi.localIP();
        BLYNK_LOG_IP("IP: ", myip);
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
        config(auth, domain, port);
        while(this->connect() != true) {}
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
        config(auth, ip, port);
        while(this->connect() != true) {}
    }
   
    #ifndef LED_BUILTIN
    #define LED_BUILTIN       2         // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
    #endif
        
    void begin(void) 
    {
        #define TIMEOUT_CONNECT_WIFI			30000

        //Turn OFF
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
               
        if (getConfigData())
        {
          hadConfigData = true;

          Base::begin(BlynkESP32_WM_config.blynk_token);
          this->conn.begin(BlynkESP32_WM_config.blynk_server, BlynkESP32_WM_config.blynk_port);

          if (connectToWifi(TIMEOUT_CONNECT_WIFI)) 
          {
            BLYNK_LOG1(BLYNK_F("begin: WiFi connected. Try connecting to Blynk"));
            
            int i = 0;
            while ( (i++ < 10) && !this->connect() )
            {
            }
            
            if  (this->connected())
            {
              BLYNK_LOG1(BLYNK_F("begin: WiFi and Blynk connected"));
            }
            else 
            {
              BLYNK_LOG1(BLYNK_F("begin: WiFi connected but Bynk not connected"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
            }
          } 
          else 
          {
              BLYNK_LOG1(BLYNK_F("begin: Fail to connect WiFi and Blynk"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
          }
        }
        else
        {
            BLYNK_LOG1(BLYNK_F("begin: No stored config data. Will forever stay in config mode until getting data"));
            // failed to connect to Blynk server, will start configuration mode
            hadConfigData = false;
            startConfigurationMode();                  
        }        
    }    

#ifndef TIMEOUT_RECONNECT_WIFI
  #define TIMEOUT_RECONNECT_WIFI   10000L
#else
  // Force range of user-defined TIMEOUT_RECONNECT_WIFI between 10-60s
  #if (TIMEOUT_RECONNECT_WIFI < 10000L)
    #warning TIMEOUT_RECONNECT_WIFI too low. Reseting to 10000
    #undef TIMEOUT_RECONNECT_WIFI
    #define TIMEOUT_RECONNECT_WIFI   10000L
  #elif (TIMEOUT_RECONNECT_WIFI > 60000L)
    #warning TIMEOUT_RECONNECT_WIFI too high. Reseting to 60000
    #undef TIMEOUT_RECONNECT_WIFI
    #define TIMEOUT_RECONNECT_WIFI   60000L
  #endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
  #define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
  // Force range of user-defined TIMES_BEFORE_RESET between 2-100
  #if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
  #elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Reseting to 100
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
  #endif
#endif
   
    void run()
    {
      static int retryTimes = 0;
      
      // Lost connection in running. Give chance to reconfig.
      if ( WiFi.status() != WL_CONNECTED || !connected() )
      {   
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi / Blynk. 
        // But if user has connected to configWeb, stay there until done, then reset hardware
		    if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
		    {
		      retryTimes = 0;
			    server.handleClient();		
			    return;
		    }
		    else
		    {
		      #if RESET_IF_CONFIG_TIMEOUT
		      // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
		      // to permit user another chance to config.
		      if ( configuration_mode && (configTimeout != 0) )
		      {	        
		        if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
		        {
		          BLYNK_LOG2(BLYNK_F("run: WiFi lost but config Timeout. Try connecting WiFi and Blynk. RetryTimes : "), retryTimes);
		        }
		        else
		        {
              ESP.restart();
		        }		        
		      }
		      #endif
		      		    
			    // Not in config mode, try reconnecting before force to config mode
			    if ( WiFi.status() != WL_CONNECTED )
			    {
				    BLYNK_LOG1(BLYNK_F("run: WiFi lost. Try reconnecting WiFi and Blynk"));
				    if (connectToWifi(TIMEOUT_RECONNECT_WIFI)) 
				    {
				      // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LOW);

				      BLYNK_LOG1(BLYNK_F("run: WiFi reconnected. Trying connect to Blynk"));
				      
				      if (connect())
				      {
					      BLYNK_LOG1(BLYNK_F("run: WiFi and Blynk reconnected"));
					    }
				    }
			    }
			    else
			    {
				    BLYNK_LOG1(BLYNK_F("run: Blynk lost. Try connecting Blynk"));
				    if (connect()) 
				    {
				      // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LOW);
              
					    BLYNK_LOG1(BLYNK_F("run: Blynk reconnected"));
				    }
			    }
					
			    //BLYNK_LOG1(BLYNK_F("run: Lost connection => configMode"));
			    //startConfigurationMode();
        }
      }
      else if (configuration_mode)
      {
      	configuration_mode = false;
      	BLYNK_LOG1(BLYNK_F("run: got WiFi/Blynk back, great"));
      	// Turn the LED_BUILTIN OFF when out of configuration mode. ESP32 LED_BUILDIN is correct polarity, LOW to turn OFF
        digitalWrite(LED_BUILTIN, LOW);      	
      }

      if (connected())
      {
        Base::run();
      }
    }
        
    String getBoardName()
    {
      return (String(BlynkESP32_WM_config.board_name));
    }
    
        
private:
    WebServer server;
    bool configuration_mode = false;
    struct Configuration BlynkESP32_WM_config;
    
    unsigned long configTimeout;
    bool hadConfigData;    

#define BOARD_TYPE      "ESP32"

#define NO_CONFIG       "nothing"
    
#if USE_SPIFFS     

    #define  CONFIG_FILENAME         BLYNK_F("/wm_config.dat")
    #define  CONFIG_FILENAME_BACKUP  BLYNK_F("/wm_config.bak")

    void loadConfigData(void)
    {
      File file = SPIFFS.open(CONFIG_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("Loading config file..."));
      
      if (!file) 
      {
        BLYNK_LOG1(BLYNK_F(" failed"));
        
        // Trying open redundant config file
        file = SPIFFS.open(CONFIG_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("Loading backup config file...")); 
        
        if (!file)
        {
          BLYNK_LOG1(BLYNK_F(" also failed"));
          return;
        }
      }
        
      file.readBytes((char *) &BlynkESP32_WM_config, sizeof(BlynkESP32_WM_config));
      
      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();    
    }

    void saveConfigData(void)
    {
      File file = SPIFFS.open(CONFIG_FILENAME, "w");
      BLYNK_LOG1(BLYNK_F("Saving config file..."));
      
      if (file) 
      {
        file.write((uint8_t*) &BlynkESP32_WM_config, sizeof(BlynkESP32_WM_config));  
        file.close();     
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F(" failed"));        
      }  
      
      // Trying open redundant Auth file
      file = SPIFFS.open(CONFIG_FILENAME_BACKUP, "w");
      BLYNK_LOG1(BLYNK_F("Saving backup config file...")); 
      
      if (file)
      {
        file.write((uint8_t *) &BlynkESP32_WM_config, sizeof(BlynkESP32_WM_config));
        file.close();  
        BLYNK_LOG1(BLYNK_F("OK"));      
      }
      else
      {
        BLYNK_LOG1(BLYNK_F(" failed"));       
      }              
    }
    
    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode 
    bool getConfigData()
    {     
      if (!SPIFFS.begin()) 
      {
        BLYNK_LOG1(BLYNK_F("SPIFFS failed!. Please use EEPROM."));
        return false;
      }
      
      if ( SPIFFS.exists(CONFIG_FILENAME) || SPIFFS.exists(CONFIG_FILENAME_BACKUP) )
      { 
        // if config file exists, load
        loadConfigData();
      }

      if (strncmp(BlynkESP32_WM_config.header, BOARD_TYPE, strlen(BOARD_TYPE)) != 0) 
      {
          memset(&BlynkESP32_WM_config, 0, sizeof(BlynkESP32_WM_config));
                                   
          BLYNK_LOG2(BLYNK_F("Init new config file, size = "), sizeof(BlynkESP32_WM_config));          
          // doesn't have any configuration
          strcpy(BlynkESP32_WM_config.header,           BOARD_TYPE);
          strcpy(BlynkESP32_WM_config.wifi_ssid,        NO_CONFIG);
          strcpy(BlynkESP32_WM_config.wifi_passphrase,  NO_CONFIG);
          strcpy(BlynkESP32_WM_config.blynk_server,     NO_CONFIG);
          BlynkESP32_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(BlynkESP32_WM_config.blynk_token,      NO_CONFIG);
          strcpy(BlynkESP32_WM_config.board_name,       NO_CONFIG);
          
          saveConfigData();
          
          return false;        
      }
      else if ( !strncmp(BlynkESP32_WM_config.wifi_ssid,        NO_CONFIG, strlen(NO_CONFIG))   ||
                !strncmp(BlynkESP32_WM_config.wifi_passphrase,  NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(BlynkESP32_WM_config.blynk_server,     NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(BlynkESP32_WM_config.blynk_token,      NO_CONFIG, strlen(NO_CONFIG) ) ) 
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }  
      else
      {
        BLYNK_LOG6(BLYNK_F("Header = "), BlynkESP32_WM_config.header, BLYNK_F(", SSID = "), BlynkESP32_WM_config.wifi_ssid, 
                   BLYNK_F(", PW = "),     BlynkESP32_WM_config.wifi_passphrase);
        BLYNK_LOG6(BLYNK_F("Server = "), BlynkESP32_WM_config.blynk_server, BLYNK_F(", Port = "), BlynkESP32_WM_config.blynk_port, 
                   BLYNK_F(", Token = "),  BlynkESP32_WM_config.blynk_token);
        BLYNK_LOG2(BLYNK_F("Board Name = "), BlynkESP32_WM_config.board_name);               
      }
      
      return true;
    }
     

#else

#define  CONFIG_DATA_SIZE     172

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     512
#else
  #if (EEPROM_SIZE > 4096)
    #warning EEPROM_SIZE must be <= 4096. Reset to 4096
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     4096
  #endif
  #if (EEPROM_SIZE < CONFIG_DATA_SIZE)
    #warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     512
  #endif  
#endif  

#ifndef EEPROM_START
  #define EEPROM_START     0
#else
  #if (EEPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif  

    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode 
    bool getConfigData()
    {      
      EEPROM.begin(EEPROM_SIZE);
      EEPROM.get(EEPROM_START, BlynkESP32_WM_config);

      if (strncmp(BlynkESP32_WM_config.header, BOARD_TYPE, strlen(BOARD_TYPE)) != 0) 
      {
          memset(&BlynkESP32_WM_config, 0, sizeof(BlynkESP32_WM_config));
                                   
          BLYNK_LOG2(BLYNK_F("Init new EEPROM, size = "), EEPROM_SIZE /*EEPROM.length()*/);          
          // doesn't have any configuration
          strcpy(BlynkESP32_WM_config.header,           BOARD_TYPE);
          strcpy(BlynkESP32_WM_config.wifi_ssid,        NO_CONFIG);
          strcpy(BlynkESP32_WM_config.wifi_passphrase,  NO_CONFIG);
          strcpy(BlynkESP32_WM_config.blynk_server,     NO_CONFIG);
          BlynkESP32_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(BlynkESP32_WM_config.blynk_token,      NO_CONFIG);
          strcpy(BlynkESP32_WM_config.board_name,       NO_CONFIG);
          
          EEPROM.put(EEPROM_START, BlynkESP32_WM_config);
          EEPROM.commit();
          
          return false;
      }
      else if ( !strncmp(BlynkESP32_WM_config.wifi_ssid,        NO_CONFIG, strlen(NO_CONFIG))   ||
                !strncmp(BlynkESP32_WM_config.wifi_passphrase,  NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(BlynkESP32_WM_config.blynk_server,     NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(BlynkESP32_WM_config.blynk_token,      NO_CONFIG, strlen(NO_CONFIG) ) ) 
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }  
      else
      {
        BLYNK_LOG6(BLYNK_F("Header = "), BlynkESP32_WM_config.header, BLYNK_F(", SSID = "), BlynkESP32_WM_config.wifi_ssid, 
                   BLYNK_F(", PW = "),     BlynkESP32_WM_config.wifi_passphrase);
        BLYNK_LOG6(BLYNK_F("Server = "), BlynkESP32_WM_config.blynk_server, BLYNK_F(", Port = "), BlynkESP32_WM_config.blynk_port, 
                   BLYNK_F(", Token = "),  BlynkESP32_WM_config.blynk_token);
        BLYNK_LOG2(BLYNK_F("Board Name = "), BlynkESP32_WM_config.board_name);               
      }
      
      return true;
    }      
    
    void saveConfigData()
    {      
      EEPROM.put(EEPROM_START, BlynkESP32_WM_config);
      EEPROM.commit();
    }
    
#endif    

    boolean connectToWifi(int timeout)
    {
      int sleep_time = 250;

      WiFi.mode(WIFI_STA);

	    BLYNK_LOG1(BLYNK_F("connectToWifi: start"));
	
      if (BlynkESP32_WM_config.wifi_passphrase && strlen(BlynkESP32_WM_config.wifi_passphrase))
      {
          WiFi.begin(BlynkESP32_WM_config.wifi_ssid, BlynkESP32_WM_config.wifi_passphrase);
      } 
      else 
      {
          WiFi.begin(BlynkESP32_WM_config.wifi_ssid);
      }

      while (WiFi.status() != WL_CONNECTED && 0 < timeout) 
      {
          delay(sleep_time);
          timeout -= sleep_time;
      }

	    if (WiFi.status() == WL_CONNECTED)
	    {
		    BLYNK_LOG1(BLYNK_F("connectToWifi: connected OK"));
        IPAddress myip = WiFi.localIP();
        BLYNK_LOG_IP("IP: ", myip);		    
		  }
	    else
	    {
		    BLYNK_LOG1(BLYNK_F("connectToWifi: connected failed"));
		  }
	
      return WiFi.status() == WL_CONNECTED;    
    }

    
    void handleRequest()
    {
      String key = server.arg("key");
      String value = server.arg("value");
      
      static int number_items_Updated = 0;

      if (key == "" && value == "") 
      {
          String result = root_html_template;
          
          BLYNK_LOG1(BLYNK_F("handleRequest: replacing result"));
          
          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          result.replace("[[wifi_ssid]]",       BlynkESP32_WM_config.wifi_ssid);
          result.replace("[[wifi_passphrase]]", BlynkESP32_WM_config.wifi_passphrase);
          result.replace("[[blynk_server]]",    BlynkESP32_WM_config.blynk_server);
          result.replace("[[blynk_port]]",      String(BlynkESP32_WM_config.blynk_port));
          result.replace("[[blynk_token]]",     BlynkESP32_WM_config.blynk_token);
          result.replace("[[board_name]]",      BlynkESP32_WM_config.board_name);

          server.send(200, "text/html", result);

          return;
      }
     
      if (number_items_Updated == 0)
      {
        memset(&BlynkESP32_WM_config, 0, sizeof(BlynkESP32_WM_config));
        strcpy(BlynkESP32_WM_config.header, BOARD_TYPE);
      }
      
      if (key == "wifi_ssid")
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(BlynkESP32_WM_config.wifi_ssid) -1)
            strcpy(BlynkESP32_WM_config.wifi_ssid, value.c_str());
          else
            strncpy(BlynkESP32_WM_config.wifi_ssid, value.c_str(), sizeof(BlynkESP32_WM_config.wifi_ssid) -1);    
      }
      else if (key == "wifi_passphrase") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(BlynkESP32_WM_config.wifi_passphrase) -1)
            strcpy(BlynkESP32_WM_config.wifi_passphrase, value.c_str());
          else
            strncpy(BlynkESP32_WM_config.wifi_passphrase, value.c_str(), sizeof(BlynkESP32_WM_config.wifi_passphrase) -1);    
      }

      else if (key == "blynk_server") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(BlynkESP32_WM_config.blynk_server) -1)
            strcpy(BlynkESP32_WM_config.blynk_server, value.c_str());
          else
            strncpy(BlynkESP32_WM_config.blynk_server, value.c_str(), sizeof(BlynkESP32_WM_config.blynk_server) -1);      
      }
      else if (key == "blynk_port") 
      {
          number_items_Updated++;
          BlynkESP32_WM_config.blynk_port = value.toInt();
      }
      else if (key == "blynk_token") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(BlynkESP32_WM_config.blynk_token) -1)
            strcpy(BlynkESP32_WM_config.blynk_token, value.c_str());
          else
            strncpy(BlynkESP32_WM_config.blynk_token, value.c_str(), sizeof(BlynkESP32_WM_config.blynk_token) -1);    
      }
      else if (key == "board_name") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(BlynkESP32_WM_config.board_name) -1)
            strcpy(BlynkESP32_WM_config.board_name, value.c_str());
          else
            strncpy(BlynkESP32_WM_config.board_name, value.c_str(), sizeof(BlynkESP32_WM_config.board_name) -1);  
      }
      
      server.send(200, "text/html", "OK");
      
      if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
      {
        #if USE_SPIFFS     
          BLYNK_LOG2(BLYNK_F("handleRequest: Updating data to SPIFFS file "), CONFIG_FILENAME);
        #else
          BLYNK_LOG1(BLYNK_F("handleRequest: Updating data to EEPROM"));
        #endif

        saveConfigData();

        BLYNK_LOG1(BLYNK_F("handleRequest: Resetting"));
        
        // Delay then reset the ESP8266 after save data
        delay(1000);
        ESP.restart();
      }
    
    }
        
    void startConfigurationMode()
    {
      #define CONFIG_TIMEOUT			60000L
      
      // turn the LED_BUILTIN ON to tell us we are in configuration mode.
      digitalWrite(LED_BUILTIN, HIGH);      
      
      String chipID = String(ESP_getChipId(), HEX);
      chipID.toUpperCase();
      
	    String ssid = "ESP_" + chipID;

	    String pass = "MyESP_" + chipID;
	    
	    BLYNK_LOG4(BLYNK_F("startConfigurationMode with SSID = "), ssid, BLYNK_F(" and PW = "), pass);
	
      IPAddress apIP(192, 168, 4, 1);

      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid.c_str(), pass.c_str());
      
      delay(100); // ref: https://github.com/espressif/arduino-esp32/issues/985#issuecomment-359157428
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      
      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
      server.on("/", [this](){ handleRequest(); });

      server.begin();
      
      // If there is no saved config Data, stay in config mode forever until having config Data.
      if (hadConfigData)      
        configTimeout = millis() + CONFIG_TIMEOUT;
      else
        configTimeout = 0;      
       
      configuration_mode = true;    
    }    
};

static WiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif

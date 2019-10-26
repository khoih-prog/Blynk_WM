/**
 * @file       BlynkSimpleEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSimpleEsp8266_WM_h
#define BlynkSimpleEsp8266_WM_h

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#include <version.h>

#if ESP_SDK_VERSION_NUMBER < 0x020200
#error Please update your ESP8266 Arduino Core
#endif

#include <ESP8266WiFi.h>

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>

#include <ESP8266WebServer.h>

//default to use EEPROM, otherwise, use SPIFFS
#if USE_SPIFFS
#include <FS.h>
#else
#include <EEPROM.h>
#endif


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
    char board_name     [16];
};

String root_html_template = " \
<!DOCTYPE html> \
<meta name=\"robots\" content=\"noindex\"> \
<html> \
<head> \
  <meta charset=\"utf-8\"> \
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
  <title>BlynkSimpleEsp8266_WM</title> \
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
    {

    }
    
    void connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG2(BLYNK_F("Connecting to "), ssid);
        WiFi.mode(WIFI_STA);
        if (WiFi.status() != WL_CONNECTED) 
        {
            if (pass && strlen(pass)) 
            {
                WiFi.begin(ssid, pass);
            } else 
            {
                WiFi.begin(ssid);
            }
        }
        while (WiFi.status() != WL_CONNECTED) 
        {
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
    
 
    void begin(void) 
    {
        #define TIMEOUT_CONNECT_WIFI			30000
               
        getConfigData();

        Base::begin(Blynk8266_WM_config.blynk_token);
        this->conn.begin(Blynk8266_WM_config.blynk_server, Blynk8266_WM_config.blynk_port);

        if (connectToWifi(TIMEOUT_CONNECT_WIFI)) 
        {
          BLYNK_LOG1(BLYNK_F("begin: WiFi connected. Try connecting to Blynk"));
          
          int i = 0;
          while ( (i++ < 10) && !this->connect() )
          {
          }
          
          if  (connected())
          {
            BLYNK_LOG1(BLYNK_F("begin: WiFi and Blynk connected"));
          }
          else 
          {
            BLYNK_LOG1(BLYNK_F("begin: WiFi connected but Bynk not connected"));
            // failed to connect to Blynk server, will start configuration mode
            // turn the LED_BUILTIN ON to tell us we are in configuration mode.
            digitalWrite(LED_BUILTIN, LOW);
            startConfigurationMode();
          }
        } 
        else 
        {
            BLYNK_LOG1(BLYNK_F("begin: Fail to connect WiFi and Blynk"));
            // failed to connect to Blynk server, will start configuration mode
            // turn the LED_BUILTIN ON to tell us we are in configuration mode.
            digitalWrite(LED_BUILTIN, LOW);            
            startConfigurationMode();
        }   
    }    
   
    void run()
    {
      #define TIMEOUT_RECONNECT_WIFI			10000
      
      // Lost connection in running. Give chance to reconfig.
      if ( WiFi.status() != WL_CONNECTED || !connected() )
      {   
		    if (configuration_mode)
		    {
			    server.handleClient();		
			    return;
		    }
		    else
		    {
			    // Not in config mode, try reconnecting before force to config mode
			    if ( WiFi.status() != WL_CONNECTED )
			    {
				    BLYNK_LOG1(BLYNK_F("run: WiFi lost. Try reconnecting WiFi and Blynk"));
				    if (connectToWifi(TIMEOUT_RECONNECT_WIFI)) 
				    {
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
      	// turn the LED_BUILTIN OFF to tell us we exit configuration mode.
        digitalWrite(LED_BUILTIN, HIGH);
      }

      if (connected())
      {
        Base::run();
      }
    }
    
    String getBoardName()
    {
      return (String(Blynk8266_WM_config.board_name));
    }
    
private:
    ESP8266WebServer server;
    boolean configuration_mode = false;
    struct Configuration Blynk8266_WM_config;
    
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
        
      file.readBytes((char*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));
      
      BLYNK_LOG1(BLYNK_F("OK"));
      file.close();    
    }

    void saveConfigData(void)
    {
      File file = SPIFFS.open(CONFIG_FILENAME, "w");
      BLYNK_LOG1(BLYNK_F("Saving config file..."));
      
      if (file) 
      {
        file.write((char*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));  
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
        file.write((char*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));
        file.close();  
        BLYNK_LOG1(BLYNK_F("OK"));      
      }
      else
      {
        BLYNK_LOG1(BLYNK_F(" failed"));       
      }              
    }
    
    void getConfigData()
    {
      #define BOARD_TYPE        "ESP8266"
      
      if (!SPIFFS.begin()) 
      {
        BLYNK_LOG1(BLYNK_F("SPIFFS failed!. Please use EEPROM."));
        return;
      }
      
      if ( SPIFFS.exists(CONFIG_FILENAME) || SPIFFS.exists(CONFIG_FILENAME_BACKUP) )
      { 
        // if config file exists, load
        loadConfigData();
      }

      if (strncmp(Blynk8266_WM_config.header, BOARD_TYPE, strlen(BOARD_TYPE)) != 0) 
      {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
                                   
          char no_config[] = "nothing";
          BLYNK_LOG2(BLYNK_F("Init new config file, size = "), sizeof(Blynk8266_WM_config));          
          // doesn't have any configuration
          strcpy(Blynk8266_WM_config.header,           BOARD_TYPE);
          strcpy(Blynk8266_WM_config.wifi_ssid,        no_config);
          strcpy(Blynk8266_WM_config.wifi_passphrase,  no_config);
          strcpy(Blynk8266_WM_config.blynk_server,     no_config);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WM_config.blynk_token,      no_config);
          strcpy(Blynk8266_WM_config.board_name,       no_config);
          
          saveConfigData();          
      }
  
      else
      {
        BLYNK_LOG6(BLYNK_F("Header = "), Blynk8266_WM_config.header, BLYNK_F(", SSID = "), Blynk8266_WM_config.wifi_ssid, 
                   BLYNK_F(", PW = "),     Blynk8266_WM_config.wifi_passphrase);
        BLYNK_LOG6(BLYNK_F("Server = "), Blynk8266_WM_config.blynk_server, BLYNK_F(", Port = "), Blynk8266_WM_config.blynk_port, 
                   BLYNK_F(", Token = "),  Blynk8266_WM_config.blynk_token);
        BLYNK_LOG2(BLYNK_F("Board Name = "), Blynk8266_WM_config.board_name);               
      }
    }
     

#else    

    void getConfigData()
    {
      #define EEPROM_SIZE       512
      #define BOARD_TYPE        "ESP8266"
      
      EEPROM.begin(EEPROM_SIZE);
      EEPROM.get(0, Blynk8266_WM_config);

      if (strncmp(Blynk8266_WM_config.header, BOARD_TYPE, strlen(BOARD_TYPE)) != 0) 
      {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
                                   
          char no_config[] = "nothing";
          BLYNK_LOG2(BLYNK_F("Init new EEPROM, size = "), EEPROM.length());          
          // doesn't have any configuration
          strcpy(Blynk8266_WM_config.header,           BOARD_TYPE);
          strcpy(Blynk8266_WM_config.wifi_ssid,        no_config);
          strcpy(Blynk8266_WM_config.wifi_passphrase,  no_config);
          strcpy(Blynk8266_WM_config.blynk_server,     no_config);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WM_config.blynk_token,      no_config);
          strcpy(Blynk8266_WM_config.board_name,       no_config);

          EEPROM.put(0, Blynk8266_WM_config);
          EEPROM.commit();
      }
  
      else
      {
        BLYNK_LOG6(BLYNK_F("Header = "), Blynk8266_WM_config.header, BLYNK_F(", SSID = "), Blynk8266_WM_config.wifi_ssid, 
                   BLYNK_F(", PW = "),     Blynk8266_WM_config.wifi_passphrase);
        BLYNK_LOG6(BLYNK_F("Server = "), Blynk8266_WM_config.blynk_server, BLYNK_F(", Port = "), Blynk8266_WM_config.blynk_port, 
                   BLYNK_F(", Token = "),  Blynk8266_WM_config.blynk_token);
        BLYNK_LOG2(BLYNK_F("Board Name = "), Blynk8266_WM_config.board_name);               
      }
    }      
    
    void saveConfigData()
    {      
      EEPROM.put(0, Blynk8266_WM_config);
      EEPROM.commit();
    }
    
#endif    
    
    boolean connectToWifi(int timeout)
    {
      int sleep_time = 250;

      WiFi.mode(WIFI_STA);

	    BLYNK_LOG1(BLYNK_F("connectToWifi: start"));
	
      if (Blynk8266_WM_config.wifi_passphrase && strlen(Blynk8266_WM_config.wifi_passphrase))
      {
          WiFi.begin(Blynk8266_WM_config.wifi_ssid, Blynk8266_WM_config.wifi_passphrase);
      } 
      else 
      {
          WiFi.begin(Blynk8266_WM_config.wifi_ssid);
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

          result.replace("[[wifi_ssid]]",       Blynk8266_WM_config.wifi_ssid);
          result.replace("[[wifi_passphrase]]", Blynk8266_WM_config.wifi_passphrase);
          result.replace("[[blynk_server]]",    Blynk8266_WM_config.blynk_server);
          result.replace("[[blynk_port]]",      String(Blynk8266_WM_config.blynk_port));
          result.replace("[[blynk_token]]",     Blynk8266_WM_config.blynk_token);
          result.replace("[[board_name]]",      Blynk8266_WM_config.board_name);

          server.send(200, "text/html", result);

          return;
      }
     
      if (key == "wifi_ssid")
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_ssid) -1)
            strcpy(Blynk8266_WM_config.wifi_ssid, value.c_str());
      }
      else if (key == "wifi_passphrase") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.wifi_passphrase) -1)
            strcpy(Blynk8266_WM_config.wifi_passphrase, value.c_str());
      }

      else if (key == "blynk_server") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_server) -1)
            strcpy(Blynk8266_WM_config.blynk_server, value.c_str());
      }
      else if (key == "blynk_port") 
      {
          number_items_Updated++;
          Blynk8266_WM_config.blynk_port = value.toInt();
      }
      else if (key == "blynk_token") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.blynk_token) -1)
            strcpy(Blynk8266_WM_config.blynk_token, value.c_str());
      }
      else if (key == "board_name") 
      {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.board_name) -1)
            strcpy(Blynk8266_WM_config.board_name, value.c_str());
      }

      server.send(200, "text/html", "OK");
      
      if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
      {
        BLYNK_LOG1(BLYNK_F("handleRequest: Updating data to EEPROM"));

        saveConfigData();

        BLYNK_LOG1(BLYNK_F("handleRequest: Resetting"));
        
        // Delay then reset the ESP8266 after save data
        delay(1000);
        ESP.reset();    
      }
    
    }
        
    void startConfigurationMode()
    {
      String chipID = String(ESP.getChipId(), HEX);
      chipID.toUpperCase();
      
	    String ssid = "ESP_" + chipID;

	    String pass = "MyESP_" + chipID;
	    
	    BLYNK_LOG4(BLYNK_F("startConfigurationMode with SSID = "), ssid, BLYNK_F(" and PW = "), pass);
	
      IPAddress apIP(192, 168, 4, 1);

      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid, pass);
      
      delay(100); // ref: https://github.com/espressif/arduino-esp32/issues/985#issuecomment-359157428
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      
      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
      server.on("/", [this](){ handleRequest(); });

      server.begin();
       
      configuration_mode = true;    
    }    

};

static WiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif

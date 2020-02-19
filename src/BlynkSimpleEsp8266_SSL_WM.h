/****************************************************************************************************************************
 * BlynkSimpleEsp8266_SSL_WM.h
 * For ESP8266 boards
 *
 * Blynk_WM is a library for the ESP8266/ESP32 Arduino platform (https://github.com/esp8266/Arduino) to enable easy
 * configuration/reconfiguration and autoconnect/autoreconnect of WiFi/Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/Blynk_WM
 * Licensed under MIT license
 * Version: 1.0.7
 *
 * Original Blynk Library author:
 * @file       BlynkSimpleEsp8266.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      28/10/2019 Initial coding
 *  1.0.1   K Hoang      28/10/2019 Add features
 *  1.0.2   K Hoang      21/11/2019 Fix bug. Add features.
 *  1.0.3   K Hoang      31/11/2019 Fix compiler errors for ESP8266 core pre-2.5.2. Add examples.
 *  1.0.4   K Hoang      07/01/2020 Add configurable personalized RFC-952 DHCP hostname
 *  1.0.5   K Hoang      20/01/2020 Add configurable static IP, GW, SN, DNS1, DNS2 and Config Portal static IP and Credentials
 *  1.0.6   K Hoang      05/02/2020 Optimize, fix EEPROM size to 2K from 4K, shorten code size, add functions
 *  1.0.7   K Hoang      18/02/2020 Add checksum, enable AutoConnect to configurable MultiWiFi and MultiBlynk Credentials
 *****************************************************************************************************************************/

#ifndef BlynkSimpleEsp8266_SSL_WM_h
#define BlynkSimpleEsp8266_SSL_WM_h

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#include <version.h>

#if ESP_SDK_VERSION_NUMBER < 0x020200
#error Please update your ESP8266 Arduino Core
#endif

// Fingerprint is not used by default
//#define BLYNK_DEFAULT_FINGERPRINT "FD C0 7D 8D 47 97 F7 E3 07 05 D3 4E E3 BB 8E 3D C0 EA BE 1C"

#if defined(BLYNK_SSL_USE_LETSENCRYPT)
  static const unsigned char BLYNK_DEFAULT_CERT_DER[] PROGMEM =
  #include <certs/dst_der.h>  // TODO: using DST Root CA X3 for now
  //#include <certs/isrgroot_der.h>
  //#include <certs/letsencrypt_der.h>
#else
  static const unsigned char BLYNK_DEFAULT_CERT_DER[] PROGMEM =
  #include <certs/blynkcloud_der.h>
#endif

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include <ESP8266WebServer.h>

//default to use EEPROM, otherwise, use SPIFFS
#if USE_SPIFFS
#include <FS.h>
#else
#include <EEPROM.h>
#endif

template <typename Client>
class BlynkArduinoClientSecure
    : public BlynkArduinoClientGen<Client>
{
public:
    BlynkArduinoClientSecure(Client& client)
        : BlynkArduinoClientGen<Client>(client)
        , fingerprint(NULL)
    {}

    void setFingerprint(const char* fp) { fingerprint = fp; }

    bool setCACert(const uint8_t* caCert, unsigned caCertLen) {
        bool res = this->client->setCACert(caCert, caCertLen);
        if (!res) {
          BLYNK_LOG1("Failed to load root CA certificate!");
        }
        return res;
    }

    bool setCACert_P(const uint8_t* caCert, unsigned caCertLen) {
        bool res = this->client->setCACert_P(caCert, caCertLen);
        if (!res) {
          BLYNK_LOG1("Failed to load root CA certificate!");
        }
        return res;
    }

    bool connect() 
    {
        //KH
        if (this->connected())
          return true;
        
        // Synchronize time useing SNTP. This is necessary to verify that
        // the TLS certificates offered by the server are currently valid.
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
        time_t now = time(nullptr);

        int i = 0;
        while ( (i++ < 30) && (now < 100000) ) {
          delay(500);
          now = time(nullptr);
        }
        
        struct tm timeinfo;
        gmtime_r(&now, &timeinfo);
        String ntpTime = asctime(&timeinfo);
        ntpTime.trim();
        BLYNK_LOG2("NTP time: ", ntpTime);

        // Now try connecting
        if (BlynkArduinoClientGen<Client>::connect()) 
        {
          if (fingerprint && this->client->verify(fingerprint, this->domain)) 
          {
              BLYNK_LOG1(BLYNK_F("Fingerprint OK"));
              return true;
          } 
          else if (this->client->verifyCertChain(this->domain)) 
          {
              BLYNK_LOG1(BLYNK_F("Certificate OK"));
              return true;
          }
          BLYNK_LOG1(BLYNK_F("Certificate not validated"));
          return false;
        }
        return false;
    }

private:
    const char* fingerprint;
};

#define SSID_MAX_LEN      32
#define PASS_MAX_LEN      32

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

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 2 + (2 * NUM_WIFI_CREDENTIALS) + (2 * NUM_BLYNK_CREDENTIALS) )
typedef struct Configuration 
{
    char header         [16];
    WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
    Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
    int  blynk_port;
    char board_name     [24];
    int  checkSum;
} Blynk_WF_Configuration;
// Currently CONFIG_DATA_SIZE  =  ( 48 + (64 * NUM_WIFI_CREDENTIALS) + (68 * NUM_BLYNK_CREDENTIALS) ) = 312

uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_WF_Configuration);

#define root_html_template " \
<!DOCTYPE html> \
<meta name=\"robots\" content=\"noindex\"> \
<html> \
<head> \
<meta charset=\"utf-8\"> \
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
<title>BlynkSimpleEsp8266_SSL_WM</title> \
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
<td><input type=\"text\" value=\"[[wf_id]]\" size=20 maxlength=64 id=\"wf_id\"></td> \
</tr> \
<tr> \
<td>Password</td> \
<td><input type=\"text\" value=\"[[wf_pw]]\" size=20 maxlength=64 id=\"wf_pw\"></td> \
</tr> \
<tr> \
<td>SSID1</td> \
<td><input type=\"text\" value=\"[[wf_id1]]\" size=20 maxlength=64 id=\"wf_id1\"></td> \
</tr> \
<tr> \
<td>Password1</td> \
<td><input type=\"text\" value=\"[[wf_pw1]]\" size=20 maxlength=64 id=\"wf_pw1\"></td> \
</tr> \
<tr> \
<th colspan=\"2\">Blynk</th> \
</tr> \
<tr> \
<td>Server</td> \
<td><input type=\"text\" value=\"[[b_svr]]\" size=20 maxlength=64 id=\"b_svr\"></td> \
</tr> \
<tr> \
<td>Token</td> \
<td><input type=\"text\" value=\"[[b_tok]]\" size=20 maxlength=32 id=\"b_tok\"></td> \
</tr> \
<tr> \
<td>Server1</td> \
<td><input type=\"text\" value=\"[[b_svr1]]\" size=20 maxlength=64 id=\"b_svr1\"></td> \
</tr> \
<tr> \
<td>Token1</td> \
<td><input type=\"text\" value=\"[[b_tok1]]\" size=20 maxlength=32 id=\"b_tok1\"></td> \
</tr> \
<tr> \
<td>Port</td> \
<td><input type=\"text\" value=\"[[b_pt]]\" id=\"b_pt\"></td> \
</tr> \
<tr> \
<th colspan=\"2\">Hardware</th> \
</tr> \
<tr> \
<td>Name</td> \
<td><input type=\"text\" value=\"[[bd_nm]]\" size=20 maxlength=32 id=\"bd_nm\"></td> \
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
function udVal(key, value) { \
var request = new XMLHttpRequest(); \
var url = '/?key=' + key + '&value=' + value; \
console.log('call ' + url + '...'); \
request.open('GET', url, false); \
request.send(null); \
} \
function save() { \
udVal('wf_id', document.getElementById('wf_id').value); \
udVal('wf_pw', document.getElementById('wf_pw').value); \
udVal('wf_id1', document.getElementById('wf_id1').value); \
udVal('wf_pw1', document.getElementById('wf_pw1').value); \
udVal('b_svr', document.getElementById('b_svr').value); \
udVal('b_tok', document.getElementById('b_tok').value); \
udVal('b_svr1', document.getElementById('b_svr1').value); \
udVal('b_tok1', document.getElementById('b_tok1').value); \
udVal('b_pt', document.getElementById('b_pt').value); \
udVal('bd_nm', document.getElementById('bd_nm').value); \
alert('Updated. Reset'); \
} \
</script> \
</body> \
</html>"

#define BLYNK_SERVER_HARDWARE_PORT    9443

#define BLYNK_BOARD_TYPE      "SSL_ESP8266"  
#define NO_CONFIG       "nothing"  

template <typename Transport>
class BlynkWifi
    : public BlynkProtocol<Transport>
{
    typedef BlynkProtocol<Transport> Base;
public:
    BlynkWifi(Transport& transp)
        : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG2(BLYNK_F("Connecting to "), ssid);
        WiFi.mode(WIFI_STA);
        
        // New from Blynk_WM v1.0.5
        if (static_IP != IPAddress(0, 0, 0, 0))
        {
          BLYNK_LOG1(BLYNK_F("Use static IP"));
          WiFi.config(static_IP, static_GW, static_SN, static_DNS1, static_DNS2);         
        }
        
        setHostname();

        if (WiFi.status() != WL_CONNECTED) {
            if (pass && strlen(pass)) {
                WiFi.begin(ssid, pass);
            } else {
                WiFi.begin(ssid);
            }
        }
        while (WiFi.status() != WL_CONNECTED) {
            BlynkDelay(500);
        }
        BLYNK_LOG1(BLYNK_F("Connected to WiFi"));
        displayWiFiData();
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT_SSL,
                const char* fingerprint = NULL)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);

        if (fingerprint) {
          this->conn.setFingerprint(fingerprint);
        } else {
          this->conn.setCACert_P(BLYNK_DEFAULT_CERT_DER, sizeof(BLYNK_DEFAULT_CERT_DER));
        }
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT_SSL,
                const char* fingerprint = NULL)
    {
        Base::begin(auth);
        this->conn.begin(ip, port);

        if (fingerprint) {
          this->conn.setFingerprint(fingerprint);
        } else {
          this->conn.setCACert_P(BLYNK_DEFAULT_CERT_DER, sizeof(BLYNK_DEFAULT_CERT_DER));
        }
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT_SSL,
               const char* fingerprint = NULL)
    {
        connectWiFi(ssid, pass);
        config(auth, domain, port, fingerprint);
        while(this->connect() != true) {}
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT_SSL,
               const char* fingerprint = NULL)
    {
        connectWiFi(ssid, pass);
        config(auth, ip, port, fingerprint);
        while(this->connect() != true) {}
    }
     
    // For ESP8266
    #define LED_ON      LOW
    #define LED_OFF     HIGH
    
		void begin(const char *iHostname = "", const char* fingerprint = NULL)
    {
        #define TIMEOUT_CONNECT_WIFI			30000
        
        //Turn OFF
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LED_OFF);

				if (iHostname[0] == 0)
				{
					#ifdef ESP8266
						String _hostname = "ESP8266-" + String(ESP.getChipId(), HEX);
					#else		//ESP32
						String _hostname = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);
					#endif
					_hostname.toUpperCase();

					getRFC952_hostname(_hostname.c_str());		
					
				}
				else
				{
					// Prepare and store the hostname only not NULL
					getRFC952_hostname(iHostname);
				}

				BLYNK_LOG2(BLYNK_F("RFC925 Hostname = "), RFC952_hostname);
               
        if (getConfigData())
        {
          hadConfigData = true;
          
          for (int i = 0; i < NUM_WIFI_CREDENTIALS; i++)
          {
            wifiMulti.addAP(Blynk8266_WM_config.WiFi_Creds[i].wifi_ssid, Blynk8266_WM_config.WiFi_Creds[i].wifi_pw);
          }

          if (connectMultiWiFi())
          {
            BLYNK_LOG1(BLYNK_F("bg: WiFi connected. Try Blynk"));
            
            int i = 0;
            while ( (i++ < 10) && !this->connectMultiBlynk() )
            {
            }
            
            if  (this->connected())
            {
              BLYNK_LOG1(BLYNK_F("bg: WiFi+Blynk connected"));
            }
            else 
            {
              BLYNK_LOG1(BLYNK_F("bg: WiFi connected, Blynk not"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
            }
          } 
          else 
          {
              BLYNK_LOG1(BLYNK_F("bg: Fail2connect WiFi+Blynk"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
          }
        }
        else
        {
            BLYNK_LOG1(BLYNK_F("bg: No configdat. Stay forever in config portal"));
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
      if ( WiFi.status() != WL_CONNECTED || !this->connected() )
      {   
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi / Blynk. 
        // But if user has connected to configWeb, stay there until done, then reset hardware
		    if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
		    {
		      retryTimes = 0;
		      
			    if (server)
			      server->handleClient();	
			      
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
		           BLYNK_LOG2(BLYNK_F("run: WiFi lost & config Timeout. Connect WiFi+Blynk. Retry# : "), retryTimes);
		        }
		        else
		        {
              ESP.reset(); 
		        }		        
		      }
		      #endif
		      	      
			    // Not in config mode, try reconnecting before forcing to config mode
			    if ( WiFi.status() != WL_CONNECTED )
			    {
				    BLYNK_LOG1(BLYNK_F("run: WiFi lost. Reconnect WiFi+Blynk"));

				    if (connectMultiWiFi())
				    {
 				      // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LED_OFF);

				      BLYNK_LOG1(BLYNK_F("run: WiFi reconnected. Connect to Blynk"));
				      
				      if (this->connectMultiBlynk())
				      {
					      BLYNK_LOG1(BLYNK_F("run: WiFi+Blynk reconnected"));
					    }
				    }
			    }
			    else
			    {
				    BLYNK_LOG1(BLYNK_F("run: Blynk lost. Connect Blynk"));

				    if (this->connectMultiBlynk()) 
				    {
				      // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
              digitalWrite(LED_BUILTIN, LED_OFF);
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
      	BLYNK_LOG1(BLYNK_F("run: got WiFi+Blynk back, great"));
      	// turn the LED_BUILTIN OFF to tell us we exit configuration mode.
        digitalWrite(LED_BUILTIN, LED_OFF);
      }

      if (this->connected())
      {
        Base::run();
      }
    }
    
		void setHostname(void)
		{
			if (RFC952_hostname[0] != 0)
			{
				WiFi.hostname(RFC952_hostname);
			}
		}

		void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
		{
			portal_apIP = portalIP;
		}
		
		void setConfigPortal(String ssid = "", String pass = "")
		{
			portal_ssid = ssid;
			portal_pass = pass;
		}		

    void setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn = IPAddress(255, 255, 255, 0), 
                              IPAddress dns_address_1 = IPAddress(0, 0, 0, 0), 
                              IPAddress dns_address_2 = IPAddress(0, 0, 0, 0))
    {
      static_IP     = ip;
      static_GW     = gw;
      static_SN     = sn;
      
      // Default to local GW
      if (dns_address_1 == IPAddress(0, 0, 0, 0))
        static_DNS1   = gw;
      else
        static_DNS1   = dns_address_1;
        
      // Default to Google DNS (8, 8, 8, 8)  
      if (dns_address_2 == IPAddress(0, 0, 0, 0))
        static_DNS2   = IPAddress(8, 8, 8, 8);
      else
        static_DNS2   = dns_address_2;
    }
 
    String getServerName(uint8_t index)
    {
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");
      
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.Blynk_Creds[index].blynk_server));
    }
                       
    String getToken(uint8_t index)
    {
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();
            
      return (String(Blynk8266_WM_config.Blynk_Creds[index].blynk_token));
    }
        
    String getBoardName()
    {
      if (!hadConfigData)
        getConfigData();

      return (String(Blynk8266_WM_config.board_name));
    }
    
    int getHWPort()
    {
      if (!hadConfigData)
        getConfigData();

      return (Blynk8266_WM_config.blynk_port);
    }    
          
    Blynk_WF_Configuration* getFullConfigData(Blynk_WF_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();
        
      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Blynk8266_WM_config, sizeof(Blynk_WF_Configuration));

      return (configData);
    }
           
private:
    ESP8266WebServer *server;
    bool configuration_mode = false;
    
    ESP8266WiFiMulti wifiMulti;
    
    unsigned long configTimeout;
    bool hadConfigData = false;     
    
    Blynk_WF_Configuration Blynk8266_WM_config;
    
    // For Config Portal, from Blynk_WM v1.0.5     
    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    
    String portal_ssid = "";
    String portal_pass = "";
    
    // For static IP, from Blynk_WM v1.0.5 
    IPAddress static_IP   = IPAddress(0, 0, 0, 0);
    IPAddress static_GW   = IPAddress(0, 0, 0, 0);
    IPAddress static_SN   = IPAddress(255, 255, 255, 0);
    IPAddress static_DNS1 = IPAddress(0, 0, 0, 0);
    IPAddress static_DNS2 = IPAddress(0, 0, 0, 0);    

		#define RFC952_HOSTNAME_MAXLEN      24
		char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

		char* getRFC952_hostname(const char* iHostname)
		{ 
			memset(RFC952_hostname, 0, sizeof(RFC952_hostname));
			
			size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);
			
			size_t j = 0;
			
			for (size_t i = 0; i < len - 1; i++)
			{
				if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
				{
				  RFC952_hostname[j] = iHostname[i];
				  j++;
				}  
			}
			// no '-' as last char
			if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
				RFC952_hostname[j] = iHostname[len - 1];

			return RFC952_hostname;
		}

		void displayConfigData(void)
		{
		    BLYNK_LOG4(BLYNK_F("Header = "), Blynk8266_WM_config.header, 
		               BLYNK_F(", Board Name = "), Blynk8266_WM_config.board_name);
        BLYNK_LOG4(BLYNK_F("SSID = "), Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, 
                   BLYNK_F(", PW = "), Blynk8266_WM_config.WiFi_Creds[0].wifi_pw);           
        BLYNK_LOG4(BLYNK_F("SSID1 = "), Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, 
                   BLYNK_F(", PW1 = "), Blynk8266_WM_config.WiFi_Creds[1].wifi_pw);                
        BLYNK_LOG4(BLYNK_F("Server = "), Blynk8266_WM_config.Blynk_Creds[0].blynk_server,
                   BLYNK_F(", Token = "),  Blynk8266_WM_config.Blynk_Creds[0].blynk_token);
        BLYNK_LOG4(BLYNK_F("Server1 = "), Blynk8266_WM_config.Blynk_Creds[1].blynk_server,
                   BLYNK_F(", Token1 = "),  Blynk8266_WM_config.Blynk_Creds[1].blynk_token);        
        BLYNK_LOG2(BLYNK_F("Port = "), Blynk8266_WM_config.blynk_port);   
		}   		
 
    void displayWiFiData(void)
		{
        BLYNK_LOG6(BLYNK_F("IP = "), WiFi.localIP().toString(), BLYNK_F(", GW = "), WiFi.gatewayIP().toString(), 
                   BLYNK_F(", SN = "), WiFi.subnetMask().toString());
        BLYNK_LOG4(BLYNK_F("DNS1 = "), WiFi.dnsIP(0).toString(), BLYNK_F(", DNS2 = "), WiFi.dnsIP(1).toString());
    }
    
    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Blynk8266_WM_config) - sizeof(Blynk8266_WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Blynk8266_WM_config ) + index);
      }
     
      return checkSum;
    }
       
#if USE_SPIFFS     

    #define  CONFIG_FILENAME         BLYNK_F("/wmssl_conf.dat")
    #define  CONFIG_FILENAME_BACKUP  BLYNK_F("/wmssl_conf.bak")

    void loadConfigData(void)
    {
      File file = SPIFFS.open(CONFIG_FILENAME, "r");
      BLYNK_LOG1(BLYNK_F("Load configfile "));
      
      if (!file) 
      {
        BLYNK_LOG1(BLYNK_F("failed"));
        
        // Trying open redundant config file
        file = SPIFFS.open(CONFIG_FILENAME_BACKUP, "r");
        BLYNK_LOG1(BLYNK_F("Load backup configfile ")); 
        
        if (!file)
        {
          BLYNK_LOG1(BLYNK_F("also failed"));
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
      BLYNK_LOG1(BLYNK_F("Save configfile "));
      
      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;
      BLYNK_LOG2(BLYNK_F("chkSum = 0x"), String(calChecksum, HEX));
      
      if (file) 
      {
        file.write((uint8_t*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));  
        file.close();     
        BLYNK_LOG1(BLYNK_F("OK"));
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));        
      }  
      
      // Trying open redundant Auth file
      file = SPIFFS.open(CONFIG_FILENAME_BACKUP, "w");
      BLYNK_LOG1(BLYNK_F("Save backup configfile ")); 
      
      if (file)
      {
        file.write((uint8_t*) &Blynk8266_WM_config, sizeof(Blynk8266_WM_config));
        file.close();  
        BLYNK_LOG1(BLYNK_F("OK"));      
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("failed"));       
      }              
    }
    
    bool getConfigData()
    {      
      if (!SPIFFS.begin()) 
      {
        BLYNK_LOG1(BLYNK_F("SPIFFS failed! Pls use EEPROM."));
        return false;
      }
      
      if ( SPIFFS.exists(CONFIG_FILENAME) || SPIFFS.exists(CONFIG_FILENAME_BACKUP) )
      { 
        // if config file exists, load
        loadConfigData();
      }

      int calChecksum = calcChecksum();
      
      BLYNK_LOG4(BLYNK_F("Calc Cksum = 0x"), String(calChecksum, HEX),
                 BLYNK_F(", Read Cksum = 0x"), String(Blynk8266_WM_config.checkSum, HEX)); 
      
      //displayConfigData();

      if ( (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WM_config.checkSum) )
      {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
                                   
          BLYNK_LOG2(BLYNK_F("Init new config file, size = "), sizeof(Blynk8266_WM_config));  
                  
          // doesn't have any configuration
          strcpy(Blynk8266_WM_config.header,                        BLYNK_BOARD_TYPE);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG);          
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WM_config.board_name,       NO_CONFIG);
          // Don't need
          Blynk8266_WM_config.checkSum = 0;
          
          saveConfigData();   
          
          return false;       
      }
      else if ( !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) ) ) 
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }  
      else
      {
        displayConfigData();               
      }
      
      return true;
    }
     

#else

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

    bool getConfigData()
    {      
      EEPROM.begin(EEPROM_SIZE);
      EEPROM.get(EEPROM_START, Blynk8266_WM_config);

      int calChecksum = calcChecksum();
      
      BLYNK_LOG4(BLYNK_F("Calc Cksum = 0x"), String(calChecksum, HEX), 
                 BLYNK_F(", Read Cksum = 0x"), String(Blynk8266_WM_config.checkSum, HEX)); 

      if ( (strncmp(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != Blynk8266_WM_config.checkSum) )
      {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
                                   
          BLYNK_LOG2(BLYNK_F("Init new EEPROM, size = "), EEPROM.length());  
                  
          // doesn't have any configuration
          strcpy(Blynk8266_WM_config.header,                        BLYNK_BOARD_TYPE);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG);
          strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG);          
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG);
          strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG);
          Blynk8266_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(Blynk8266_WM_config.board_name,       NO_CONFIG);
          // Don't need
          Blynk8266_WM_config.checkSum = 0;

          EEPROM.put(EEPROM_START, Blynk8266_WM_config);
          EEPROM.commit();
          
          return false;
      }
      else if ( !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[0].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_server,   NO_CONFIG, strlen(NO_CONFIG) )  ||
                !strncmp(Blynk8266_WM_config.Blynk_Creds[1].blynk_token,    NO_CONFIG, strlen(NO_CONFIG) ) ) 
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }  
      else
      {
        displayConfigData();               
      }
      
      return true;
    }      
    
    void saveConfigData()
    {      
      int calChecksum = calcChecksum();
      Blynk8266_WM_config.checkSum = calChecksum;
      BLYNK_LOG4(BLYNK_F("Save EEPROM, size = "), EEPROM.length(), BLYNK_F(", chkSum = 0x"), String(calChecksum, HEX));
      
      EEPROM.put(EEPROM_START, Blynk8266_WM_config);
      EEPROM.commit();
    }
    
#endif

    bool connectMultiBlynk(void)
    {
      #define BLYNK_CONNECT_TIMEOUT_MS      5000L
      
      for (int i = 0; i < NUM_BLYNK_CREDENTIALS; i++)
      {
        config(Blynk8266_WM_config.Blynk_Creds[i].blynk_token, 
                    Blynk8266_WM_config.Blynk_Creds[i].blynk_server, Blynk8266_WM_config.blynk_port);
                                    
        if (this->connect(BLYNK_CONNECT_TIMEOUT_MS) )
        {
          BLYNK_LOG4(BLYNK_F("Connected to Blynk Server = "), Blynk8266_WM_config.Blynk_Creds[i].blynk_server, 
                     BLYNK_F(", Token  = "), Blynk8266_WM_config.Blynk_Creds[i].blynk_token);
          return true;
        }
      }

      BLYNK_LOG1(BLYNK_F("Blynk not connected"));
      
      return false;

    }

    uint8_t connectMultiWiFi(void)
    {
      // For ESP8266, this better be 3000 to enable connect the 1st time
      #define WIFI_MULTI_CONNECT_WAITING_MS      3000L
      
      uint8_t status;
      BLYNK_LOG1(BLYNK_F("Connecting MultiWifi..."));

      int i = 0;
      status = wifiMulti.run();
      delay(WIFI_MULTI_CONNECT_WAITING_MS);

      while ( ( i++ < 10 ) && ( status != WL_CONNECTED ) )
      {
        status = wifiMulti.run();

        if ( status == WL_CONNECTED )
          break;
        else
          delay(WIFI_MULTI_CONNECT_WAITING_MS);
      }

      if ( status == WL_CONNECTED )
      {
        BLYNK_LOG2(BLYNK_F("WiFi connected after time: "), i);
        BLYNK_LOG4(BLYNK_F("SSID: "), WiFi.SSID(), BLYNK_F(", RSSI = "), WiFi.RSSI());
        BLYNK_LOG4(BLYNK_F("Channel: "), WiFi.channel(), BLYNK_F(", IP address: "), WiFi.localIP() );
      }
      else
        BLYNK_LOG1(BLYNK_F("WiFi not connected"));

      return status;
    }
    
    void handleRequest()
    {
      if (server)
      {
        String key = server->arg("key");
        String value = server->arg("value");
        
        static int number_items_Updated = 0;

        if (key == "" && value == "") 
        {
          String result = root_html_template;
          
          BLYNK_LOG1(BLYNK_F("hR: replace result"));
          
          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          result.replace("[[wf_id]]",     Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[wf_pw]]",     Blynk8266_WM_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[wf_id1]]",    Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[wf_pw1]]",    Blynk8266_WM_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[b_svr]]",     Blynk8266_WM_config.Blynk_Creds[0].blynk_server);       
          result.replace("[[b_tok]]",     Blynk8266_WM_config.Blynk_Creds[0].blynk_token);
          result.replace("[[b_svr1]]",    Blynk8266_WM_config.Blynk_Creds[1].blynk_server);       
          result.replace("[[b_tok1]]",    Blynk8266_WM_config.Blynk_Creds[1].blynk_token);
          result.replace("[[b_pt]]",      String(Blynk8266_WM_config.blynk_port));
          result.replace("[[bd_nm]]",     Blynk8266_WM_config.board_name);

          server->send(200, "text/html", result);

          return;
        }
       
        if (number_items_Updated == 0)
        {
          memset(&Blynk8266_WM_config, 0, sizeof(Blynk8266_WM_config));
          strcpy(Blynk8266_WM_config.header, BLYNK_BOARD_TYPE);
        }
        
        if (key == "wf_id")
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) -1)
              strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, value.c_str());
            else
              strncpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_ssid) -1);    
        }
        else if (key == "wf_pw") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw) -1)
              strcpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw, value.c_str());
            else
              strncpy(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[0].wifi_pw) -1);    
        }
        
        else if (key == "wf_id1")
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) -1)
              strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, value.c_str());
            else
              strncpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_ssid) -1);    
        }
        else if (key == "wf_pw1") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw) -1)
              strcpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw, value.c_str());
            else
              strncpy(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(Blynk8266_WM_config.WiFi_Creds[1].wifi_pw) -1);    
        }        
        else if (key == "b_svr") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_server) -1)
              strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server, value.c_str());
            else
              strncpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_server) -1);      
        }
        else if (key == "b_tok") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_token) -1)
              strcpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token, value.c_str());
            else
              strncpy(Blynk8266_WM_config.Blynk_Creds[0].blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[0].blynk_token) -1);    
        }
        else if (key == "b_svr1") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_server) -1)
              strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server, value.c_str());
            else
              strncpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_server, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_server) -1);      
        }
        else if (key == "b_tok1") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_token) -1)
              strcpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token, value.c_str());
            else
              strncpy(Blynk8266_WM_config.Blynk_Creds[1].blynk_token, value.c_str(), sizeof(Blynk8266_WM_config.Blynk_Creds[1].blynk_token) -1);    
        }                     
        else if (key == "b_pt") 
        {
            number_items_Updated++;
            Blynk8266_WM_config.blynk_port = value.toInt();
        }
        else if (key == "bd_nm") 
        {
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(Blynk8266_WM_config.board_name) -1)
              strcpy(Blynk8266_WM_config.board_name, value.c_str());
            else
              strncpy(Blynk8266_WM_config.board_name, value.c_str(), sizeof(Blynk8266_WM_config.board_name) -1);  
        }
        
        server->send(200, "text/html", "OK");
        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
        {
          #if USE_SPIFFS     
            BLYNK_LOG2(BLYNK_F("hR: Update SPIFFS "), CONFIG_FILENAME);
          #else
            BLYNK_LOG1(BLYNK_F("hR: Update EEPROM"));
          #endif

          saveConfigData();

          BLYNK_LOG1(BLYNK_F("hR: Reset"));
          
          // Delay then reset the ESP8266 after save data
          delay(1000);
          ESP.reset();    
        }
      }    // if (server)
    }
        
    void startConfigurationMode()
    {   
      #define CONFIG_TIMEOUT			60000L
      
      // turn the LED_BUILTIN ON to tell us we are in configuration mode.
      digitalWrite(LED_BUILTIN, LED_ON);
      
      if ( (portal_ssid == "") || portal_pass == "" )
      {      
        String chipID = String(ESP.getChipId(), HEX);
        chipID.toUpperCase();
        
	      portal_ssid = "ESP_" + chipID;

	      portal_pass = "MyESP_" + chipID;
	    }
	    
	    BLYNK_LOG6(BLYNK_F("startConfigMode with SSID = "), portal_ssid, BLYNK_F(", PW = "), portal_pass,
	               BLYNK_F(" and IP = "), portal_apIP.toString());
	
      WiFi.mode(WIFI_AP);
      WiFi.softAP(portal_ssid.c_str(), portal_pass.c_str());
      
      delay(100); // ref: https://github.com/espressif/arduino-esp32/issues/985#issuecomment-359157428
      WiFi.softAPConfig(portal_apIP, portal_apIP, IPAddress(255, 255, 255, 0));
      
      if (!server)
	      server = new ESP8266WebServer;
	      
      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
      if (server)
      {
        server->on("/", [this](){ handleRequest(); });
        server->begin();
      }
                           
      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
        configTimeout = millis() + CONFIG_TIMEOUT;                        
      else
        configTimeout = 0;
       
      configuration_mode = true;    
    }    
  };

static WiFiClientSecure _blynkWifiClient;
static BlynkArduinoClientSecure<WiFiClientSecure> _blynkTransport(_blynkWifiClient);
BlynkWifi<BlynkArduinoClientSecure<WiFiClientSecure> > Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif

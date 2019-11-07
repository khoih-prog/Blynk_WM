To use SSL, in Arduino IDE Tools menu, it's OK to select either Basic SSL Support (lower ROM use, OK with Blynk+OpenSSL+LetsEncrypt) or All Ciphers,

Certainly don't forget to forward port 9443 from your Internet Router to your local Blynk server.

## For ESP8266


## Using LetsEncrypt Certificate (valid only 3 months, can be 1 year with paid subscription )

  1) In libraries/Blynk/src/Blynk/BlynkConfig.h, uncomment to use #define BLYNK_SSL_USE_LETSENCRYPT
  
  ```
  // Uncomment to use Let's Encrypt Root CA
  #define BLYNK_SSL_USE_LETSENCRYPT
  ```
  
  2) Server and name must use hostname, for example: "xxxx.duckdns.org" / "xxxx.no-ip.org". Local IP won't work (e.g. "192.168.x.y", "10.10.x.y", etc.). Otherwise, you will get the following error:
  
      ```
      Error BSSL:_wait_for_handshake: failed
      BSSL:Couldn't connect. Error = 'Expected server name was not found in the chain.'
      ```
      
      Numbered IP ( e.g. 222.222.111.111) is also not supported. This is the limitation of Let's Encrypt. Also have in mind that "xxxx.duckdns.org"/"xxxx.no-ip.org" must be resolved by public DNS severs.
      
      Add server.host property in server.properties file. For example :
      
      ```
      server.host=xxxx.duckdns.org
      ```
      or
      ```
      server.host=xxxx.no-ip.org
      ```
  3) Modifying /home/pi/Blynk-Server/server.properties (assuming your Blynk Server was installed in /home/pi/Blynk-Server, replacing with your correct path). You can try either of the following ways:
  
      a) OK
      
      ```
      server.ssl.cert=/home/pi/Blynk-Server/fullchain.crt
      server.ssl.key=/home/pi/Blynk-Server/privkey.pem
      server.ssl.key.pass=your_ssl_key_password
      ```
      
      b) OK. Let's Encrypt certificate found on ~/Blynk-Server or /
      
      ```
      server.ssl.cert= 
      server.ssl.key=
      server.ssl.key.pass= 
      ```
      
  4) Get LetsEncrypt Certificate => fullchain.crt, privkey.pem and user.pem are created in / (root / 664)
  
  5) Convert fullchain.crt -> fullchain_der.h :
  
      ```
      cd ~/Blynk_Server
      cp /fullchain.crt .
      openssl x509 -in fullchain.crt -outform der -out fullchain.der
      xxd -i fullchain.der > fullchain_der.h
      ```
     
     Then delete the line 
     ```
     "unsigned char fullchain_der[] ="
     ``` 
     and 
     ```
     "unsigned int fullchain_der_len = xxxx;"
     ```
     in the file
     
  6) Replacing certificate files in ~/Arduino/libraries/Blynk/src/certs/ (assuming Arduino libraries are stored in ~/Arduino/libraries/. Replacing with your correct path) with fullchain_der.h.
  
      a) ~/Arduino/libraries/Blynk/src/certs/blynkcloud_der.h (if don't use #define BLYNK_SSL_USE_LETSENCRYPT) 
      b) ~/Arduino/libraries/Blynk/src/certs/dst_der.h (if use #define BLYNK_SSL_USE_LETSENCRYPT)
      
      ```
      cd ~/Arduino/libraries/Blynk/src/certs/
      mv dst_der.h dst_der.h.orig
      mv blynkcloud_der.h blynkcloud_der.h.orig
      cp ~/Blynk_Server/fullchain_der.h blynkcloud_der.h
      cp ~/Blynk_Server/fullchain_der.h dst_der.h
      ```
      
## Using OpenSSL Certificate (valid 5 years)

  1) In libraries/Blynk/src/Blynk/BlynkConfig.h, comment to not use #define BLYNK_SSL_USE_LETSENCRYPT
  
  ```
  // Uncomment to use Let's Encrypt Root CA
  //#define BLYNK_SSL_USE_LETSENCRYPT  
  ```
  
  2) Server and name must use hostname, for example: "xxxx.duckdns.org" / "xxxx.no-ip.org". Local IP won't work (e.g. "192.168.x.y", "10.10.x.y", etc.).Otherwise, you will get the following error:
  
      ```
      Error BSSL:_wait_for_handshake: failed
      BSSL:Couldn't connect. Error = 'Expected server name was not found in the chain.'   
      ```
      
  3) Create Certificate (in the example, make a new ~/Blynk-Server/SSL directory store to-be-created SSL certificate):
  
      ```
      pi@raspberrypi:~/Blynk-Server/SSL $ openssl req -x509 -nodes -days 1825 -newkey rsa:2048 -keyout server.key -out server.crt
      
      Generating a RSA private key
      ............+++++
      .........+++++
      writing new private key to 'server.key'
      -----
      You are about to be asked to enter information that will be incorporated
      into your certificate request.
      What you are about to enter is what is called a Distinguished Name or a DN.
      There are quite a few fields but you can leave some blank
      For some fields there will be a default value,
      If you enter '.', the field will be left blank.
      -----
      Country Name (2 letter code) [AU]:XX
      State or Province Name (full name) [Some-State]:YYYY
      Locality Name (eg, city) []:AAAAA
      Organization Name (eg, company) [Internet Widgits Pty Ltd]:YourName
      Organizational Unit Name (eg, section) []:.
      Common Name (e.g. server FQDN or YOUR name) []:xxxx.duckdns.org or xxxx.no-ip.org
      Email Address []:your_email@yourmail.com
      ```
      
      To create server.pem, must use v1 PBE-SHA1-2DES. Otherwise, Blynk server will have error "invalid key file".
      
      ```
      pi@raspberrypi:~/Blynk-Server/SSL $ openssl pkcs8 -topk8 -v1 PBE-SHA1-2DES -in server.key -out server.pem
      Enter Encryption Password: your_ssl_key_password
      Verifying - Enter Encryption Password: your_ssl_key_password
      ```

      Copy server.* files to ~/Blynk-Server. Chown/grp to root, Chmod to 644
      
      Remember your your_ssl_key_password to use later in server.properties file.

  2) Modify file server.properties
  
      a) Modify as follows:
      
      ```
      server.ssl.cert=/home/pi/Blynk-Server/server.crt
      server.ssl.key=/home/pi/Blynk-Server/server.pem
      server.ssl.key.pass=your_ssl_key_password
      ```
      
  4) Convert server.crt => server_der.h :
      
      ```
      cd ~/Blynk_Server
      cp /server.crt .
      openssl x509 -in server.crt -outform der -out server.der
      xxd -i server.der > server_der.h
      ```
      
     Then edit and delete "unsigned char server_der[] =" and "unsigned int server_der_len = xxxx;" in the file
     
  5) Replacing certificate files in ~/Arduino/libraries/Blynk/src/certs/ with server_der.h
  
      a) ~/Arduino/libraries/Blynk/src/certs/blynkcloud_der.h (if not define BLYNK_SSL_USE_LETSENCRYPT) 
      b) ~/Arduino/libraries/Blynk/src/certs/dst_der.h (if define BLYNK_SSL_USE_LETSENCRYPT)
      
      ```
      cd ~/Arduino/libraries/Blynk/src/certs/
      mv dst_der.h dst_der.h.orig
      mv blynkcloud_der.h blynkcloud_der.h.orig
      cp ~/Blynk_Server/server_der.h blynkcloud_der.h
      cp ~/Blynk_Server/server_der.h dst_der.h  
      ```
      
## For ESP32

  1) For ESP32 SSL, use <certs/letsencrypt_pem.h> if using LetsEncrypt (use #define BLYNK_SSL_USE_LETSENCRYPT) and <certs/blynkcloud_pem.h> if use OpenSSL (don't use #define BLYNK_SSL_USE_LETSENCRYPT)

  These line are in ~/Arduino/libraries/Blynk/src/BlynkSimpleEsp32_SSL.h or BlynkSimpleEsp32_SSL_WM.h
  ```  	
     #if defined(BLYNK_SSL_USE_LETSENCRYPT)
      static const char BLYNK_DEFAULT_ROOT_CA[] =
      #include <certs/letsencrypt_pem.h>
    #else
      static const char BLYNK_DEFAULT_ROOT_CA[] =
      #include <certs/blynkcloud_pem.h>
    #endif
  ```
  
  2) To create file blynkcloud_pem.h/letsencrypt_pem.h from localServer certificate file OpenSSL server.crt or LetsEncrypt fullchain.crt, just copy and add ",",\n,; to the end of each line similar to the original file. (You can write a simple C program to do this converting task).
   
   This file is OK to use (both blynkcloud_pem.h/letsencrypt_pem.h are the same) even if BLYNK_SSL_USE_LETSENCRYPT is defined or not.
   
   For Example: blynkcloud_pem.h generated from server.crt
   
 ```
    
 "-----BEGIN CERTIFICATE-----\n"																			\
"MIID8TCCAtmgAwIBAgIUXTAEvCpQ1v695km/VZ5xScms0LIwDQYJKoZIhvcNAQEL\n"	\
"BQAwgYcxCzAJBgNVBAYTAkNBMRAwDgYDVQQIDAdPTlRBUklPMRQwEgYDVQQHDAtN\n"	\
"aXNzaXNzYXVnZTESMBAGA1UECgwJS2hvaUhvYW5nMRowGAYDVQQDDBFraG9paC5k\n"	\
"dWNrZG5zLm9yZzEgMB4GCSqGSIb3DQEJARYRa2hvaWg1OEBnbWFpbC5jb20wHhcN\n"	\
"MTkwOTI1MDI0NTQ2WhcNMjQwOTIzMDI0NTQ2WjCBhzELMAkGA1UEBhMCQ0ExEDAO\n"	\
"BgNVBAgMB09OVEFSSU8xFDASBgNVBAcMC01pc3Npc3NhdWdlMRIwEAYDVQQKDAlL\n"	\
"aG9pSG9hbmcxGjAYBgNVBAMMEWtob2loLmR1Y2tkbnMub3JnMSAwHgYJKoZIhvcN\n"	\
"AQkBFhFraG9paDU4QGdtYWlsLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\n"	\
"AQoCggEBAMWo8olI2wf9v72wQXJyMF+IUKM39IkGo6nzYmyB6FYAFo3n/k/X+A1p\n"	\
"7FML6t6kauqDRuCOmpyysuNPyzKRU+NmY+Lfae5mOXXBlEM5C7WSv2tQAI7W653G\n"	\
"s1vWdCKZRNr2rvuFyc/1Fhox23sZJVK1bohwUYCTRRwTtq4dg+Cg47oui1Q0UEHM\n"	\
"luawula/jYUt9UyzNqilxcLP47KrH2QenG4zdOq8jSD9EJ4F7y9uCaU2VRm3vaO4\n"	\
"2rHtcQuvt7uj21UQfrsn47uSP2JDnBljPuRVGwQV1sCRBHrxDmkGT+ri4MKz1uzK\n"	\
"wPzlLhZZlQjud+2WGjdF3/WBWhNY5wkCAwEAAaNTMFEwHQYDVR0OBBYEFMlHW+J/\n"	\
"CfKhqlCpavqEM628lhMaMB8GA1UdIwQYMBaAFMlHW+J/CfKhqlCpavqEM628lhMa\n"	\
"MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBAAQSYEN7QIMMeYLG\n"	\
"f5J/nGoJbApP3+o1hjU2N8RvA315HtclCAmO4Ruk/gtsEyi7PoBZWCz/o6bpypkz\n"	\
"GIPO2bvwI7O5nHBee6AXntZ9Qzjl08WLlm9zCTsOzvh2pkIuzaucG2JfcD3V0z22\n"	\
"jXqYDpIL1x3UmEmKPrrJlwQY2wzWNZF/Z9vUUvLIS59+KmtpsmhPqqAQuEt3vmkX\n"	\
"5xs+6ZI3VboN1N7Xg/N2WsXzpnslxu9qiMaSZ3sHTL8sYhLlnN34EF+V3cjai+uS\n"	\
"JEWZcGbwKTkwCaWy+MYFEWJUK/Chic2RgslG4jdO4lMXBDnc0+kCQgasUo6mbNUs\n"	\
"WSHZY1Q=\n"																													\
"-----END CERTIFICATE-----\n"																					;

```
      
## See more in Blynk Server instructions (https://github.com/blynkkk/blynk-server#blynk-server) :
      
A) Automatic Let's Encrypt certificates generation

  Latest Blynk server has super cool feature - automatic Let's Encrypt certificates generation. However, it has few requirements:

  Add server.host property in server.properties file. For example :
  
    server.host=myhost.com
    
  IP is not supported, this is the limitation of Let's Encrypt. Also have in mind that myhost.com should be resolved by public DNS severs.

  Add contact.email property in server.properties. For example :
    
    contact.email=test@gmail.com
    
  You need to start server on port 80 (requires root or admin rights) or make port forwarding to default Blynk HTTP port - 8080.

  That's it! Run server as regular and certificates will be generated automatically.
      
B) Manual Let's Encrypt SSL/TLS Certificates

  1) First install certbot on your server (machine where you going to run Blynk Server)
  
  ```
  wget https://dl.eff.org/certbot-auto
  chmod a+x certbot-auto
  ```
  
  2) Generate and verify certificates (your server should be connected to internet and have open 80/443 ports)
  ```
  ./certbot-auto certonly --agree-tos --email YOUR_EMAIL --standalone -d YOUR_HOST
  ```
  For example:
  
  ```
  ./certbot-auto certonly --agree-tos --email pupkin@blynk.cc --standalone -d blynk.cc
  ```
  
  Then add to your server.properties file (in folder with server.jar)

  ```
  server.ssl.cert=/etc/letsencrypt/live/YOUR_HOST/fullchain.pem
  server.ssl.key=/etc/letsencrypt/live/YOUR_HOST/privkey.pem
  server.ssl.key.pass=your_ssl_key_password
  ```

C) Generate own OpenSSL certificates

  1) Generate self-signed certificate and key
  
  ```
  openssl req -x509 -nodes -days 1825 -newkey rsa:2048 -keyout server.key -out server.crt
  ```
  2) Convert server.key to PKCS#8 private key file in PEM format
  
	  a) For Local Blynk Server running RPi Raspbian, using:
	  
	  
	  ```openjdk version "11.0.3" 2019-04-16```
	  ```OpenJDK Runtime Environment (build 11.0.3+7-post-Raspbian-5)```
	  ```OpenJDK Server VM (build 11.0.3+7-post-Raspbian-5, mixed mode```
	  
	  											
	 use only v1 PBE-SHA1-2DES by this command: ( If use with Ubuntu => invalid key file )
	  
	```
	openssl pkcs8 -topk8 -v1 PBE-SHA1-2DES -in server.key -out server.pem
	```
	  
	  b) For Local Blynk Server running Ubuntu, using
	  
    ```
    java version "11.0.5" 2019-10-15 LTS
    Java(TM) SE Runtime Environment 18.9 (build 11.0.5+10-LTS)
    Java HotSpot(TM) 64-Bit Server VM 18.9 (build 11.0.5+10-LTS, mixed mode)

    ```
													
   use this command to generate pem file: ( If use with RPi => invalid key file )
	  
  ```
  openssl pkcs8 -topk8 -inform PEM -outform PEM -in server.key -out server.pem
  ```
    
   If you connect hardware with USB script you have to provide an option '-s' pointing to "common name" (hostname) you did specified during certificate generation.

   As an output you'll retrieve server.crt and server.pem files that you need to provide for server.ssl properties.

  ```
  server.ssl.cert=./server.pem
  server.ssl.key=./server.pem
  server.ssl.key.pass=your_ssl_key_password
  ```


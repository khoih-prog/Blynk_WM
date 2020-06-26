# Detailed Blynk WiFi Examples

The Arduino/Blynk sketch **Blynk_WM_Template.ino** is a fully-developed get-started demo program for the powerful BlynkSimpleEsp... and the newer WiFiManager (WM) libraries. It demonstrates 
 * **WiFiManager Config Portal** configuration and use
 * **WiFiManager Dynamic (extended) Parameters** configuration and use
 * Use of **compiler constants** for compile-time selection
 * Use of Blynk's **BLYNK_WRITE_DEFAULT()** flexible capability
 
This sketch lets end-users choose a color using ZeRGBa, colors a blinking (heartbeat) LED, and shows the HEX code for that color.

It requires:
 * Blynk ZeRGBa configured in MERGE mode with values between 0 and 255
 * Blynk LED
 * Blynk Value Display
 * Blynk master library installed
 * Blynk_WiFiManager library installed
 * ESP32 or ESP8266 devices
 
As in all Blynk sketches using WiFi, you will need
 * Your WiFi SSID or SSIDs and passwords
 * Your Blynk authcode or authcodes
 * Your Blynk server URL (Main US Blynk server is blynk-cloud.com.)
 
These values do not need to be coded into the sketch as they may be entered at runtime (once) into the Config Portal.
 
You also do not have to hardcode the Virtual Pins for the ZeRGBa, LED or Value Display, can input them at runtime using the Config Portal.
This sketch uses Blynk's BLYNK_WRITE_DEFAULT() capability to deliver this flexibility. I use this approach to manage a number of similar wireless controls like SONOFFs with the same sketch.  
 
The Config Portal will appear as SSID MyConfigPortal, with WiFi password of 12345678 and IP address of 192.168.220.1. 
These three values (Config Portal SSID, password, IP address) are hardcoded into the sketch (but could be made selectable in the Config Portal, itself.)
 
 I hope this is as useful to you as it has been to me to understand Blynk, the BlynkSimpleEsp... and ...WiFiManager libraries, the ESP32 and ESP8266. https://github.com/thorathome/Blynk_Examples

## Blynk_ESP_WM
I'm inspired by [EasyBlynk8266] (https://github.com/Barbayar/EasyBlynk8266)
 
To help you to eliminate hardcoding your Wifi and Blynk credentials for ESP8266 and ESP32 (with / wwithout SSL), and updating/reflashing every time when you need to change them.

Just copy BlynkSimpleEsp8266_WM.h, BlynkSimpleEsp8266_SSL_WM.h, BlynkSimpleEsp32_WM.h and BlynkSimpleEsp32_SSL_WM.h into Blynk libraries directory (normally ./Arduino/libraries/Blynk/src)

In your code, replace
1. BlynkSimpleEsp8266.h     with BlynkSimpleEsp8266_WM.h      for ESP8266 without SSL
2. BlynkSimpleEsp8266_SSL.h with BlynkSimpleEsp8266_SSL_WM.h  for ESP8266 with SSL
3. BlynkSimpleEsp32.h       with BlynkSimpleEsp32_WM.h        for ESP32 without SSL
4. BlynkSimpleEsp32_SSL.h   with BlynkSimpleEsp32_SSL_WM.h    for ESP32 with SSL

and replace

, `Blynk.begin(...)` with `Blynk.begin()` in your code. Keep `Blynk.run()`.

That's it.

## So, how it works?
If it cannot connect to the Blynk server in 30 seconds, it will switch to `Configuration Mode`. You will see your built-in LED turned ON. In `Configuration Mode`, it starts an access point called `ESP_xxxxxx`. Connect to it using password `MyESP_xxxxxx` .

https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Selection_004.jpg

After you connected, please, go to http://192.168.4.1.

https://github.com/khoih-prog/Blynk_WM/blob/master/pics/Selection_005.jpg

Enter your credentials, then click `Save`. After you restarted, you will see your built-in LED turned OFF. That means, it connected to your Blynk server successfully.

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically.

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for graphical user interface.

## Prerequisite
* ESP8266 core for Arduino https://github.com/esp8266/Arduino#installing-with-boards-manager
* Blynk library https://www.arduino.cc/en/guide/libraries#toc3

## Hello World
Please take a look at examples, as well.
```
#include <BlynkSimpleEsp8266_WM.h>

void setup() 
{
    Blynk.begin();
}


void loop() 
{
    Blynk.run();
}
```

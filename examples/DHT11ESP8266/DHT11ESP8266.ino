#include <BlynkSimpleEsp8266_WM.h>
#include <DHT.h>

#define DHT_PIN     2
#define DHT_TYPE    DHT11

#define DHT_DEBUG   1

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

void readAndSendData() 
{
    float temperature = dht.readTemperature();
    float humidity    = dht.readHumidity();
    

    if (!isnan(temperature) && !isnan(humidity)) 
    {
      Blynk.virtualWrite(V0, temperature);
      Blynk.virtualWrite(V1, humidity);
    }
    else
    {
      Blynk.virtualWrite(V0, -100);
      Blynk.virtualWrite(V1, -100);
    }
}

void setup() 
{
    dht.begin();
    Blynk.begin();
    timer.setInterval(60 * 1000, readAndSendData);
}

void loop() 
{
    Blynk.run();
    timer.run();
}

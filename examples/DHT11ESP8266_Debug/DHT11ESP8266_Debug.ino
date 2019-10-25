#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266_WM.h>
#include <Ticker.h>
#include <DHT.h>

#define DHT_PIN     2
#define DHT_TYPE    DHT11

#define DHT_DEBUG   1

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;
Ticker     aux_ticker;

void readAndSendData() 
{
    float temperature = dht.readTemperature();
    float humidity    = dht.readHumidity();
    

    if (!isnan(temperature) && !isnan(humidity)) 
    {
      Blynk.virtualWrite(V17, temperature);
      Blynk.virtualWrite(V18, humidity);
    }
    else
    {
      Blynk.virtualWrite(V17, -100);
      Blynk.virtualWrite(V18, -100);
    }
}

#define PIN_LED   2 // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED

void set_led(byte status)
{
  digitalWrite(PIN_LED  /*LED_BUILTIN*/, status);
 }

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     15000L

  // Send status report every STATUS_REPORT_INTERVAL (10) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // report status to Blynk
    if (Blynk.connected())
    {
      set_led(LOW);
      aux_ticker.once_ms(111, set_led, (byte) HIGH);

      Serial.println("B");
    }
    else
    {
      Serial.println("F");
    }

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup() 
{
    // Debug console
    Serial.begin(115200);
    dht.begin();
    Blynk.begin();
    timer.setInterval(60 * 1000, readAndSendData);

    if (Blynk.connected())
    {
       Serial.println("Blynk connected. Board Name : " + Blynk.getBoardName());
    }
}

void loop() 
{
    Blynk.run();
    timer.run();
    check_status();
}

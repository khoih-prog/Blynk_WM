#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32_WM.h>
#include <Ticker.h>
#include <DHT.h>

#define PIN_D22   22            // Pin D22 mapped to pin GPIO22/SCL of ESP32
  
#define DHT_PIN     PIN_D22     // pin DATA @ D22 / GPIO22
#define DHT_TYPE    DHT11

#define DHT_DEBUG   1

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;
Ticker     led_ticker;

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

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
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
      led_ticker.once_ms(111, set_led, (byte) HIGH);

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
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("\nStarting ...");
    
    dht.begin();
    Blynk.begin();
    timer.setInterval(60 * 1000, readAndSendData);

    if (Blynk.connected())
    {
       Serial.println("\nBlynk ESP32 connected. Board Name : " + Blynk.getBoardName());
    }
}

void loop() 
{
    Blynk.run();
    timer.run();
    check_status();
}

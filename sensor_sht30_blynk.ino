#define BLYNK_TEMPLATE_ID "TMPLJuP_R2V9"
#define BLYNK_DEVICE_NAME "SHT30"
#define BLYNK_AUTH_TOKEN "WmFViDHNvCZfg1WQvAyLEwpiNrDdiAkw"
#define BLYNK_PRINT Serial

#include <SPI.h>
#include "Wire.h"
#include "SHT31.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

uint32_t start;
uint32_t stop;

SHT31 sht;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KMTek"; //nama wifi
char pass[] = "KMTek123"; //password wifi

BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  Wire.begin();

  sht.begin(0x44);    //Sensor I2C Address

  Wire.setClock(100000);
  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}

void loop()
{
  Blynk.run();
  timer.run();
  sht.read();

  Serial.print("Temperature:");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.print("Humidity:");
  Serial.println(sht.getHumidity(), 1);
  delay(1000 );

  Blynk.virtualWrite(V1,sht.getTemperature());
  Blynk.virtualWrite(V2, sht.getHumidity());
  delay(1000);

}

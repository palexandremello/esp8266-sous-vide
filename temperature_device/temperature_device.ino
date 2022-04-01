#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
float setMaxTemperatureCokking = 60;
bool isCooking = true;

OneWire barramento(D4);
DallasTemperature sensor(&barramento);

float getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);

}

void setup()
{
   Serial.begin(115200);
   sensor.begin();
   WiFiManager wifiManager;
   wifiManager.resetSettings();
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");

}

void loop()
{
  while (isCooking) {
    float temp = getTemperature(sensor);
    if (temp >= setMaxTemperatureCokking) {
      Serial.println("DEACTIVATE RELE COOKING POT");
      Serial.println(temp);
    } else {
      Serial.println("ACTIVATE RELE COOKING POT");
      Serial.println(temp);
    }

    delay(1000);
  }
}

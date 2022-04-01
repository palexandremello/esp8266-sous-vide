#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
#include "temperature.h"

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long timingCooking = 300000;
void setup()
{
   Serial.begin(115200);
   sensor.begin();
   WiFiManager wifiManager;
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");
   startMillis = millis();  //initial start time

}

void loop()
{
  while (isCooking) {
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    Serial.println(currentMillis);
    Serial.println(timingCooking);
    if (currentMillis <= timingCooking) {
      
        float temp = getTemperature(sensor);
        if (temp >= setMaxTemperatureCokking) {
          Serial.println("DEACTIVATE RELE COOKING POT");
          Serial.println(temp);
        } else {
          Serial.println("ACTIVATE RELE COOKING POT");
          Serial.println(temp);
          }
          
          delay(1000);
          }  else {
      isCooking = false;
    }
    }
}

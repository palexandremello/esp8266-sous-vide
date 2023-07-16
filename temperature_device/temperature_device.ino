#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
#include "temperature.h"
#include "cooking_pot.h"

#define LED_PIN 16
#define MAX_TEMPERATURE 20
unsigned long timingCooking = 300000;
bool isReleActivate = false;


TimerCooker timer_cooker(timingCooking);
TemperatureSensor temperature_sensor;
CookingPot cooking_pot(MAX_TEMPERATURE, LED_PIN);

void setup()
{
   Serial.begin(115200);
   WiFiManager wifiManager;
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");
   timer_cooker.startTimer();
   temperature_sensor.setup();
   cooking_pot.setup();

}


void loop()
{
  float temperature = temperature_sensor.getTemperature();

  if (timer_cooker.isTimeUp()) {
    Serial.println("Time's up!!");
  } else {
    cooking_pot.isReachMaxTemperature(temperature);
    cooking_pot.checkRele();
  }

  timer_cooker.printRemainingTime();
}
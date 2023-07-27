#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
#include <PubSubClient.h>
#include "temperature.h"
#include "cooking_pot.h"
#include "timer.h"
#include "secrets.h"
#include "sous_vide_orchestrator.h"

#define LED_PIN 16
#define MAX_TEMPERATURE 58
unsigned long timingCooking =  20 * 60 * 60 * 1000;


TimerCooker timer_cooker(timingCooking);
TemperatureSensor temperature_sensor;
CookingPot cooking_pot(MAX_TEMPERATURE, LED_PIN);

SousVideOrchestrator sous_vide_orchestrator(temperature_sensor, timer_cooker, cooking_pot, MAX_TEMPERATURE);
void setup()
{
   Serial.begin(115200);
   WiFiManager wifiManager;
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");
   sous_vide_orchestrator.setup();


}

void loop()
{


  sous_vide_orchestrator.update();



}

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "timer.h"
#include "secrets.h"
#include "temperature.h"
#include "pid_control.h"
#include "mqtt_command_listener.h"
#include "mqtt_publisher_interface.h"
#include "cooking_pot.h"
#include "mqtt_manager.h"
#include "warmup_controller.h"
#include "sous_vide_orchestrator.h"

#define RELE_PIN 16
#define MAX_TEMPERATURE 0
unsigned long timingCooking =  0;

// Initialize MQTTManager
MQTTManager mqttManager(MQTT_SERVER);

TimerCooker timer_cooker(timingCooking);
TemperatureSensor temperature_sensor;
CookingPot cooking_pot(RELE_PIN);
WarmupController warmup_controller(cooking_pot, MAX_TEMPERATURE * 0.9);
SousVideOrchestrator sous_vide_orchestrator(temperature_sensor, timer_cooker, cooking_pot, mqttManager, warmup_controller, MAX_TEMPERATURE);
mqttManager.setCommandListener(&sous_vide_orchestrator);  

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  if(!wifiManager.autoConnect("SousVideHomeMade")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  sous_vide_orchestrator.setup();
}

void loop() {
  sous_vide_orchestrator.update();
  mqttManager.loop();
}

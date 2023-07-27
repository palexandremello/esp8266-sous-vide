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

#define RELE_PIN 16
#define MAX_TEMPERATURE 58
unsigned long timingCooking =  20 * 60 * 60 * 1000;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

unsigned long previousMillis = 0;
const long interval = 1000;


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("sousvide/temperature", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("sousvide/temperature");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

TimerCooker timer_cooker(timingCooking);
TemperatureSensor temperature_sensor;
CookingPot cooking_pot(MAX_TEMPERATURE, RELE_PIN);

SousVideOrchestrator sous_vide_orchestrator(temperature_sensor, timer_cooker, cooking_pot, MAX_TEMPERATURE);
void setup()
{
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

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

   sous_vide_orchestrator.setup();


}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    client.publish("sousvide/temperature", "Como um furacão, devasta");
    sous_vide_orchestrator.update();

  }




}

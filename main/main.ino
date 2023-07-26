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
#define MAX_TEMPERATURE 63.0
unsigned long timingCooking = 3600000;


WiFiClient espClient;                                                   
PubSubClient client(espClient);                                         
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length) {        
  Serial.print("Mensagem recebida [");                                  
  Serial.print(topic);                                                  
  Serial.print("] ");                                                   
  for (int i = 0; i < length; i++) {                                    
    Serial.print((char)payload[i]);                                     
  }
  Serial.println();                                                     

  if ((char)payload[0] == '1') {                                        
    digitalWrite(BUILTIN_LED, LOW);                                     
  } else {                                                              
    digitalWrite(BUILTIN_LED, HIGH);                                    
  }

}


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

   client.setServer(MQTT_SERVER, MQTT_PORT);
   client.setCallback(callback);



}

void loop()
{

  client.loop();                                                         

  sous_vide_orchestrator.update();

  client.publish("sousvide/temperature", "Hello World");                        


}
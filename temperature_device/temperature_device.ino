#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
#include "temperature.h"
#include "cooking_pot.h"

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long timingCooking = 300000;
bool isReleActivate = false;

class TimerCooker {

  private:
    unsigned long startTime;
    unsigned long timingCooking;

  public:
  TimerCooker(unsigned long timeToCook) {
    timingCooking = timeToCook;
  }

  void startTimer() {
    startTime = millis();
  }

  bool isTimeUp() {
    unsigned long elapsedMillis = millis() - startTime;
    return (elapsedMillis >= timingCooking);
  }

};

TimerCooker timer_cooker(60000);
TemperatureSensor temperature_sensor;
CookingPot cooking_pot(65);
void setup()
{
   Serial.begin(115200);
   WiFiManager wifiManager;
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");
   timer_cooker.startTimer();
   temperature_sensor.setup();

}



void loop()
{
  float temperature = temperature_sensor.getTemperature();
  Serial.println("Temperature now is: " + String(temperature) + "ºC");

  if (timer_cooker.isTimeUp()) {
    Serial.println("Time's up!!");
  } else {
    cooking_pot.isReachMaxTemperature(temperature);
    if (cooking_pot.getTemperatureReached()) {
      Serial.println("Temperature now is: " + String(temperature) + "ºC");
      Serial.println("Reached limited, deactivate cooking pot");
    }
  }

}


//  while (isCooking) {
//    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
//
//    timer_cooker.execute_time();Informações Gerais: O conjunto de dados contém 1168 entradas e 18 colunas. Não há nenhum valor ausente em nenhuma das colunas.


//     
//        float temp = getTemperature(sensor);
 //       Serial.println(temp);
 //       if (temp >= setMaxTemperatureCokking) {
   //       Serial.println("DEACTIVATE RELE COOKING POT");
     //     isReleActivate = false;
       // } else {
         // if (!isReleActivate) {
           //   Serial.println("ACTIVATE RELE COOKING POT");
             // isReleActivate = true;

          //} else {
          //}
          //}
          
          //}  else {
      //isCooking = false;
    //}
    //delay(1000);
    //}

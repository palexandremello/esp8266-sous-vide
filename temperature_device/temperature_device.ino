#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager​
#include "temperature.h"

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

void setup()
{
   Serial.begin(115200);
   sensor.begin();
   WiFiManager wifiManager;
   wifiManager.autoConnect("SousVideHomeMade");
   Serial.println("connected :)");
   timer_cooker.startTimer();

}



void loop()
{
  if (timer_cooker.isTimeUp()) {
    Serial.println("Time's up!!");
  } else {
    Serial.println("Still cooking!!");
  }
}


//  while (isCooking) {
//    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
//
//    timer_cooker.execute_time();
//    if (currentMillis <= timingCooking) {
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

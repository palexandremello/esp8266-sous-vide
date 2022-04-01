#include "temperature.h"

void setup()
{
   Serial.begin(115200);
   sensor.begin(); 
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

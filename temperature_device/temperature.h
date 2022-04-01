#include <OneWire.h>
#include <DallasTemperature.h>

float setMaxTemperatureCokking = 60;
bool isCooking = true;

OneWire barramento(D4);
DallasTemperature sensor(&barramento);

float getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);

}

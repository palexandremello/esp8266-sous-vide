#include <OneWire.h>
#include <DallasTemperature.h>
#define D3 0

float setMaxTemperatureCokking = 60;
bool isCooking = true;

OneWire barramento(D3);
DallasTemperature sensor(&barramento);

float getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);

}

#include <OneWire.h>
#include <DallasTemperature.h>
#define D3 0


class TemperatureSensor {
  private:
    OneWire barramento;
    DallasTemperature sensor;
    float maxTemperatureCooking;

  
  public:
     TemperatureSensor(float maxTemperatureCooking) : barramento(D3), sensor(&barramento) {
      this->maxTemperatureCooking = maxTemperatureCooking;
     }


     void setup() {
      sensor.begin();
     }
     

     float getTemperature() {
      float temperaturesSamples = 0;
      float maxSamples = 10;
      for (int i = 0; i < maxSamples; i++) {
        sensor.requestTemperatures();
        float t = sensor.getTempCByIndex(0);
        temperaturesSamples += t;
      }

      return temperaturesSamples / maxSamples;
     }
};


float setMaxTemperatureCokking = 60;
bool isCooking = true;

OneWire barramento(D3);
DallasTemperature sensor(&barramento);

float getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);

}

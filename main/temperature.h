#include <OneWire.h>
#include <DallasTemperature.h>
#define D3 0

class TemperatureSensor {
  private:
    OneWire barramento;
    DallasTemperature sensor;
  
  public:
    TemperatureSensor() : barramento(D3), sensor(&barramento) {
    }

    void setup() {
      sensor.begin();
    }

    float getTemperature() {
      sensor.requestTemperatures();
      return sensor.getTempCByIndex(0);
    }
};

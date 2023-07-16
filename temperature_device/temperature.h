#include <OneWire.h>
#include <DallasTemperature.h>
#define D3 0
#define MAX_SAMPLES 10


class TemperatureSensor {
  private:
    OneWire barramento;
    DallasTemperature sensor;
    float temperaturesSamples[MAX_SAMPLES] = {0.0};
    int currentSampleIndex;
    int sampleCount;
  
  public:
     TemperatureSensor() : barramento(D3), sensor(&barramento) {
      this->currentSampleIndex = 0;
      this->sampleCount = 0;
     }


     void setup() {
      sensor.begin();
     }

     void addSample(float sample) {
      temperaturesSamples[currentSampleIndex] = sample;
      currentSampleIndex = (currentSampleIndex + 1) % MAX_SAMPLES;
      
      if (sampleCount < MAX_SAMPLES) {
        sampleCount++;
      }

     }
     
     float getAverageTemperature() {
      float total = 0;
      for (int i = 0; i < sampleCount; i++) {
        total += temperaturesSamples[i];
      }

      return total / sampleCount;
     }

     float getTemperature() {
        sensor.requestTemperatures();
        float t = sensor.getTempCByIndex(0);
        addSample(t);
        return getAverageTemperature();
     }
};



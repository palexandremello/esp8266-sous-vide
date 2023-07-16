#include <OneWire.h>
#include <DallasTemperature.h>
#define D3 0
#define MAX_SAMPLES 10


class TemperatureSensor {
  private:
    OneWire barramento;
    DallasTemperature sensor;
    float maxTemperatureCooking;
    float temperaturesSamples[MAX_SAMPLES];
    int currentSampleIndex;
    int sampleCount;
  
  public:
     TemperatureSensor(float maxTemperatureCooking) : barramento(D3), sensor(&barramento) {
      this->maxTemperatureCooking = maxTemperatureCooking;
      this->currentSampleIndex = 0;
      this->sampleCount = 0;
     }


     void setup() {
      sensor.begin();
     }

     void addSample(float sample) {
      temperaturesSamples[currentSampleIndex] = sample;
      Serial.print("Adicionando amostra no índice ");
      Serial.print(currentSampleIndex);
      Serial.print(": ");
      Serial.println(sample);

      currentSampleIndex = (currentSampleIndex + 1) % MAX_SAMPLES;
      
      if (sampleCount < MAX_SAMPLES) {
        sampleCount++;
      }

          // Imprimir todo o buffer circular após a adição da nova amostra
      Serial.println("Estado atual do buffer circular:");
      for (int i = 0; i < sampleCount; i++) {
           Serial.print("Índice ");
           Serial.print(i);
           Serial.print(": ");
           Serial.println(temperaturesSamples[i]);
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



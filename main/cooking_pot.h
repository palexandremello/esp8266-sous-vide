

class CookingPot {

    private:
      float maxTemperatureCooking;
      bool reachedTemperature = false;
      bool isReleActivate = false;
      bool previousReleStatus = false;
      int relayPin;

    
    public:
      CookingPot(float maxTemperatureCooking, int relayPin) {
        this->maxTemperatureCooking = maxTemperatureCooking;
        this->relayPin = relayPin;
      }

      void setup() {
        pinMode(relayPin, OUTPUT);

      }

      void isReachMaxTemperature(float temperature) {
        reachedTemperature =  temperature >= maxTemperatureCooking;
      }

      void setReleStatus() {
        Serial.println(reachedTemperature);
        Serial.println(isReleActivate);
        if (!reachedTemperature && !isReleActivate) {
          isReleActivate = true;
        } else if (reachedTemperature && isReleActivate) {
          isReleActivate = false;
        } 
      }

      bool getReleStatus() {
        return isReleActivate;
      }

      void checkRele() {
        setReleStatus();

         digitalWrite(relayPin, isReleActivate ? LOW : HIGH);
      }

      bool getTemperatureReached() {
        return reachedTemperature;
      }

};

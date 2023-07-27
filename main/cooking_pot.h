

class CookingPot {

    private:
      float maxTemperatureCooking;
      bool reachedTemperature = false;
      bool isReleActivate = false;
      bool previousReleStatus = false;
      int relePin;

    
    public:
      CookingPot(float maxTemperatureCooking, int relePin) {
        this->maxTemperatureCooking = maxTemperatureCooking;
        this->relePin = relePin;
      }

      void setup() {
        pinMode(relePin, OUTPUT);

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

      void checkRele() {
        setReleStatus();

         digitalWrite(relePin, isReleActivate ? LOW : HIGH);
      }

      bool getTemperatureReached() {
        return reachedTemperature;
      }

};

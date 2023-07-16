

class CookingPot {

    private:
      float maxTemperatureCooking;
      bool reachedTemperature = false;
      bool isReleActivate = false;

    
    public:
      CookingPot(float maxTemperatureCooking) {
        this->maxTemperatureCooking = maxTemperatureCooking;
      }


      void isReachMaxTemperature(float temperature) {
        reachedTemperature =  temperature >= maxTemperatureCooking;
      }

      void activateRele() {

        if (reachedTemperature && !isReleActivate) {
          Serial.println("Activate rele");
          isReleActivate = true;
        } else {
          Serial.println("Deactivate rele");
          isReleActivate = false;
        }
      }

      bool getTemperatureReached() {
        return reachedTemperature;
      }

};
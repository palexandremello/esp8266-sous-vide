

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

        if (!reachedTemperature && !isReleActivate) {
          Serial.println("Activate rele");
          isReleActivate = true;
        } else if (reachedTemperature && isReleActivate) {
          Serial.println("Deactivate rele");
          isReleActivate = false;
        } 
      }

      void checkRele() {
        setReleStatus();

        if (previousReleStatus != isReleActivate){
          digitalWrite(relePin, isReleActivate ? HIGH : LOW);
          previousReleStatus = isReleActivate;
        }
      }

      bool getTemperatureReached() {
        return reachedTemperature;
      }

};
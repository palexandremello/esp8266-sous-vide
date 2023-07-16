

class CookingPot {

    private:
      float maxTemperatureCooking;
      bool isReleActivate = false;

    
    public:
      CookingPot(float maxTemperatureCooking) {
        this->maxTemperatureCooking = maxTemperatureCooking;
      }


      bool isReachMaxTemperature(float temperature) {
        return temperature >= maxTemperatureCooking;
      }

};
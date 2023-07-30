

class CookingPot {

    private:
      bool isRelayActivate = false;
      int relayPin;

    
    public:
      CookingPot(int relayPin) {
        this->relayPin = relayPin;
      }

      void setup() {
        pinMode(relayPin, OUTPUT);

      }

      void setRelayStatus(bool activate) {
        isReleActivate = activate;
      }

      bool getReleStatus() {
        return isReleActivate;
      }

      void checkRele() {
        digitalWrite(relayPin, isReleActivate ? LOW : HIGH);
      }

};

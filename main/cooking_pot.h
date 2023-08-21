

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
        digitalWrite(relayPin, HIGH); 

      }

      void setRelayStatus(bool activate) {
        isRelayActivate = activate;
      }

      bool getReleStatus() {
        return isRelayActivate;
      }

      void checkRele() {
        digitalWrite(relayPin, isRelayActivate ? LOW : HIGH);
      }

};

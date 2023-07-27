#include "secrets.h"

class WiFiConnection {
    private:
      WiFiManager wifiManager;
    

    public:
     void setup() {

        if (!wifiManager.autoConnect(AUTO_AP_SOUSVIDE)) {
            Serial.println("failed to connect, we should reset as see if it connects");
            delay(3000);
            ESP.reset();
            delay(5000);
        }

        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
     }
}
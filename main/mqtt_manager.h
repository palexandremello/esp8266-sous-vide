class MQTTManager : public MQTTPublisherInterface {

private:
    WiFiClient espClient;
    PubSubClient client;
    MQTTCommandListener* listener;
    long lastMsg = 0;

public:
    static MQTTManager* instance;

    MQTTManager(const char* mqtt_server) : client(espClient) {
        client.setServer(mqtt_server, MQTT_PORT);
        client.setCallback(MQTTManager::staticCallback);
        MQTTManager::instance = this;

    }

    void setCommandListener(MQTTCommandListener* listener) {
        this->listener = listener;
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Attempting MQTT connection...");

            if (client.connect(MQTT_SOUSVIDE_TEMPERATURE, MQTT_USER, MQTT_PASSWORD)) {
                Serial.println("connected");
                client.subscribe(MQTT_PARAMS_COOKING);
                client.subscribe(PID_METRICS)
                Serial.println("Subscribed to topic: " + String(MQTT_PARAMS_COOKING));
            } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
            }
        } 
    }

    void loop() {
        if (!client.connected()) { 
            reconnect();
        }
        client.loop();
    }

    static void staticCallback(char* topic, byte* message, unsigned int length) {
        Serial.println("Entered callback");
        
          Serial.print("Message arrived on topic: ");
          Serial.print(topic);
          Serial.print(". Message: ");
          String messageTemp;
          
          for (int i = 0; i < length; i++) {
              Serial.print((char)message[i]);
              messageTemp += (char)message[i];
          }
          Serial.println();

          StaticJsonDocument<200> doc;
          deserializeJson(doc, messageTemp);

          float temp = doc["temperature"].as<float>();
          unsigned long timer = doc["timer"].as<unsigned long>();
          bool startCooking = doc["startCooking"].as<bool>();
          if (MQTTManager::instance->listener) {
              MQTTManager::instance->listener->onSetTemperature(temp);
              MQTTManager::instance->listener->onSetTimer(timer);
              if (startCooking) {
                  MQTTManager::instance->listener->onStartCooking();
              }
          }  
    }

    void publishMetrics(float temperature, unsigned long remainingTime, bool isReleOn, bool isWarmupCompleted, bool isCookingStarted) override {
        StaticJsonDocument<200> doc;
        doc["temperature"] = temperature;
        doc["remainingTime"] = remainingTime;
        doc["isReleOn"] = isReleOn;
        doc["isWarmupCompleted"] = isWarmupCompleted;
        doc["isCookingStarted"] = isCookingStarted;
        String payload;
        serializeJson(doc, payload);
        client.publish(MQTT_SOUSVIDE_TEMPERATURE, payload.c_str());
    }
};
MQTTManager* MQTTManager::instance = nullptr;

class MQTTManager : public MQTTPublisherInterface {

    private:
      WiFiClient espClient;
      PubSubClient client;
      MQTTCommandListener* listener;
      long lastMsg = 0;

    public:
      MQTTManager(const char* mqtt_server) : client(espClient) {

        client.setServer(mqtt_server, MQTT_PORT);
        client.setCallback([this](char* topic, byte* message, unsigned int length) {
        this->callback(topic, message, length);
        });
      }

      void setCommandListener(MQTTCommandListener* listenerPtr) {
        listener = listenerPtr;
      }

      void reconnect() {
        while (!client.connected()) {
            Serial.print("Attempting MQTT connection...");

            if (client.connect(MQTT_SOUSVIDE_TEMPERATURE, MQTT_USER, MQTT_PASSWORD)) {
                Serial.println("connected");

                client.subscribe(MQTT_PARAMS_COOKING);
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

      void callback(char* topic, byte* message, unsigned int length) {
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;
        for (int i = 0; i < length; i++) {
            Serial.print((char)message[i]);
            messageTemp += (char)message[i];
        }
        Serial.println();

        if (commandListener) {
          if (String (topic) == SET_TEMPERATURE_TOPIC) {
             float temp = messageTemp.toFloat();
             listener->onSetTemperature(temp);

          } else if (String(topic) == SET_TIMER_TOPIC) {
             unsigned long duration = messageTemp.toInt();
             listener->onSetTimer(duration);

          } else if (String(topic) == START_COOKING_TOPIC) {
             listener->onStartCooking();
           }

        }
      }

      void publishMetrics(float temperature, long remainingTime, bool isReleOn, bool isWarmupCompleted, bool isCookingStarted) {
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
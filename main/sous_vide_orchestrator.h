class SousVideOrchestrator {


    private:
       TemperatureSensor& temperatureSensor;
       TimerCooker& timerCooker;
       CookingPot& cookingPot;
       MQTTManager& mqttManager;
       bool isTimerStarted;
       bool isWarmupCompleted = false;
       const float MAX_TEMPERATURE_COOKING;
       const float START_THRESHOLD;

    
    public:
      SousVideOrchestrator(TemperatureSensor& temperatureSensor, TimerCooker& timerCooker, CookingPot& cookingPot, MQTTManager& mqttManager, float maxTemperature) 
      : temperatureSensor(temperatureSensor), timerCooker(timerCooker), cookingPot(cookingPot), mqttManager(mqttManager) ,MAX_TEMPERATURE_COOKING(maxTemperature), START_THRESHOLD(maxTemperature * 0.9) {
        this->isTimerStarted = false;
      }

      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

      void update() {
        float temperature = temperatureSensor.getTemperature();

        warmupController.warmup(temperature);

        if (warmupController.isWarmupDone()) {
            if (temperature >= MAX_TEMPERATURE_COOKING) {
              timerCooker.startTimer();
              isTimerStarted = true;
            } else if (temperature <= START_THRESHOLD) {
                cookingPot.setReleStatus(true);

            }

        }
        Serial.println("isTimerStarted: ", isTimerStarted);
        if (isTimerStarted) {
          cookingPot.isReachMaxTemperature(temperature);
          cookingPot.checkRele();
          Serial.print("Temperatura Atual: ");
          Serial.println(temperature);
          timerCooker.printRemainingTime();
          mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus());

          if (timerCooker.isTimeUp()) {
              Serial.println("Time's up!!");
              isTimerStarted = false;
          }
  
  }

};


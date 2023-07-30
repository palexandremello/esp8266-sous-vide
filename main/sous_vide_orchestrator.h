class SousVideOrchestrator {


    private:
       TemperatureSensor& temperatureSensor;
       TimerCooker& timerCooker;
       CookingPot& cookingPot;
       WarmupController& warmupController;
       MQTTManager& mqttManager;
       bool isTimerStarted;
       bool isWarmupCompleted = false;
       const float MAX_TEMPERATURE_COOKING;
       const float START_THRESHOLD;

    
    public:
      SousVideOrchestrator(TemperatureSensor& temperatureSensor, TimerCooker& timerCooker,
                           CookingPot& cookingPot, MQTTManager& mqttManager, 
                           WarmupController& warmupController, float maxTemperature) 
      : temperatureSensor(temperatureSensor), timerCooker(timerCooker), 
        cookingPot(cookingPot), mqttManager(mqttManager) ,
        warmupController(warmupController), MAX_TEMPERATURE_COOKING(maxTemperature), 
        START_THRESHOLD(double(maxTemperature * 0.9)) {
        this->isTimerStarted = false;
      }

      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

      void update() {
        float temperature = temperatureSensor.getTemperature();

        if (!warmupController.isWarmupDone()) {
          warmupController.warmup(temperature);

          mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus());
        } else {

          if (!isTimerStarted && temperature >= MAX_TEMPERATURE_COOKING) {
            timerCooker.startTimer();
            isTimerStarted = true;
            cookingPot.setRelayStatus(false);
            cookingPot.checkRele();
          } else if (temperature < MAX_TEMPERATURE_COOKING) {
            cookingPot.setRelayStatus(true);
            cookingPot.checkRele();

          }

          mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus());

        }

        if (isTimerStarted && timerCooker.isTimeUp()) {
            Serial.println("Time's up!!");
            isTimerStarted = false;
            cookingPot.setRelayStatus(false);
            cookingPot.checkRele();
        }

  }

};


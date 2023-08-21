class SousVideOrchestrator: public MQTTCommandListener {


    private:
       TemperatureSensor& temperatureSensor;
       TimerCooker& timerCooker;
       CookingPot& cookingPot;
       WarmupController& warmupController;
       MQTTManager& mqttManager;
       PIDController& pidController;
       bool isTimerStarted;
       bool timerHasBeenStarted;
       bool isCookingStarted;
       bool isWarmupCompleted = false;
       float MAX_TEMPERATURE_COOKING;
       float START_THRESHOLD;
       bool newReleStatus;

    
    public:
      SousVideOrchestrator(TemperatureSensor& temperatureSensor, TimerCooker& timerCooker,
                           CookingPot& cookingPot, MQTTManager& mqttManager, 
                           WarmupController& warmupController, PIDController& pidController, float maxTemperature) 
      : temperatureSensor(temperatureSensor), timerCooker(timerCooker), 
        cookingPot(cookingPot), mqttManager(mqttManager) ,
        warmupController(warmupController), 
        pidController(pidController),
        MAX_TEMPERATURE_COOKING(maxTemperature), 
        START_THRESHOLD(double(maxTemperature * 0.9)) {
        this->isTimerStarted = false;
        this->timerHasBeenStarted = false;
        this-> newReleStatus = false;
        this-> isCookingStarted = false;
      }

      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

void update() {
    if (!isCookingStarted){
      return;
    }
    float temperature = temperatureSensor.getTemperature();
    bool isWarmupDone = warmupController.isWarmupDone();
    
    if (!isWarmupDone) {
        warmupController.warmup(temperature);
        mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), isWarmupDone, isWarmupDone);
    } else {
        if (!timerHasBeenStarted && temperature >= MAX_TEMPERATURE_COOKING) {
            timerCooker.startTimer();
            isTimerStarted = true;
            timerHasBeenStarted = true;
        }

        ControlState newReleStatus = pidController.compute(MAX_TEMPERATURE_COOKING, temperature);
        cookingPot.setRelayStatus(newReleStatus == ON);
        cookingPot.checkRele();
        mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), isWarmupDone, isWarmupDone);
    }

    if (isTimerStarted && timerCooker.isTimeUp()) {
        Serial.println("Time's up!!");
        isTimerStarted = false;
        cookingPot.setRelayStatus(OFF);
    }
}

  void onSetTemperature(float temp) override {
    MAX_TEMPERATURE_COOKING = temp;
    START_THRESHOLD = temp * 0.9;
    warmupController.setStartThreshold(START_THRESHOLD);
    isWarmupCompleted = false;
  }

  void onSetTimer(unsigned long duration) override {
    timerCooker.setTimer(duration);

    if (isTimerStarted) {
      timerCooker.resetTimer();
      isTimerStarted = false;
      timerHasBeenStarted = false;
      isCookingStarted = false;
    }
  }

  void onStartCooking() override {
    Serial.println("Received Start Cooking Command.");
    isCookingStarted = true;
    isWarmupCompleted = false;
    isTimerStarted = false;
    timerHasBeenStarted = false;
  }

};


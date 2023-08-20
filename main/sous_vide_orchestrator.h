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
        PIDController(pidController),
        MAX_TEMPERATURE_COOKING(maxTemperature), 
        START_THRESHOLD(double(maxTemperature * 0.9)) {
        this->isTimerStarted = false;
        this->timerHasBeenStarted = false;
        this-> newReleStatus = false;
      }

      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

      void update() {
        float temperature = temperatureSensor.getTemperature();

        if (!warmupController.isWarmupDone()) {
          warmupController.warmup(temperature);
          mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), true, false);
        } else {

        if (!timerHasBeenStarted && temperature >= MAX_TEMPERATURE_COOKING) {
            timerCooker.startTimer();
            isTimerStarted = true;
            timerHasBeenStarted = true;
            mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), false, true);
        }

        ControlState newReleStatus = pidController.compute(MAX_TEMPERATURE_COOKING, temperature);
        cookingPot.setRelayStatus(newReleStatus == ON);
        cookingPot.checkRele();
        mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), false, true);
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
      timerHasBeensStarted = false;
    }
  }

  void onStartCooking() override {
    isWarmupCompleted = false;
    isTimerStarted = false;
    timerHasBeenStarted = false;
  }

};


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

        if (!isWarmupCompleted) {
          if (temperature >= START_THRESHOLD) {
            isWarmupCompleted = true;
            timerCooker.startTimer();
            cookingPot.checkRele();
          } else {
            c
          }
        }
};


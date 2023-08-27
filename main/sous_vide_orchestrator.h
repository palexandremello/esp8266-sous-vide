#include "sousvide_state.h"

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
       SousVideState currentState;

    
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
        this->currentState = IDLE;
      }

      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

void update() {

    float temperature = temperatureSensor.getTemperature();

    switch (currentState) {
       case IDLE:
           Serial.println("State: IDLE");
           break;
       case WARMUP:
            Serial.println("State: WARMUP");

           warmupController.warmup(temperature);
           cookingPot.checkRele();
           mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), true, false);
           
           if (temperature >= START_THRESHOLD) {
               Serial.println("Transitioning to COOKING state.");
               currentState = COOKING;
               timerCooker.startTimer();
           }
           break;
       case COOKING:
            Serial.println("State: COOKING");

           ControlState newReleStatus = pidController.compute(MAX_TEMPERATURE_COOKING, temperature);
           cookingPot.setRelayStatus(newReleStatus == ON);
           cookingPot.checkRele();
           mqttManager.publishMetrics(temperature, timerCooker.getRemainingTimeMillis(), cookingPot.getReleStatus(), false, true);
           if (timerCooker.isTimeUp()) {
               Serial.println("Time's up!!");
               cookingPot.setRelayStatus(false);
               cookingPot.checkRele();
               currentState = IDLE;
           }
           break;
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
    }
  }

  void onStartCooking() override {
    Serial.println("Received Start Cooking Command.");
    currentState = WARMUP;
  }

  void reset() {
    isCookingStarted = false;
    isWarmupCompleted = false;
    isTimerStarted = false;
    timerHasBeenStarted = false;
    MAX_TEMPERATURE_COOKING = 0; 

  }

};


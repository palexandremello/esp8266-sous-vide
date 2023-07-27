class SousVideOrchestrator {


    private:
       TemperatureSensor& temperatureSensor;
       TimerCooker& timerCooker;
       CookingPot& cookingPot;
       bool isTimerStarted;
       const float MAX_TEMPERATURE_COOKING;
       const float START_THRESHOLD;

    
    public:
      SousVideOrchestrator(TemperatureSensor& temperatureSensor, TimerCooker& timerCooker, CookingPot& cookingPot, float maxTemperature) 
      : temperatureSensor(temperatureSensor), timerCooker(timerCooker), cookingPot(cookingPot), MAX_TEMPERATURE_COOKING(maxTemperature), START_THRESHOLD(maxTemperature * 0.9) {
        this->isTimerStarted = false;
      }


      void setup() {
        temperatureSensor.setup();
        cookingPot.setup();
      }

      void update() {
        float temperature = temperatureSensor.getTemperature();

        if (!isTimerStarted && temperature >= START_THRESHOLD) {
          timerCooker.startTimer();
          isTimerStarted = true;
        } else {
            Serial.print("Temperatura Atual: ");
            Serial.println(temperature);

        }

        if (isTimerStarted) {
            cookingPot.isReachMaxTemperature(temperature);
            cookingPot.checkRele();
            Serial.print("Temperatura Atual: ");
            Serial.println(temperature);
            timerCooker.printRemainingTime();

            if (timerCooker.isTimeUp()) {
              Serial.println("Time's up!!");
              isTimerStarted = false;
            }

        }
      }
};
#include "limits.h"
class TimerCooker {

  private:
    unsigned long startTime;
    bool timerStarted = false;
    unsigned long timingCooking;
    unsigned long elapsedMillis;
    String previousRemainingTime;
    int elapsedMinutes;

void setElapsedTime() {
    unsigned long currentMillis = millis();
    if (currentMillis >= startTime) {
        elapsedMillis = currentMillis - startTime;
    } else {
        // Handle millis() rollover
        elapsedMillis = (ULONG_MAX - startTime) + currentMillis;
    }
}
    

  public:
  TimerCooker(unsigned long timeToCook) {
    timingCooking = timeToCook;
  }

  void startTimer() {
    startTime = millis();
    timerStarted = true;
  }

  void setTimer(unsigned long timeToCook) {
    this->timingCooking = timeToCook;
  }

  bool isTimeUp() {
    setElapsedTime();
    return (elapsedMillis >= timingCooking);
  }

  unsigned long getRemainingTimeMillis() {
    if (elapsedMillis >= timingCooking) {
        return 0;
    }
    return (timingCooking - elapsedMillis);
  }

  void resetTimer() {
    startTime = 0;
    elapsedMillis = 0;
    previousRemainingTime = "";
    elapsedMinutes = 0;
    }

  String getRemainingTime() {
      long remaningSeconds = (timingCooking - elapsedMillis) / 1000;
      int minutes = remaningSeconds / 60;
      int seconds = remaningSeconds % 60;

      String formattedTime = String(minutes) + ":";

      if (seconds < 10) {
        formattedTime += "0";  // adicionar um zero à esquerda para segundos menores que 10
      }
      
      formattedTime += String(seconds);
      return formattedTime;
    
  }

  void printRemainingTime() {
    String remainingTime = getRemainingTime();
    if (remainingTime != previousRemainingTime) {
      Serial.print("Faltam apenas: ");
      Serial.print(remainingTime);
      Serial.println(" minutos para terminar o cozimento");
      previousRemainingTime = remainingTime;
    }
  }


};

#include "control_state.h"

class PIDController {

    private:
      float Kp, Ki, Kd;
      float integral = 0;
      float maxIntegral = 1000.0;
      float minIntegral = -1000.0;
      float previousError;


    public:
       PIDController(float Kp, float Ki, float Kd) : Kp(Kp), Ki(Ki), Kd(Kd) {
        this->previousError = 0;
       }

       ControlState compute(float desiredTemperature, float currentTemperature) {
        float error = desiredTemperature - currentTemperature;
        integral += error;
        float derivative = error - previousError;

        float output = Kp * error + Ki * integral + Kd * derivative;

        previousError = error;

        if (output > 0) {
            return ON;
        } else {
            return OFF;
        }
       }

};
class WarmupController {

    private:
       CookingPot& cookingPot;
       float START_THRESHOLD;
       bool isWarmupCompleted = false;

    
    public:
      WarmupController(CookingPot& cookingPot, float startThreshold): cookingPot(cookingPot), START_THRESHOLD(startThreshold) {}
       

      void warmup(float temperature) {
        if (!isWarmupCompleted) {
          if (temperature >= START_THRESHOLD) {
            isWarmupCompleted = true;
          } 
          cookingPot.setRelayStatus(true);
       }
    }

      bool isWarmupDone() const {
         return isWarmupCompleted;
      }

      void setStartThreshold(float threshold) {
        START_THRESHOLD = threshold;
      }
};
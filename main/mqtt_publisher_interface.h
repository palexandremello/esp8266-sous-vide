
class MQTTPublisherInterface {
    public:
       virtual void publishMetrics(float temperature, unsigned long remainingTime, bool releStatus, bool isWarmupCompleted, bool isCookingStarted ) = 0;
};

class MQTTCommandListener {
    public:
        virtual void onSetTemperature (float temperature) = 0;
        virtual void onSetTimer (unsigned long duration) = 0;
        virtual void onStartCooking () = 0;
};
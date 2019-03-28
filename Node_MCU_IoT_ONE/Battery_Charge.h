#include "Arduino.h"

#define MIN_BATTERY_VOL 5
#define THRESHOLD 11
#define FACTOR 6.4
#define CHARGE_TIME 6*(3600000)
#define CHARGING_SINCE (millis() - start_charge_time)
#define BATTERY_PRESENT (check_voltage() > MIN_BATTERY_VOL)
#define BATTERY_DISCHARGED (check_voltage() < THRESHOLD)

class Battery{
    private:

        unsigned long start_charge_time;            // to record time when charging started
        int voltage_check_pin;                      // battery voltage check pin                                    
        int charge_enable_pin;                      // enable charge pin
        bool is_charging;                           // checking charging status

    public:
        Battery(int Tvoltage_check_pin,int Tcharge_enable_pin);
        void charge_check();
        float check_voltage();                      // returns voltage of battery on pin voltage_check_pin
        void start_charging();                      // starts charging battery and notes time
        void stop_charging();                       // stops charging battery
        bool ischarging();
        float charging_since();
};
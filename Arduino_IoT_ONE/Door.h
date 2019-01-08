#include"Arduino.h"
#ifndef Door_h
#define Door_h

class Door{
    int door_unlock_pin;
    int door_close_sensor_pin;
    int red_light_pin;
    int green_light_pin;
    bool is_locked;
    bool is_closed;
    void turn_red_light_on();
    void turn_green_light_on();
    void turn_red_light_off();
    void turn_green_light_off();
    void send_unlock_signal();
    
    public:
        Door(int Tdoor_unlock_pin, int Tdoor_lock_sensor_pin, int Tred_light_pin, int Tgreen_light_pin);
        void init();
        void polling_for_close_check();
        void unlock_door();
        void lock_door();
        void close_door();
        void blink_red_light();
        bool get_is_locked();
        bool get_is_closed();
};
#endif

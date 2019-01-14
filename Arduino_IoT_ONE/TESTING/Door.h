#include"Arduino.h"
#ifndef Door_h
#define Door_h

class Door{
    byte door_unlock_pin;
    byte door_close_sensor_pin;
    byte red_light_pin;
    int green_light_pin;
    bool is_locked;
    bool is_closed;
    void turn_red_light_on();
    void turn_green_light_on();
    void turn_red_light_off();
    void turn_green_light_off();
    void send_unlock_signal();
    
    public:
        Door(byte Tdoor_unlock_pin, byte Tdoor_lock_sensor_pin, byte Tred_light_pin, byte Tgreen_light_pin);
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

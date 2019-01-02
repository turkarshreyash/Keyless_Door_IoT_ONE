#include"Arduino.h"
#include"Door.h"

void Door::turn_red_light_on(){
    Serial.println("Red light turned on");
    digitalWrite(red_light_pin, HIGH);
}
void Door::turn_green_light_on(){
    Serial.println("Green light turned on");
    digitalWrite(green_light_pin,HIGH);
}
void Door::turn_red_light_off(){
        Serial.println("Red light turned off");
        digitalWrite(red_light_pin, LOW);
}
void Door::turn_green_light_off(){
    Serial.println("Green light turned off");
    digitalWrite(green_light_pin, LOW);
}

bool Door::get_is_closed(){
    return is_closed;
}
bool Door::get_is_locked(){
    return is_locked;
}

void Door::send_unlock_signal(){
    Serial.println("Door Unlocked");
    digitalWrite(door_unlock_pin, HIGH);
    delay(100);
    digitalWrite(door_unlock_pin, LOW);
}


Door::Door(int Tdoor_unlock_pin, int Tdoor_close_sensor_pin, int Tred_light_pin, int Tgreen_light_pin){
    door_unlock_pin = Tdoor_unlock_pin;
    door_close_sensor_pin = Tdoor_close_sensor_pin;
    red_light_pin = Tred_light_pin;
    green_light_pin = Tgreen_light_pin;
    is_closed = false;
    is_locked = false;
}
void Door::init(){
    Serial.println("Door init Called");
    polling_for_close_check();
    turn_green_light_on();
    turn_red_light_off();
    lock_door();
}
void Door::polling_for_close_check(){
    Serial.println("Polling.....");
    if(digitalRead(door_close_sensor_pin)){
        Serial.println("Door Closed");
        is_closed = true;
        return;
    }
    Serial.println("Door not closed");
    is_closed = false;
}  

void Door::lock_door(){
    Serial.println("Entered Lock Function");
    if(!is_closed){
        Serial.println("Door not Closed");
        return;
    }
    Serial.println("Door is Closed");
    is_locked = true;
    turn_green_light_off();
    turn_red_light_on();
}

void Door::unlock_door(){
    Serial.println("Entered unlock Function");
    if(!is_closed){
        Serial.println("Door is open!");
        return;
    }
    is_locked=false;
    send_unlock_signal();
    turn_red_light_off();
    turn_green_light_on();
}

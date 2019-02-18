#include"Arduino.h"
#include"Door.h"

void Door::turn_red_light_on(){

    digitalWrite(red_light_pin, HIGH);
}
void Door::turn_green_light_on(){
    digitalWrite(green_light_pin,HIGH);
}
void Door::turn_red_light_off(){
        digitalWrite(red_light_pin, LOW);
}
void Door::turn_green_light_off(){
    digitalWrite(green_light_pin, LOW);
}

void Door::blink_red_light(){
    digitalWrite(red_light_pin, LOW);
    delay(200);
    digitalWrite(red_light_pin, HIGH);
}

bool Door::get_is_closed(){
    return is_closed;
}
bool Door::get_is_locked(){
    return is_locked;
}

void Door::send_unlock_signal(){
 
    digitalWrite(door_unlock_pin, HIGH);
    delay(75);
    digitalWrite(door_unlock_pin, LOW);
}


Door::Door(byte Tdoor_unlock_pin, byte Tdoor_close_sensor_pin, byte Tred_light_pin, byte Tgreen_light_pin,byte Tpir_pin){
    door_unlock_pin = Tdoor_unlock_pin;
    door_close_sensor_pin = Tdoor_close_sensor_pin;
    red_light_pin = Tred_light_pin;
    green_light_pin = Tgreen_light_pin;
    pir_pin = Tpir_pin;
    digitalWrite(door_unlock_pin, LOW);
    is_closed = false;
    is_locked = false;
    use_pir = false;
    pir_last_state = false;
}
void Door::init(){
    polling_for_close_check();
    turn_green_light_on();
    turn_red_light_off();
    lock_door();
}
void Door::polling_for_close_check(){
    if(digitalRead(door_close_sensor_pin)){
        if(!is_closed){
            time_elapsed_since_closed = millis();
        }
        is_closed = true;
        return;
    }
    is_closed = false;
}  
void Door::pir_polling(){
    if (!use_pir)
    {
        if (millis() > 50000)
        {
            use_pir = true;
        }
        return;
    }
    bool pir_current_state = analogRead(pir_pin);;
    if(pir_current_state > 553){
        if(pir_last_state != pir_current_state){
            if(millis() - time_elapsed_since_closed > 15000){
                unlock_door();
            }
        }
    }
    pir_last_state = pir_current_state;
}

void Door::lock_door(){
    if(!is_closed){
        return;
    }
    is_locked = true;
    turn_green_light_off();
    turn_red_light_on();
}

void Door::unlock_door(){
    if(!is_closed){
        return;
    }
    is_locked=false;
    send_unlock_signal();
    turn_red_light_off();
    turn_green_light_on();
}
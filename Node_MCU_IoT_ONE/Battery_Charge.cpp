#include "Arduino.h"
#include "Battery_Charge.h"
                            
float Battery::check_voltage(){
    float Tvoltage = 0.0;
    float Vvalue = 0.0, Rvalue = 0.0;
    for (unsigned int i = 0; i < 10; i++){
        Vvalue = Vvalue + analogRead(voltage_check_pin); //Read analog Voltage
        delay(5);                          //ADC stable
    }
    Vvalue = (float)Vvalue / 10.0;           //Find average of 10 values
    Rvalue = (float)(Vvalue / 1024.0) * 3.3; //Convert Voltage in 5v factor
    Tvoltage = Rvalue * FACTOR;         //Find original voltage by multiplying with factor
    /////////////////////////////////////Battery Voltage//////////////////////////////////
    return Tvoltage;
}

void Battery::start_charging()
{
    digitalWrite(charge_enable_pin, HIGH);
    start_charge_time = millis();
    is_charging = true;
}

void Battery::stop_charging()
{
    digitalWrite(charge_enable_pin, LOW);
    start_charge_time = 0;
    is_charging = false;
}

Battery::Battery(int Tvoltage_check_pin, int Tcharge_enable_pin)
{
    voltage_check_pin = Tvoltage_check_pin;
    charge_enable_pin = Tcharge_enable_pin;
    stop_charging();
    is_charging = false;
    
}

void Battery::charge_check()
{   
    Serial.print(check_voltage());
        if (BATTERY_PRESENT)
        {
            if (!is_charging)
            {   
                if (BATTERY_DISCHARGED)
                {
                    start_charging();
                }
            }
            else
            {   
                if (CHARGE_TIME <= CHARGING_SINCE)
                { 
                    stop_charging();
                }
                
            }
        }else{
            stop_charging();
        }
}

bool Battery::ischarging(){
    return is_charging;
}

float Battery::charging_since(){
    return CHARGING_SINCE;
}
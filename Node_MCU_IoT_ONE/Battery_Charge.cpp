#include "Arduino.h"
#include "Battery_Charge.h"

const int  Battery::min_battery_vol = 5;                
const int Battery::threshold = 10;                      
const unsigned long Battery::charge_time = (5) * (3.6e6);
const float Battery::RatioFactor = 3.2;

float Battery::check_voltage(){
    float Tvoltage = 0.0;
    float Vvalue = 0.0, Rvalue = 0.0;
    for (unsigned int i = 0; i < 10; i++)
    {
        Vvalue = Vvalue + analogRead(voltage_check_pin); //Read analog Voltage
        delay(5);                          //ADC stable
    }
    Vvalue = (float)Vvalue / 10.0;           //Find average of 10 values
    Rvalue = (float)(Vvalue / 1024.0) * 3.3; //Convert Voltage in 5v factor
    Tvoltage = Rvalue * RatioFactor;         //Find original voltage by multiplying with factor
    /////////////////////////////////////Battery Voltage//////////////////////////////////
    return Tvoltage;
}

bool Battery::power_supply(){
    if(digitalRead(power_supply_check_pin)){
        return true;
    }
    return false;
}

bool Battery::battery_present()
{
    if (check_voltage() > min_battery_vol)
    {
        return true;
    }
    return false;
}

bool Battery::battery_discharged()
{
    if (check_voltage() < threshold)
    {
        return true;
    }
    return false;
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


Battery::Battery(int Tvoltage_check_pin, int Tcharge_enable_pin, int Tpower_supply_check_pin)
{
    voltage_check_pin = Tvoltage_check_pin;
    charge_enable_pin = Tcharge_enable_pin;
    power_supply_check_pin = Tpower_supply_check_pin;
    is_charging = false;
}

void Battery::charge_check()
{   
    Serial.println("Inside Function charge_check");
    Serial.print("Voltage : ");
    Serial.print(check_voltage());
    if (power_supply())
    {
        Serial.println("Getting Power Supply");
        if (battery_present())
        {
            Serial.println("Battery is Present");
            if (!is_charging)
            {   
                Serial.println("Battery is Not Charging");
                if (battery_discharged())
                {
                    Serial.println("Battery is discharged");
                    start_charging();
                }
            }
            else
            {   
                Serial.println("BAttery is charging");
                Serial.println("Time Elapsed : ");
                Serial.println((millis() - start_charge_time));
                if (charge_time <= (millis()-start_charge_time))
                { 
                    Serial.println("Battery charge time is over Now Stopping Charging");
                    stop_charging();
                }
                
            }
        }else{
            stop_charging();
        }
    }
    else
    {
        Serial.println("No main Power");
        if (is_charging)
        {
            Serial.println("Battery Charging Paused ");
            stop_charging();
        }
    }
}

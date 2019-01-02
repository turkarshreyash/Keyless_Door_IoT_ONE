#include "Arduino.h"
#include "Battery_Charge.h"
const int  Battery::min_battery_vol = 3;                
const int Battery::threshold = 10;                      
const unsigned long Battery::charge_time = (5) * (3.6e6);
const float Battery::R1 = 1000000;                      
const float Battery::R2 = 46000;                        
float Battery::check_voltage(){
    float value = analogRead(voltage_check_pin);
    return ((value * 5.0) / 1024.0) / (R2 / (R1 + R2));
}
bool Battery::power_supply(){
    if(analogRead(power_supply_check_pin)>=700){
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
        ;
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
void Battery::pause_charging()
{
    digitalWrite(charge_enable_pin, LOW);
    paused_since = millis();
    charging_is_paused = true;
    is_charging = false;
}
void Battery::resume_charge()
{
    digitalWrite(charge_enable_pin, HIGH);
    unsigned long current_time = millis();
  //  Serial.println("Resumed Charging !");
    if ((current_time - paused_since) < (paused_since - start_charge_time))
    {
        start_charge_time = start_charge_time + (current_time - paused_since);
    //    Serial.print("Minor Fault : ");
      //  Serial.print(start_charge_time);
        
    }
    else
    {
        start_charge_time = current_time;
       // Serial.println("Major Fault : ");
        //Serial.println(start_charge_time);
    }
    Serial.println();
    charging_is_paused = false;
    is_charging = true;
}
Battery::Battery(int Tvoltage_check_pin, int Tcharge_enable_pin, int Tpower_supply_check_pin)
{
    voltage_check_pin = Tvoltage_check_pin;
    charge_enable_pin = Tcharge_enable_pin;
    power_supply_check_pin = Tpower_supply_check_pin;
    is_charging = false;
    charging_is_paused = false;
}
void Battery::charge_check()
{   
    //Serial.println("Inside Function charge_check");
    if (power_supply())
    {
      //  Serial.println("Getting Power Supply");
        if (battery_present())
        {
        //    Serial.println("Battery is Present");
            if (charging_is_paused)
            {
          //      Serial.println("Battery Charging is Paused");
                resume_charge();
            }
            if (!is_charging)
            {   
            //    Serial.println("Battery is Not Charging");
                if (battery_discharged())
                {
              //      Serial.println("Battery is discharged");
                    start_charging();
                }
            }
            else
            {   
                //Serial.println("BAttery is charging");
                //Serial.println("Time Elapsed : ");
                Serial.println((millis() - start_charge_time));
                if (charge_time <= (millis()-start_charge_time))
                { 
                 //   Serial.println("Battery charge time is over Now Stopping Charging");
                    stop_charging();
                }
                
            }
        }else{
            stop_charging();
        }
    }
    else
    {
        //Serial.println("No main Power");
        if (is_charging)
        {
          //  Serial.println("Battery Charging Paused ");
            pause_charging();
        }
    }
}

#include"Door.h"
#include"Pin_Pad.h"
#include "Battery_Charge.h"
#include<Keypad.h>
#define door_unlock_pin A4
#define door_close_sensor_pin A3
#define red_light_pin A0
#define green_light_pin A1
#define button_pin 2
#define node_mcu_lock 12
#define node_mcu_open 3
#define battery_vol_ch A5
#define battery_charge_en 13
#define power_supply_ch A2


int buttonState;           // the current reading from the input pin
int lastButtonState = HIGH; // the previous reading from the input pin
int reading;

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 10;   // the debounce time; 

String pin = "0000";

const byte n_rows = 4;              //four rows
const byte n_cols = 4;              //four columns
byte rowPins[n_rows] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[n_cols] = {7, 6, 5, 4};   //connect to the column pinouts of the keypad
char keys[n_rows][n_cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
Keypad mykeypad = Keypad(makeKeymap(keys), rowPins, colPins, n_rows, n_cols);



Door door(door_unlock_pin,door_close_sensor_pin,red_light_pin,green_light_pin);
Pin_Pad pin_pad(pin);
Battery battery(battery_vol_ch, battery_charge_en, power_supply_ch);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(door_unlock_pin,OUTPUT);
  pinMode(door_close_sensor_pin,INPUT);
  pinMode(red_light_pin,OUTPUT);
  pinMode(green_light_pin,OUTPUT);
  pinMode(button_pin, INPUT); //switch
  pinMode(node_mcu_lock,INPUT);
  pinMode(node_mcu_open,INPUT);
  door.init();

}

void loop() {


  reading = digitalRead(button_pin);
  if (reading != lastButtonState)
  {
    //Serial.println("Reset Debounce time");
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW)
      {
        //Serial.println("Entered!");
        if (door.get_is_locked())
        {
          door.unlock_door();
        }
        else if (door.get_is_closed())
        {
          door.lock_door();
        }
      }
    }
  }
  lastButtonState = reading;

  if (digitalRead(node_mcu_lock))
  {
    //Serial.println("LOCK REQUEST RECEIVED");
    if (door.get_is_closed() && !door.get_is_locked())
    {
      door.lock_door();
    }
    delay(500);
    }
    if(digitalRead(node_mcu_open)){
      //Serial.println("OPEN REQUEST RECEIVED ");
      if(door.get_is_closed()){
        door.unlock_door();
      }
      delay(500);
    }
  if(!door.get_is_locked()){
    door.polling_for_close_check();
  }
  if(door.get_is_closed()||door.get_is_locked()){
    pin_pad.check_action(door, mykeypad);
  }

  battery.charge_check();
}

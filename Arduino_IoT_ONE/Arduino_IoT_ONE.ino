#include"Door.h"
#include"Pin_Pad.h"
#include<Keypad.h>

byte door_unlock_pin = A4;
byte door_close_sensor_pin = A2;
byte red_light_pin = A0;
byte green_light_pin = A1;
byte button_pin = 2;
byte node_mcu_lock = 12;
byte node_mcu_open = 3;
byte indi_light = A3;
byte pir = A5;
byte reading;

byte buttonState;           // the current reading from the input pin
byte lastButtonState = HIGH; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled


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



Door door(door_unlock_pin,door_close_sensor_pin,red_light_pin,green_light_pin,pir);
Pin_Pad pin_pad(pin);


void setup() {


  pinMode(door_unlock_pin,OUTPUT);
  pinMode(door_close_sensor_pin,INPUT);
  pinMode(red_light_pin,OUTPUT);
  pinMode(green_light_pin,OUTPUT);
  pinMode(button_pin, INPUT);  //switch
  pinMode(node_mcu_lock,INPUT);
  pinMode(node_mcu_open,INPUT);
  pinMode(indi_light,OUTPUT);
  pinMode(pir,INPUT);
  door.init();

}

void loop() {
  digitalWrite(indi_light,HIGH);

  reading = digitalRead(button_pin);

    if (reading != buttonState)
    {
      buttonState = reading;


      if (buttonState == LOW)
      {
      
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

  lastButtonState = reading;



  if (digitalRead(node_mcu_lock))
  {
    
    if (door.get_is_closed() && !door.get_is_locked())
    {
      door.lock_door();
    }
    delay(500);
    }
    if(digitalRead(node_mcu_open)){
      
      if(door.get_is_closed()){
        door.unlock_door();
      }
      delay(500);
    }

  if(door.get_is_closed() && !door.get_is_locked()){
    door.pir_polling();
  }
  

  if(!door.get_is_locked()){
    door.polling_for_close_check();
  }
  if(door.get_is_closed()||door.get_is_locked()){
    pin_pad.check_action(door, mykeypad);
  }
  



  delay(50);
  digitalWrite(indi_light,LOW);
  delay(50);
}

#include"Arduino.h"
#include"Pin_Pad.h"

Pin_Pad::Pin_Pad(String Tpin)
{
    pin = Tpin;
}

bool Pin_Pad::pin_checked(Keypad &myKeypad, Door &door)
{
    door.blink_red_light();
    String entered_pin = "";
    int len = pin.length();
    Serial.print("Lenght of pin : ");
    Serial.print(len);
    for (int i = 0; i < len;)
    {   
        char pressed_key = myKeypad.getKey();
        if (pressed_key)
        {
            if (pressed_key == 'B')
            {
                Serial.println("exit without Opening door !");
                return false;
            }
            else if (pressed_key == 'C')
            {
                Serial.println("Clear entered pin");
                entered_pin = "";
                i = 0;
            }
            else if (pressed_key != 'A')
            {
                Serial.println(pressed_key);
                i++;
                entered_pin = entered_pin + pressed_key;
            }
            Serial.println(entered_pin);
        }
        
    }
    return entered_pin == pin;
}

void Pin_Pad::check_action(Door &door, Keypad &myKeypad)
{
    char pressed_key = myKeypad.getKey();
    if(pressed_key){
        Serial.println("Something is entered");
        if (pressed_key == 'A')
        {
            Serial.println("Entered Key : A");
            if (door.get_is_locked())
            {
                Serial.println("Door is locked Enter pin: ");
                if (pin_checked(myKeypad,door))
                {
                    door.unlock_door();
                }
            }
            else if (!door.get_is_locked() && door.get_is_closed())
            {
                Serial.println("Opening Door ....");
                door.unlock_door();
            }
        }
        else if (pressed_key == 'D')
        {
            Serial.println("Entered Key : D");
            door.lock_door();
        }
    }
    
}

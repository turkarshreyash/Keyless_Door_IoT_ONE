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
    char pressed_key;
    for (int i = 0; i < 4;)
    {   
        pressed_key = myKeypad.getKey();
        if (pressed_key)
        {
            if (pressed_key == 'B')
            {
                return false;
            }
            else if (pressed_key == 'C')
            {
                entered_pin = "";
                i = 0;
            }
            else if (pressed_key != 'A')
            {
                i++;
                entered_pin = entered_pin + pressed_key;
            }
        }
        
    }
    return entered_pin == pin;
}

void Pin_Pad::check_action(Door &door, Keypad &myKeypad)
{
    char pressed_key = myKeypad.getKey();
    if(pressed_key){
     
        if (pressed_key == 'A')
        {
        
            if (door.get_is_locked())
            {

                if (pin_checked(myKeypad,door))
                {
                    door.unlock_door();
                }
            }
            else if (!door.get_is_locked() && door.get_is_closed())
            {
               
                door.unlock_door();
            }
        }
        else if (pressed_key == 'D')
        {

            door.lock_door();
        }
    }
    
}

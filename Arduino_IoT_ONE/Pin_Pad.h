#include"Arduino.h"
#include"Door.h"
#include <Keypad.h>

#ifndef Pin_Pad_h
#define Pin_Pad_h

class Pin_Pad
{
    String pin;
    bool pin_checked(Keypad &myKeypad);

  public:
    Pin_Pad(String Tpin);
    void check_action(Door &door, Keypad &myKeypad);
};

#endif

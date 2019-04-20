/*
Innovation Eternity
*/

#include"Arduino.h"
#include"Door.h"
#include <Keypad.h>

#ifndef Pin_Pad_h
#define Pin_Pad_h

class Pin_Pad
{
    String pin;
    Door *door;
    Keypad *myKeypad;
    bool pin_checked();

  public:
    Pin_Pad(String,Keypad*,Door*);
    void check_action();
};

#endif

/*
Design by Innovation Eternity
Implementation by S Inc. (C) 2019
*/
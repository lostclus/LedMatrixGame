#ifndef Keyboard_h
#define Keyboard_h

#include <Arduino.h>

class Keyboard {
  private:
    byte rowCount,
         colCount,
         *rowPins,
         *colPins;
    word keysV[10];
    unsigned long keysTime;
  public:
    word downKeys,
         pressKeys;
    Keyboard(byte rowCount, byte colCount, byte *rowPins, byte *colPins);
    word read(unsigned long now);
    bool isKeyDown(word key);
    bool isKeyPress(word key);
};

#endif	//Keyboard.h
// vim:et:sw=2:ai

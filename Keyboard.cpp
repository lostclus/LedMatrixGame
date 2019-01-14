#include "Keyboard.h"

Keyboard::Keyboard(byte rowCount, byte colCount, byte *rowPins, byte *colPins) {
  int i;

  this->rowCount = rowCount;
  this->colCount = colCount;
  this->rowPins = rowPins;
  this->colPins = colPins;
  keysTime = 0;
  for (i = 0; i < sizeof(keysV) / sizeof(keysV[0]); i++)
    keysV[i] = 0;
}

word Keyboard::read(unsigned long now) {
  word curKeys,
       prevUpKeys;
  int i;

  for (int ci=0; ci<colCount; ci++) {
    byte cp = colPins[ci];
    pinMode(cp, OUTPUT);
    digitalWrite(cp, LOW);

    for (int ri=0; ri<rowCount; ri++) {
      byte rp = rowPins[ri];
      pinMode(rp, INPUT_PULLUP);
      bitWrite(downKeys, ri * colCount + ci,
               int(!bool(digitalRead(rp))));
      pinMode(rp, INPUT);
    }

    pinMode(cp, INPUT);
  }

  pressKeys = 0;

  if (now > keysTime) {
    curKeys = prevUpKeys = ~((word)0);
    for (i = 0; i < sizeof(keysV) / sizeof(keysV[0]); i++) {
      if (i < sizeof(keysV) / sizeof(keysV[0]) / 2) {
        curKeys &= keysV[i];
      } else {
        prevUpKeys &= ~keysV[i];
      }
    }
    pressKeys = prevUpKeys & curKeys;

    for (i = sizeof(keysV) / sizeof(keysV[0]) - 1; i > 0; i--)
      keysV[i] = keysV[i-1];

    keysV[0] = ~((word)0);
    keysTime = now;
  }
  keysV[0] &= downKeys;

  return downKeys;
}

bool Keyboard::isKeyDown(word key) {
  return (downKeys & key) != 0;
}

bool Keyboard::isKeyPress(word key) {
  return (pressKeys & key) != 0;
}

// vim:et:sw=2:ai

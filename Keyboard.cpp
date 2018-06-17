#include "Keyboard.h"

Keyboard::Keyboard(byte rowCount, byte colCount, byte *rowPins, byte *colPins) {
  this->rowCount = rowCount;
  this->colCount = colCount;
  this->rowPins = rowPins;
  this->colPins = colPins;
}

word Keyboard::read() {
  word prevKeys = downKeys;

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
      delay(1);
    }

    pinMode(cp, INPUT);
  }

  pressKeys = ((~prevKeys) & downKeys);
  return downKeys;
}

bool Keyboard::isKeyDown(word key) {
  return (downKeys & key) != 0;
}

bool Keyboard::isKeyPress(word key) {
  return (pressKeys & key) != 0;
}

// vim:et:sw=2:ai

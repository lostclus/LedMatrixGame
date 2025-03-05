#include "BaseGame.h"

BaseGame::BaseGame(Keyboard *kbd, Display *disp, int buzzerPin) {
  this->kbd = kbd;
  this->disp = disp;
  this->buzzerPin = buzzerPin;
}

void BaseGame::reset() {
}

// vim:et:sw=2:ai

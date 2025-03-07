#include "BaseGame.h"

BaseGame::BaseGame(Keyboard *kbd, Display *disp, Speaker *spk) {
  this->kbd = kbd;
  this->disp = disp;
  this->spk = spk;
}

void BaseGame::reset() {
}

// vim:et:sw=2:ai

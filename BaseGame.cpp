#include "BaseGame.h"

BaseGame::BaseGame(Keyboard *kbd, MultiLedControl *lc) {
  this->kbd = kbd;
  this->lc = lc;
}

bool BaseGame::handleStart() {
  return false;
}

bool BaseGame::handleSelect() {
  return false;
}

// vim:et:sw=2:ai

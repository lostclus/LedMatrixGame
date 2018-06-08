#include "PointControlGame.h"

PointControlGame::PointControlGame(Keyboard *kbd, MultiLedControl *lc)
  : BaseGame(kbd, lc) {
  pointX = lc->getColumnsCount() / 2;
  pointY = lc->getRowsCount() / 2;
  lc->clearDisplay();
  lc->setLed(pointY, pointX, true);
}

void PointControlGame::loop() {
  int moveX = 0,
      moveY = 0;

  if (moveX != 0 || moveY != 0) {
    lc->setLed(pointY, pointX, false);
    pointX = max(0, min(lc->getColumnsCount() - 1, pointX + moveX));
    pointY = max(0, min(lc->getRowsCount() - 1, pointY + moveY));
    lc->setLed(pointY, pointX, true);
  }
}

// vim:et:sw=2:ai

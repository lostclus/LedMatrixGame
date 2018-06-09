#include "PointControlGame.h"
#include "KeyDef.h"

PointControlGame::PointControlGame(Keyboard *kbd, MultiLedControl *lc)
  : BaseGame(kbd, lc) {
  pointX = lc->getColumnsCount() / 2;
  pointY = lc->getRowsCount() / 2;
  lc->clearDisplay();
  lc->setLed(pointY, pointX, true);
  nextTarget();
}

void PointControlGame::nextTarget() {
  do {
    targetX = random(lc->getColumnsCount());
    targetY = random(lc->getRowsCount());
  }
  while (targetX == pointX && targetY == pointY);
}

void PointControlGame::loop() {
  int moveX = 0,
      moveY = 0;
  unsigned long now = millis();

  if (kbd->isKeyPress(KEY_UP)) moveY = -1;
  else if (kbd->isKeyPress(KEY_DOWN)) moveY = 1;
  if (kbd->isKeyPress(KEY_LEFT)) moveX = -1;
  else if (kbd->isKeyPress(KEY_RIGHT)) moveX = 1;

  if (moveX != 0 || moveY != 0) {
    lc->setLed(pointY, pointX, false);
    pointX = max(0, min(lc->getColumnsCount() - 1, pointX + moveX));
    pointY = max(0, min(lc->getRowsCount() - 1, pointY + moveY));
    lc->setLed(pointY, pointX, true);

    if (pointX == targetX && pointY == targetY) {
      tone(3, 1000, 200);
      nextTarget();
    }
  }

  lc->setLed(targetY, targetX, now % 500 < 250);
}

// vim:et:sw=2:ai

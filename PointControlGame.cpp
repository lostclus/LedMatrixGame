#include "PointControlGame.h"
#include "KeyDef.h"

PointControlGame::PointControlGame(Keyboard *kbd, Display *disp, Speaker *spk)
  : BaseGame(kbd, disp, spk) {
  pointX = disp->matrix.width() / 2;
  pointY = disp->matrix.height() / 2;
  disp->matrix.clear();
  disp->matrix.dot(pointX, pointY, 1);
  disp->matrix.update();
  nextTarget();
}

void PointControlGame::nextTarget() {
  do {
    targetX = random(disp->matrix.width());
    targetY = random(disp->matrix.height());
  }
  while (targetX == pointX && targetY == pointY);
}

void PointControlGame::handle() {
  int moveX = 0,
      moveY = 0;
  unsigned long now = millis();

  if (kbd->isKeyPress(KEY_UP)) moveY = -1;
  else if (kbd->isKeyPress(KEY_DOWN)) moveY = 1;
  if (kbd->isKeyPress(KEY_LEFT)) moveX = -1;
  else if (kbd->isKeyPress(KEY_RIGHT)) moveX = 1;

  if (moveX != 0 || moveY != 0) {
    disp->matrix.dot(pointX, pointY, 0);
    pointX = max(0, min(disp->matrix.width() - 1, pointX + moveX));
    pointY = max(0, min(disp->matrix.height() - 1, pointY + moveY));
    disp->matrix.dot(pointX, pointY, 1);

    if (pointX == targetX && pointY == targetY) {
      spk->sound1();
      nextTarget();
    }
  }

  disp->matrix.dot(targetX, targetY, now % 500 < 250);
  disp->matrix.update();
}

// vim:et:sw=2:ai

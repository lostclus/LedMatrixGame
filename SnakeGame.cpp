#include "SnakeGame.h"
#include "KeyDef.h"
#include "Speaker.h"

SnakeGame::SnakeGame(Keyboard *kbd, MultiLedControl *lc)
  : BaseGame(kbd, lc) {
  int half;

  snake = new byte[lc->getColumnsCount() *
                   lc->getRowsCount()];
  isGgameOver = false;
  prevAdvance = 0;
  blinkCount = 3;

  half = lc->getColumnsCount() / 2;
  length = lc->getColumnsCount() / 3;

  for (int i=0; i<length; i++)
    snake[i] = ((half + i) << 4) + half - 1;

  foodX = half + 1;
  foodY = half - 1;
  vecX = 0;
  vecY = -1;

  lc->clearDisplay();
  render();
}

SnakeGame::~SnakeGame() {
  delete[] snake;
}

void SnakeGame::render() {
  for (int i=0; i<length; i++)
    lc->setLed(snake[i] >> 4, snake[i] & 0x0f, true);
  lc->setLed(foodY, foodX, true);
}

void SnakeGame::advance() {
  int hx = (snake[0] & 0x0f) + vecX,
      hy = (snake[0] >> 4) + vecY;

  if (hx < 0 || hx >= lc->getColumnsCount() ||
      hy < 0 || hy >= lc->getRowsCount()) {
    // showGameOverMessage();
    isGgameOver = true;
  }

  for (int i=0; i<length; i++) {
    if ((snake[i] & 0x0f) == hx &&
        (snake[i] >> 4) == hy) {
      // showGameOverMessage();
      isGgameOver = true;
    }
  }

  bool grow = (hx == foodX && hy == foodY);
  if (grow) {
    bool inSnake;
    tone(SPEAKER_PIN, 440);

    length++;
    randomSeed(millis());
    do {
      foodX = random(lc->getColumnsCount());
      foodY = random(lc->getRowsCount());
      inSnake = false;
      for (int i=0; i<length; i++) {
        if ((snake[i] & 0x0f) == foodX &&
            (snake[i] >> 4) == foodY) {
          inSnake = true;
          break;
        }
      }
    } while (inSnake);

    for (int i=0; i<10; i++) {
      tone(SPEAKER_PIN, 440 + i * 44);
      delay(20);
    }
    noTone(SPEAKER_PIN);
  }

  for (int i=length-1; i>=0; i--) {
      snake[i + 1] = snake[i];
  }
  snake[0] = (hy << 4) + hx;
}

void SnakeGame::readControls() {
  int dx = 0,
      dy = 0;

  if (kbd->isKeyDown(KEY_UP)) dy = -1;
  else if (kbd->isKeyDown(KEY_DOWN)) dy = 1;
  if (kbd->isKeyDown(KEY_LEFT)) dx = -1;
  else if (kbd->isKeyDown(KEY_RIGHT)) dx = 1;

  if (dy != 0 && vecX != 0) {
    vecX = 0;
    vecY = dy;    
  }
  if (dx != 0 && vecY != 0) {
    vecX = dx;
    vecY = 0;
  }
}

void SnakeGame::loop() {
  unsigned long now = millis();

  readControls();

  if (!isGgameOver) {
    if (now - prevAdvance > 250) {
      lc->setLed(snake[length-1] >> 4, snake[length-1] & 0x0f, false);
      advance();
      prevAdvance = now;
      render();
    }
  } else {
    while (blinkCount > 0) {
      lc->clearDisplay();
      delay(300);
      render();
      delay(300);
      blinkCount--;     
    }
  }
}

// vim:et:sw=2:ai

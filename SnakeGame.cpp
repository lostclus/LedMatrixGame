#include <NonBlockingRtttl.h>

#include "SnakeGame.h"
#include "KeyDef.h"
#include "Speaker.h"

SnakeGame::SnakeGame(Keyboard *kbd, MultiLedControl *lc)
  : BaseGame(kbd, lc) {
  snake = new byte[lc->getColumnsCount() *
                   lc->getRowsCount()];
  newGame();
}

SnakeGame::~SnakeGame() {
  delete[] snake;
}

void SnakeGame::newGame() {
  int half;

  isGameOver = false;
  prevAdvance = 0;

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
    isGameOver = true;
  }

  for (int i=0; i<length; i++) {
    if ((snake[i] & 0x0f) == hx &&
        (snake[i] >> 4) == hy) {
      // showGameOverMessage();
      isGameOver = true;
    }
  }

  bool grow = (hx == foodX && hy == foodY);
  if (grow) {
    bool inSnake;

    rtttl::begin(SPEAKER_PIN, ":d=16,o=5,b=600:a,b,c,d,e,f,g");

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
  }

  for (int i=length-1; i>0; i--) {
      snake[i] = snake[i-1];
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

  if (!isGameOver) {
    if (now - prevAdvance > 250) {
      lc->setLed(snake[length-1] >> 4, snake[length-1] & 0x0f, false);
      advance();
      prevAdvance = now;
      render();
    }
  } else {
    if ((now / 300) % 2 == 0) {
      lc->clearDisplay();
    } else {
      render();
    }
  }

  rtttl::play();
}

bool SnakeGame::handleStart() {
  if (isGameOver) {
    newGame();
    return true;
  }
  return false;
}

// vim:et:sw=2:ai

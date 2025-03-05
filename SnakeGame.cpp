#include <NonBlockingRtttl.h>

#include "SnakeGame.h"
#include "KeyDef.h"

SnakeGame::SnakeGame(Keyboard *kbd, Display *disp, int buzzerPin)
  : BaseGame(kbd, disp, buzzerPin) {
  width = disp->matrix.width();
  height = disp->matrix.height();
  snake = new byte[width * height];
  reset();
}

SnakeGame::~SnakeGame() {
  delete[] snake;
}

void SnakeGame::reset() {
  int half;

  isGameOver = false;
  prevAdvance = 0;

  half = width / 2;
  length = width / 3;

  for (int i=0; i<length; i++)
    snake[i] = ((half + i) << 4) + half - 1;

  foodX = half + 1;
  foodY = half - 1;
  vecX = 0;
  vecY = -1;

  disp->matrix.clearDisplay();
  render();
}

void SnakeGame::render() {
  for (int i=0; i<length; i++)
    disp->matrix.dot(snake[i] & 0x0f, snake[i] >> 4, 1);
  disp->matrix.dot(foodX, foodY, 1);
  disp->matrix.update();
}

void SnakeGame::advance() {
  int hx = (snake[0] & 0x0f) + vecX,
      hy = (snake[0] >> 4) + vecY;

  if (hx < 0 || hx >= width || hy < 0 || hy >= height) {
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

    rtttl::begin(buzzerPin, ":d=16,o=5,b=600:a,b,c,d,e,f,g");

    length++;
    randomSeed(millis());
    do {
      foodX = random(width);
      foodY = random(height);
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

void SnakeGame::handle() {
  unsigned long now = millis();

  readControls();

  if (!isGameOver) {
    if (now - prevAdvance > 250) {
      disp->matrix.dot(snake[length-1] & 0x0f, snake[length-1] >> 4, 0);
      advance();
      prevAdvance = now;
      render();
    }
  } else {
    if ((now / 300) % 2 == 0) {
      disp->matrix.clear();
      disp->matrix.clearDisplay();
    } else {
      render();
    }
  }

  rtttl::play();
}

// vim:et:sw=2:ai

#include "Arkanoid.h"
#include "KeyDef.h"

ArkanoidGame::ArkanoidGame(Keyboard *kbd, Display *disp, Speaker *spk)
  : BaseGame(kbd, disp, spk) {
  width = disp->matrix.width();
  height = disp->matrix.height();
  reset();
}

void ArkanoidGame::reset() {
  isGameOver = false;
  ballX = width / 4;
  ballY = height / 2;
  ballDX = BALL_SPEED;
  ballDY = BALL_SPEED;
  paddleX = (width - PADDLE_WIDTH) / 2;
  paddleY = height - 1;
  memset(bricks, true, sizeof(bricks));
}

void ArkanoidGame::handle() {
  unsigned long now = millis();
  static unsigned long prevUpdate = 0;

  if (isGameOver) {
    disp->run.tick();
    return;
  }

  if (kbd->isKeyPress(KEY_LEFT) && paddleX > 0) {
    paddleX--;
  } else if (kbd->isKeyPress(KEY_RIGHT) && paddleX < width - PADDLE_WIDTH) {
    paddleX++;
  } else if (kbd->isKeyPress(KEY_UP) && paddleY > BRICK_ROWS) {
    paddleY--;
  } else if (kbd->isKeyPress(KEY_DOWN) && paddleY < height - 1) {
    paddleY++;
  }
  
  if (now - prevUpdate > 150) {
    prevUpdate = now;

    ballX += ballDX;
    ballY += ballDY;
    
    if (ballX <= 0) {
      ballDX = abs(ballDX);
      spk->sound2();
    } else if (ballX >= width - 1) {
      ballDX = -abs(ballDX);
      spk->sound2();
    }

    if (ballY <= 0) {
      ballDY = abs(ballDY);
      spk->sound2();
    }
    
    if (ballY >= paddleY) {
      if (ballX >= paddleX && ballX < paddleX + PADDLE_WIDTH) {
	ballDY = -abs(ballDY);
        spk->sound2();
      } else {
	isGameOver = true;
        disp->runGameOver();
      }
    }
    
    if (ballY < BRICK_ROWS) {
      int bx = ballX, by = ballY;
      bool hit = false;

      if (bricks[by][bx]) {
	hit = true;
      } else if ((bx = ballX - 1) >= 0 && bricks[by][bx]) {
	hit = true;
      } else if ((bx = ballX + 1) < height && bricks[by][bx]) {
	hit = true;
      }
      if (hit) {
	  bricks[by][bx] = false;
	  ballDY = -ballDY;
          spk->sound2();
      }
    }

    if (ballDY < 0 && ballY == 0) {
      ballDY = abs(ballDY);
    }
    
    draw();
  }
}

void ArkanoidGame::draw() {
  disp->matrix.clear();
  
  for (int i = 0; i < BRICK_ROWS; i++) {
    for (int j = 0; j < BRICK_COLS; j++) {
      if (bricks[i][j]) {
	disp->matrix.dot(j, i, 1);
      }
    }
  }
  
  for (int i = 0; i < PADDLE_WIDTH; i++) {
    disp->matrix.dot(paddleX + i, paddleY, 1);
  }
  
  disp->matrix.dot(ballX, ballY, 1);
  disp->matrix.update();
}

// vim:ai:et:sw=2

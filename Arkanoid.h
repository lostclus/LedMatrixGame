#ifndef Arkanoid_h
#define Arkanoid_h

#include "BaseGame.h"

class ArkanoidGame : public BaseGame {
  private:
    int ballX, ballY, ballDX, ballDY;
    int paddleX, paddleY;
    static const int PADDLE_WIDTH = 4;
    static const int BALL_SPEED = 1;
    static const int BRICK_ROWS = 3;
    static const int BRICK_COLS = 16;
    bool bricks[BRICK_ROWS][BRICK_COLS];
    
    int width;
    int height;
  
  public:
    ArkanoidGame(Keyboard *kbd, Display *disp, Speaker *spk);
    virtual void reset();
    virtual void handle();
    void draw();
};

#endif
// vim:ai:et:sw=2

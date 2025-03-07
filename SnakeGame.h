#ifndef SnakeGame_h
#define SnakeGame_h

#include <Arduino.h>
#include "BaseGame.h"

class SnakeGame : public BaseGame {
  private:
    byte *snake,
         length;
    int width, height,
        foodX, foodY,
        vecX, vecY;
    long prevAdvance;

    void render();
    void advance();
    void readControls();
 
  public:
    SnakeGame(Keyboard *kbd, Display *disp, Speaker *spk);
    ~SnakeGame();
    virtual void reset();
    virtual void handle();
};

#endif	//SnakeGame.h
// vim:et:sw=2:ai

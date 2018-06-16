#ifndef SnakeGame_h
#define SnakeGame_h

#include <Arduino.h>
#include "BaseGame.h"

class SnakeGame : public BaseGame {
  private:
    byte *snake,
         length;
    int foodX, foodY,
        vecX, vecY;
    bool isGgameOver;
    long prevAdvance;
    int blinkCount;

    void render();
    void advance();
    void SnakeGame::readControls();
 
  public:
    SnakeGame(Keyboard *kbd, MultiLedControl *lc);
    ~SnakeGame();
    virtual void loop();
};

#endif	//SnakeGame.h
// vim:et:sw=2:ai

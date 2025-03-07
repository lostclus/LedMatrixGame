#ifndef PointControlGame_h
#define PointControlGame_h

#include <Arduino.h>
#include "BaseGame.h"

class PointControlGame : public BaseGame {
  private:
    byte pointX, pointY,
         targetX, targetY;
  public:
    PointControlGame(Keyboard *kbd, Display *disp, Speaker *spk);
    void nextTarget();
    virtual void handle();
};

#endif	//PointControlGame.h
// vim:et:sw=2:ai

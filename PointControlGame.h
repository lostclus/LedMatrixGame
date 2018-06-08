#ifndef PointControlGame_h
#define PointControlGame_h

#include <Arduino.h>
#include "BaseGame.h"

class PointControlGame : public BaseGame {
  private:
    byte pointX, pointY;
  public:
    PointControlGame(Keyboard *kbd, MultiLedControl *lc);
    virtual void loop();
};

#endif	//PointControlGame.h
// vim:et:sw=2:ai

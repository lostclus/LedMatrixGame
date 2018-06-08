#ifndef BaseGame_h
#define BaseGame_h

#include "Keyboard.h"
#include "MultiLedControl.h"

class BaseGame {
  protected:
    Keyboard *kbd;
    MultiLedControl *lc;
  public:
    BaseGame(Keyboard *kbd, MultiLedControl *lc);
    virtual void loop() = 0;
};

#endif	//BaseGame.h
// vim:et:sw=2:ai

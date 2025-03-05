#ifndef BaseGame_h
#define BaseGame_h

#include "Keyboard.h"
#include "Display.h"

class BaseGame {
  protected:
    Keyboard *kbd;
    Display *disp;
    int buzzerPin;
  public:
    bool isGameOver = false;
    BaseGame(Keyboard *kbd, Display *disp, int buzzerPin);
    virtual void reset();
    virtual void handle() = 0;
};

#endif	//BaseGame.h
// vim:et:sw=2:ai

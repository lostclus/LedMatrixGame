#ifndef MatrixTest_h
#define MatrixTest_h

#include <Arduino.h>
#include "BaseGame.h"

class MatrixTest : public BaseGame {
  private:
    unsigned long delaytime=50;
    void writeArduinoOnMatrix();
    void rows();
    void columns();
    void single();
  public:
    MatrixTest(Keyboard *kbd, MultiLedControl *lc);
    virtual void loop();
};

#endif	//MatrixTest.h
// vim:et:sw=2:ai

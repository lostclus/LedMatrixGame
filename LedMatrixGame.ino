#include "Keyboard.h"
#include "MultiLedControl.h"
#include "BaseGame.h"
#include "PointControlGame.h"
#include "MatrixTest.h"

const byte kbdRowPins[] = {4, 5, 6};
const byte kbdColPins[] = {7, 8, 9};

Keyboard kbd = Keyboard(3, 3, kbdRowPins, kbdColPins);
MultiLedControl lc = MultiLedControl(12,11,10,2,2,8,8);
BaseGame *game;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1);
  /* and clear the display */
  lc.clearDisplay();
  //game = new PointControlGame(&kbd, &lc);
  game = new MatrixTest(&kbd, &lc);
}

void loop() {
  game->loop();
}

// vim:ai:et:sw=2

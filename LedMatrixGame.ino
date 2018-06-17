#include "Keyboard.h"
#include "KeyDef.h"
#include "MultiLedControl.h"
#include "BaseGame.h"
#include "MatrixTest.h"
#include "PointControlGame.h"
#include "SnakeGame.h"

const byte kbdRowPins[] = {4, 5, 6};
const byte kbdColPins[] = {7, 8, 9};

Keyboard kbd = Keyboard(3, 3, kbdRowPins, kbdColPins);
MultiLedControl lc = MultiLedControl(12,11,10,2,2,8,8);
BaseGame *game;
bool pause;

void setup() {
  randomSeed(analogRead(0));
  lc.shutdown(false);
  lc.setIntensity(1);
  lc.clearDisplay();
  // game = new MatrixTest(&kbd, &lc);
  // game = new PointControlGame(&kbd, &lc);
  pause = false;
  game = new SnakeGame(&kbd, &lc);
}

void loop() {
  kbd.read();

  if (kbd.isKeyPress(KEY_START))
    pause = !pause;
  if (kbd.isKeyPress(KEY_SELECT)) {
    if (game != NULL) {
      delete game;
      game = new SnakeGame(&kbd, &lc);
    }
  }

  if (game != NULL && !pause) game->loop();
}

// vim:ai:et:sw=2

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

#define GAME_FACTORY(CLASS) \
  [](Keyboard *kbd, MultiLedControl *lc){ return (BaseGame*)new CLASS(kbd, lc); }

BaseGame *(*games[])(Keyboard *kbd, MultiLedControl *lc) = {
  GAME_FACTORY(SnakeGame),
  GAME_FACTORY(PointControlGame),
};
int gameIndex;

BaseGame *newGame() {
  return games[gameIndex](&kbd, &lc);
}

void setup() {
  randomSeed(analogRead(0));
  lc.shutdown(false);
  lc.setIntensity(1);
  lc.clearDisplay();

  pause = false;
  gameIndex = 0;
  game = newGame();
}

void loop() {
  kbd.read();

  if (kbd.isKeyPress(KEY_START))
    pause = !pause;
  if (kbd.isKeyPress(KEY_SELECT)) {
    if (game != NULL)
      delete game;
    if (++gameIndex >= (sizeof(games) / sizeof(*games)))
      gameIndex = 0;
    game = newGame();
  }

  if (game != NULL && !pause) game->loop();
}

// vim:ai:et:sw=2

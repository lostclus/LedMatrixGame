#include "Keyboard.h"
#include "KeyDef.h"
#include "MultiLedControl.h"
#include "BaseGame.h"
#include "MatrixTest.h"
#include "PointControlGame.h"
#include "SnakeGame.h"

#define WITH_STM32
#undef WITH_ARDUINO

#ifdef WITH_ARDUINO
#define KBD_ROW1_PIN 4
#define KBD_ROW2_PIN 5
#define KBD_ROW3_PIN 6
#define KBD_COL1_PIN 7
#define KBD_COL2_PIN 8
#define KBD_COL3_PIN 9
#define LED_MATRIX_MISO_PIN 12
#define LED_MATRIX_MOSI_PIN 11
#define LED_MATRIX_SS_PIN 10
#endif

#ifdef WITH_STM32
#define KBD_ROW1_PIN PB12
#define KBD_ROW2_PIN PB13
#define KBD_ROW3_PIN PB14
#define KBD_COL1_PIN PB15
#define KBD_COL2_PIN PA8
#define KBD_COL3_PIN PA9
#define LED_MATRIX_MISO_PIN PA6
#define LED_MATRIX_MOSI_PIN PA7
#define LED_MATRIX_SS_PIN PA4
#endif

byte kbdRowPins[] = {KBD_ROW1_PIN,
                     KBD_ROW2_PIN,
                     KBD_ROW3_PIN};
byte kbdColPins[] = {KBD_COL1_PIN,
                     KBD_COL2_PIN,
                     KBD_COL3_PIN};

Keyboard kbd = Keyboard(3, 3, kbdRowPins, kbdColPins);
MultiLedControl lc = MultiLedControl(LED_MATRIX_MISO_PIN,
                                     LED_MATRIX_MOSI_PIN,
                                     LED_MATRIX_SS_PIN,
                                     2, 2, 8, 8);
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
  unsigned long now = millis();
  kbd.read(now);

  if (kbd.isKeyPress(KEY_START)) {
    if (game == NULL || !game->handleStart())
      pause = !pause;
  }
  if (kbd.isKeyPress(KEY_SELECT)) {
    if (game == NULL || !game->handleSelect()) {
      if (game != NULL)
        delete game;
      if (++gameIndex >= (sizeof(games) / sizeof(*games)))
        gameIndex = 0;
      game = newGame();
    }
  }

  if (game != NULL && !pause) game->loop();
}

// vim:ai:et:sw=2

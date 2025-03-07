#include <GyverMAX7219.h>
#include <RunningGFX.h>


#include "Display.h"
#include "Keyboard.h"
#include "KeyDef.h"
#include "Speaker.h"
#include "BaseGame.h"
#include "PointControlGame.h"
#include "SnakeGame.h"
#include "Arkanoid.h"

#define BUZZER_PIN 2
#define KBD_ROW1_PIN 4
#define KBD_ROW2_PIN 5
#define KBD_ROW3_PIN 6
#define KBD_COL1_PIN 7
#define KBD_COL2_PIN 8
#define KBD_COL3_PIN 9

byte kbdRowPins[] = {KBD_ROW1_PIN,
                     KBD_ROW2_PIN,
                     KBD_ROW3_PIN};
byte kbdColPins[] = {KBD_COL1_PIN,
                     KBD_COL2_PIN,
                     KBD_COL3_PIN};

// GyverMAX7219
// MAX7219 <2, 2, 10, 12, 11> mtrx;
// mtrx.setType(GM_SERIES);
// mtrx.setConnection(GM_RIGHT_BOTTOM_LEFT);

Keyboard *kbd;
Display *disp;
Speaker *spk;
BaseGame *game;
bool isPause;

typedef BaseGame *game_factory_t(Keyboard *kbd, Display *disp, Speaker *spk);
typedef struct game_t {
  char *name;
  game_factory_t *factory;
};

#define GAME_FACTORY(CLASS) \
  [](Keyboard *kbd, Display *disp, Speaker *spk){ return (BaseGame*)new CLASS(kbd, disp, spk); }

const char SNAKE_NAME[] PROGMEM = "Snake";
const char POINT_CONTROL_NAME[] PROGMEM = "Point control";
const char ARKANOID_NAME[] PROGMEM = "Arkanoid";

game_t games[] = {
  {
    SNAKE_NAME,
    GAME_FACTORY(SnakeGame),
  },
  {
    POINT_CONTROL_NAME,
    GAME_FACTORY(PointControlGame),
  },
  {
    ARKANOID_NAME,
    GAME_FACTORY(ArkanoidGame),
  }
};

int gameIndex;

BaseGame *newGame() {
  return games[gameIndex].factory(kbd, disp, spk);
}

void updateMenu() {
  int dw = disp->matrix.width(),
      dh = disp->matrix.height();

  spk->stop();

  disp->matrix.clearDisplay();
  disp->matrix.clear();

  disp->run.setSpeed(15);
  disp->run.setWindow(0, dw - 1, dh / 2 - 4);
  disp->run.setText_P(games[gameIndex].name);
  disp->run.start();
}

void setup() {
  // Serial.begin(115200);
  // Serial.println("Starting...");
  randomSeed(analogRead(0));
  pinMode(BUZZER_PIN, OUTPUT);

  kbd = new Keyboard(3, 3, kbdRowPins, kbdColPins);
  disp = new Display();
  disp->begin();
  spk = new Speaker(BUZZER_PIN);

  isPause = false;
  gameIndex = 0;
  game = NULL;
  updateMenu();
}

void loop() {
  unsigned long now = millis();

  kbd->read(now);
  if (kbd->isKeyPress(KEY_START)) {
    
    if (game == NULL) {
      disp->run.stop();
      disp->matrix.clear();
      disp->matrix.clearDisplay();
      game = newGame();
    } else {
      if (game->isGameOver) {
        disp->matrix.clear();
        disp->matrix.clearDisplay();
        game->reset();
      } else {
        isPause = !isPause;
      }
    }
  }
  if (kbd->isKeyPress(KEY_MENU)) {
    if (game != NULL) {
      delete game;
      game = NULL;
      updateMenu();
    }
  }

  if (game != NULL) {
    if (!isPause) game->handle();
    spk->handle();
  } else {
    if (kbd->isKeyPress(KEY_LEFT) || kbd->isKeyPress(KEY_UP)) {
      gameIndex = max(0, gameIndex - 1);
      updateMenu();
    }
    if (kbd->isKeyPress(KEY_RIGHT) || kbd->isKeyPress(KEY_DOWN)) {
      gameIndex = min((int)(sizeof(games) / sizeof(games[0])) - 1, gameIndex + 1);
      updateMenu();
    }

    disp->run.tick();
  }
}

// vim:ai:et:sw=2

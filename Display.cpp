#include "Display.h"

Display::Display() : matrix(), run(&matrix) {
}

void Display::begin() {
  matrix.begin();
  matrix.setType(LED_MATRIX_TYPE);
  matrix.setConnection(LED_MATRIX_CONNECTION);
  matrix.setBright(5);
  matrix.clearDisplay();
  matrix.clear();
}

void Display::runGameOver() {
  run.setSpeed(15);
  run.setWindow(0, matrix.width() - 1, matrix.height() / 2 - 4);
  run.setText_P(PSTR("GAME OVER"));
  run.start();
}

// vim:ai:et:sw=2

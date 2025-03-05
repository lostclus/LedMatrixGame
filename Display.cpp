#include "Display.h"

Display::Display() : matrix(), run(&matrix) {
}

void Display::begin() {
  Serial.println(F("matrix.begin..."));
  matrix.begin();
  matrix.setType(LED_MATRIX_TYPE);
  matrix.setConnection(LED_MATRIX_CONNECTION);
  matrix.setBright(5);
  matrix.clearDisplay();
  matrix.clear();
}

// vim:ai:et:sw=2

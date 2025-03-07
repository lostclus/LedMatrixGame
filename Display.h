#ifndef XX_Display_h
#define XX_Display_h

#include <GyverMAX7219.h>
#include <RunningGFX.h>

#define LED_MATRIX_CS_IN 10
#define LED_MATRIX_H_DEVS 2
#define LED_MATRIX_V_DEVS 2
#define LED_MATRIX_TYPE GM_SERIES
#define LED_MATRIX_CONNECTION GM_RIGHT_BOTTOM_LEFT

class Display {
  public:
    MAX7219 < LED_MATRIX_H_DEVS, LED_MATRIX_V_DEVS, LED_MATRIX_CS_IN > matrix;
    RunningGFX run;

    Display();
    void begin();

    void runGameOver();
};

#endif	//Display.h
// vim:ai:et:sw=2

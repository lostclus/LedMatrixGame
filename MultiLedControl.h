#ifndef MultiLedControl_h
#define MultiLedControl_h

#include <LedControl.h>

class MultiLedControl {
  public:
    int vNumDevices,
        hNumDevices,
        vDevSize,
        hDevSize;
    LedControl lc;
    int devMap[8];

    MultiLedControl(int dataPin, int clkPin, int csPin,
                    int vNumDevices, int hNumDevices,
                    int vDevSize, int hDevSize);
    void shutdown(bool status);
    void setIntensity(int intensity);
    void clearDisplay();
    void setLed(int row, int col, boolean state);
    void setRow(int row, word value);
    void setColumn(int col, word value);
    int getRowsCount();
    int getColumnsCount();
};

#endif	//MultiLedControl.h
// vim:ai:et:sw=2

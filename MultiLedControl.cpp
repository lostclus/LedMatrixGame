#include "MultiLedControl.h"

MultiLedControl::MultiLedControl(int dataPin, int clkPin, int csPin,
                                 int vNumDevices, int hNumDevices,
                                 int vDevSize, int hDevSize) :
  lc(dataPin, clkPin, csPin, vNumDevices * hNumDevices) {
  this->vNumDevices = vNumDevices;
  this->hNumDevices = hNumDevices;
  this->vDevSize = vDevSize;
  this->hDevSize = hDevSize;

  for (int dr=0, i=vNumDevices * hNumDevices; dr<vNumDevices; dr++)
    for (int dc=0; dc<hNumDevices; dc++)
      devMap[dr * vNumDevices + dc] = --i;
}

void MultiLedControl::shutdown(bool status) {
  for (int i=0; i<lc.getDeviceCount(); i++) lc.shutdown(i, status);
}

void MultiLedControl::setIntensity(int intensity) {
  for (int i=0; i<lc.getDeviceCount(); i++) lc.setIntensity(i, intensity);
}

void MultiLedControl::clearDisplay() {
  for (int i=0; i<lc.getDeviceCount(); i++) lc.clearDisplay(i);
}

void MultiLedControl::setLed(int row, int col, boolean state) {
  int dr = row / vDevSize,
      dc = col / hDevSize;
  lc.setLed(devMap[dr * vNumDevices + dc],
            row % vDevSize, col % hDevSize,
            state);
}

void MultiLedControl::setRow(int row, word value) {
  int dr = row / vDevSize;
  for (int dc=hNumDevices-1; dc>=0; dc--) {
    lc.setRow(devMap[dr * vNumDevices + dc],
              row % vDevSize, (byte)(value & 0xff));
    value >>= 8;
  }
}

void MultiLedControl::setColumn(int col, word value) {
  int dc = col / hDevSize;
  for (int dr=vNumDevices-1; dr>=0; dr--) {
    lc.setColumn(devMap[dr * vNumDevices + dc],
                 col % hDevSize, (byte)(value & 0xff));
    value >>= 8;
  }
}

int MultiLedControl::getRowsCount() {
  return vDevSize * vNumDevices;
}

int MultiLedControl::getColumnsCount() {
  return hDevSize * hNumDevices;
}

// vim:ai:et:sw=2

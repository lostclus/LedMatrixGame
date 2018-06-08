#include "MatrixTest.h"

MatrixTest::MatrixTest(Keyboard *kbd, MultiLedControl *lc)
  : BaseGame(kbd, lc) {
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void MatrixTest::writeArduinoOnMatrix() {
  lc->clearDisplay();
  /* here is the data for the characters */
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  /* now display them one by one with a small delay */
  lc->setRow(0,a[0]);
  lc->setRow(1,a[1]);
  lc->setRow(2,a[2]);
  lc->setRow(3,a[3]);
  lc->setRow(4,a[4]);
  delay(delaytime);
  lc->setRow(0,r[0]);
  lc->setRow(1,r[1]);
  lc->setRow(2,r[2]);
  lc->setRow(3,r[3]);
  lc->setRow(4,r[4]);
  delay(delaytime);
  lc->setRow(0,d[0]);
  lc->setRow(1,d[1]);
  lc->setRow(2,d[2]);
  lc->setRow(3,d[3]);
  lc->setRow(4,d[4]);
  delay(delaytime);
  lc->setRow(0,u[0]);
  lc->setRow(1,u[1]);
  lc->setRow(2,u[2]);
  lc->setRow(3,u[3]);
  lc->setRow(4,u[4]);
  delay(delaytime);
  lc->setRow(0,i[0]);
  lc->setRow(1,i[1]);
  lc->setRow(2,i[2]);
  lc->setRow(3,i[3]);
  lc->setRow(4,i[4]);
  delay(delaytime);
  lc->setRow(0,n[0]);
  lc->setRow(1,n[1]);
  lc->setRow(2,n[2]);
  lc->setRow(3,n[3]);
  lc->setRow(4,n[4]);
  delay(delaytime);
  lc->setRow(0,o[0]);
  lc->setRow(1,o[1]);
  lc->setRow(2,o[2]);
  lc->setRow(3,o[3]);
  lc->setRow(4,o[4]);
  delay(delaytime);
  lc->setRow(0,0);
  lc->setRow(1,0);
  lc->setRow(2,0);
  lc->setRow(3,0);
  lc->setRow(4,0);
  delay(delaytime);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void MatrixTest::rows() {
  lc->clearDisplay();
  for(int row=0; row<16; row++) {
    delay(delaytime);
    lc->setRow(row, 0b1101100010100000);
    delay(delaytime);
    lc->setRow(row, 0);
    for(int i=0; i<row; i++) {
      delay(delaytime);
      lc->setRow(row, 0b1101100010100000);
      delay(delaytime);
      lc->setRow(row, 0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void MatrixTest::columns() {
  lc->clearDisplay();
  for(int col=0; col<16; col++) {
    delay(delaytime);
    lc->setColumn(col, 0b1101100010100000);
    delay(delaytime);
    lc->setColumn(col, 0);
    for(int i=0; i<col; i++) {
      delay(delaytime);
      lc->setColumn(col, 0b1101100010100000);
      delay(delaytime);
      lc->setColumn(col, 0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void MatrixTest::single() {
  for(int row=0;row<16;row++) {
    for(int col=0;col<16;col++) {
      delay(delaytime);
      lc->setLed(row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc->setLed(row,col,false);
        delay(delaytime);
        lc->setLed(row,col,true);
        delay(delaytime);
      }
    }
  }
}

void MatrixTest::loop() { 
  writeArduinoOnMatrix();
  rows();
  columns();
  single();
}

// vim:et:sw=2:ai

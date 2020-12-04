#ifndef DIGITCONTROL_h
#define DIGITCONTROL_h

#include "MotorDriver.h"


class DigitControl {
 public:
  DigitControl(int32_t* value = 0, uint8_t lcdCol = 0, uint8_t lcdRow = 0);
  void MoveDecimalPosRight();
  void MoveDecimalPosLeft();
  void IncrementValue();
  void DecrementValue();
  void Print();
 private:
  void PrintValue();
  void PrintCursor();
  uint8_t decimalPos;
  int32_t* value;
  uint8_t lcdCol;
  uint8_t lcdRow;
  uint8_t DEC_NUM = 6;
};

// Externs
extern DigitControl digitControl;

#endif

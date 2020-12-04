#include "globals.h"

SerialLCD lcd = SerialLCD(0,PIN_SEROUT);
MotorPowerState_t eMotorPowerState = disable;
AccelStepper stepMotor;
DigitControl digitControl;
sMotorSettings_t sMotorSettings;
SampleRun_t sSampleRuns[12];
elapsedMillis timeElapsed;


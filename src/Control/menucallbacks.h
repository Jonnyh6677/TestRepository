#ifndef MENUCALLBACKS_h
#define MENUCALLBACKS_h

#include "MotorDriver.h"
void mFunc_digitRotation(uint8_t param);
// Callback function declarations
void mFunc_startMoveStepsInit(uint8_t param);
void mFunc_startSlitsRun(uint8_t sampleRun);
void mFunc_startSlitStepRun(uint8_t axis);
void mFunc_startWLRun(uint8_t sampleRun);
void mFunc_clearEeprom(uint8_t param);
void mFunc_back(uint8_t param);
void mFunc_startSerialMode(uint8_t param);
void mFunc_startMoveSteps(uint8_t param);
void mFunc_enableMotor(uint8_t param);
void mFunc_disableMotor(uint8_t param);
void mFunc_startInitRun(uint8_t param);

void mFunc_setSpeed(uint8_t param);
void mFunc_setAxisRange(uint8_t param);
void mFunc_setRotationDir(uint8_t param);
void mFunc_setSensorPolarity(uint8_t param);
void mFunc_setAcceleration(uint8_t param);
void mFunc_setVref(uint8_t param);
void mFunc_setDefaultSettings(uint8_t param);
void mFunc_printStatus(uint8_t param);
void mFunc_initSettings(uint8_t axisType);
void mFunc_saveSettingsToEeprom(uint8_t param);

void mFunc_startExampleRun(uint8_t sampleRun);
void mFunc_startStepCheck(uint8_t param);
void mFunc_startLongTimeRun(uint8_t param);
void mFunc_startMoveToSpecialPos(uint8_t pos);
void mFunc_startOffsetRun(uint8_t param);

void mFunc_showAxisName(uint8_t line);

#endif

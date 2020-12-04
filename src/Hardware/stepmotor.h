#ifndef STEPMOTOR_h
#define STEPMOTOR_h

#include "MotorDriver.h"

typedef enum
{
  disable = 0,
  enable
}MotorPowerState_t;

// Externs
extern MotorPowerState_t eMotorPowerState;

// Function declarations
void vMotorPowerStateTrasition();
void vMotorPowerEnable();
void vMotorPowerDisable();
void vMotorPowerStandby();
uint8_t vMotorPowerGetState();

void vInitializeMotor();
void vSetMotorDirection(void);
void vSetSensorPolarity(void);
void vSetMotorVref(void);
void vSetMotorAcceleration(void);
void vSetMotorMaxSpeed(void);
void vSetMotorPinModes(void);

#endif

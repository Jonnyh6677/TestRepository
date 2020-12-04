#include "stepmotor.h"


/*!
 @fn              void vInitializeMotor()
 @brief           Initialisiert den Motor anhand den globalen Motor-Settings in 'sMotorSettings'
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vInitializeMotor()
{
   // Motor init
   stepMotor = AccelStepper(AccelStepper::DRIVER, sMotorSettings.u8stepPin, sMotorSettings.u8dirPin);
   vSetMotorMaxSpeed();
   vSetMotorAcceleration();
   vSetMotorDirection();
   vSetMotorVref();
   vSetMotorPinModes();
   vMotorPowerDisable();
}

/*!
 @fn              void vSetMotorDirection(void)
 @brief           Definiert die Motordrehrichtung 
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vSetMotorDirection(void)
{
   stepMotor.setPinsInverted(sMotorSettings.u8dir,false,false);
}

void vSetSensorPolarity(void)
{
   stepMotor.setPinsInverted(sMotorSettings.u8LsActive,false,false);
}

/*!
 @fn              void vSetMotorMaxSpeed(void)
 @brief           Definiert die maximale Motorgeschwindigkeit (Schirtte/Sekunde)
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vSetMotorMaxSpeed(void)
{
   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax);
}

/*!
 @fn              void vSetMotorAcceleration(void)
 @brief           Definiert die Beschleunigungs- / Verzögerungsrate 
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vSetMotorAcceleration(void)
{
   stepMotor.setAcceleration(sMotorSettings.u32motorAcceleration);
}

/*!
 @fn              void vSetMotorAcceleration(void)
 @brief           Definiert den Motorstrom
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vSetMotorVref(void)
{
   analogWrite(PIN_VREF,sMotorSettings.u8vref);
}

/*!
 @fn              void vSetMotorPinModes(void)
 @brief           Setzt sämtliche Pin-Modes
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vSetMotorPinModes(void)
{
   pinMode(sMotorSettings.u8enablePin, OUTPUT);
   pinMode(sMotorSettings.u8stepPin, OUTPUT);
   pinMode(sMotorSettings.u8lsPin, INPUT);
}

/*!
 @fn              void vMotorPowerStateTrasition()
 @brief           Switch the enable/disable state of specific motor ()
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/ 
void vMotorPowerStateTrasition()
{
  switch(eMotorPowerState)
  {
    case enable:
       eMotorPowerState= disable;
       digitalWrite(sMotorSettings.u8enablePin, !digitalRead(sMotorSettings.u8enablePin));
       break;
    case disable:
       eMotorPowerState= enable;
       digitalWrite(sMotorSettings.u8enablePin, !digitalRead(sMotorSettings.u8enablePin));
       break;
    default:
       break;
  }
}

/*!
 @fn              void vMotorPowerEnable()
 @brief           Enables specific ()
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vMotorPowerEnable()
{
   eMotorPowerState= enable;
   digitalWrite(sMotorSettings.u8enablePin, LOW);
   analogWrite(PIN_VREF,sMotorSettings.u8vref);
}

/*!
 @fn              void vMotorPowerDisable()
 @brief           Disables specific ()
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vMotorPowerDisable()
{
   eMotorPowerState= disable;
   digitalWrite(sMotorSettings.u8enablePin, HIGH);
}


/*!
 @fn              void vMotorPowerStandby()
 @brief           Sets Current to Standby specific ()
 @author 	        Markus Schappacher
 @param 	        
 @return 	        void
*/
void vMotorPowerStandby()
{
   eMotorPowerState= enable;
   digitalWrite(sMotorSettings.u8enablePin, LOW);
   analogWrite(PIN_VREF,sMotorSettings.u8vrefStandby);
}


/*!
 @fn              uint8_t vMotorPowerGetState()
 @brief           Returns the state of a specific motor (u8motorIndex)
 @author 	      Jonathan Haas
 @param 	         
 @return 	      uint8_t (state of motor)
*/
uint8_t vMotorPowerGetState()
{
   return (uint8_t)eMotorPowerState;
}

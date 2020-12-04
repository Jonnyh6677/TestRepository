#include "print.h"

void vDebugPrintInfos()
{
   Serial.printf("--------------------\nDistance To Go: %d\nCurrent Position: %d\nTarget Position: %d\n---------------------\n\n", stepMotor.targetPosition());
}

void vPrintStatus()
{
   // lcd.clear();   // Ist relativ langsam...
   lcd.setPosition(0, 0);
   lcd.printf("                    ");
   lcd.setPosition(0, 0);
   lcd.printf("Spd %d  Ac %d ", sMotorSettings.u32motorSpeedMax, sMotorSettings.u32motorAcceleration);
   lcd.setPosition(0, 1);
   lcd.printf("                    ");
   lcd.setPosition(0, 1);
   lcd.printf("Target  %d", stepMotor.targetPosition());
   lcd.setPosition(0, 2);
   lcd.printf("                    ");
   lcd.setPosition(0, 2);
   lcd.printf("Current %d", stepMotor.currentPosition());
   lcd.setPosition(13, 2);
   lcd.printf("LS    %d", !digitalRead(sMotorSettings.u8lsPin));
   lcd.setPosition(0, 3);
   lcd.printf("Loop %d", sMotorSettings.u32loop); // Anzahl der einzelnen Durchläufe im Dauerlauf
   //##lcd.setPosition(0, 3);
   //## lcd.print("[Black] := Stop/Back");
}


void vPrintSettings()
{
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Spd:%d Ac:%d ", sMotorSettings.u32motorSpeedMax, sMotorSettings.u32motorAcceleration);
   lcd.setPosition(0, 1);
   lcd.printf("Range:%d Dir:%d", sMotorSettings.u32axisRange, sMotorSettings.u8dir);
   lcd.setPosition(0, 2);
   lcd.printf("LsSig:%d LsRange:%d", sMotorSettings.u8LsActive, sMotorSettings.u16lsRangeSteps);
   lcd.setPosition(0, 3);
   lcd.print("[Black] := Stop/Back");
}

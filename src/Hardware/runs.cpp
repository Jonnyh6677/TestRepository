#include "runs.h"

/*!
 @fn              void vRunsInitRun(uint32_t initPosition )
 @brief           Init specific motor (u8motorIndex) and set position on LS to (initPosition)
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void vRunsInitRun(uint32_t initPosition)
{
   // u8motorIndex = 0;    //## Fixierung des Index
   IntervalTimer stepTimer;

   // set motor acceleration
   vSetMotorAcceleration();

   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax); //## zum Initialisieren halbe Geschwindigkeit

   // motor position is in LS range
   if (digitalRead(sMotorSettings.u8lsPin) == sMotorSettings.u8LsActive)
   {
      // Run out of LS
      vRunsMoveTo(sMotorSettings.u16lsRangeSteps);
   }

   int32_t decSteps = 0;
   vRunsMoveToLsSig(-sMotorSettings.u32axisRange, &decSteps);

   // Set LS positon to zero
   stepMotor.setCurrentPosition(sMotorSettings.u32axisZeropoint + decSteps);
   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax);
}

/*!
 @fn              vRunsOffsetInFrontLsRun(uint32_t* steps)
 @brief           Moves to LS and writes the step offset in uint32_t* steps
 @author 	      Jonathan Haas
 @param 	         uint32_t* steps 
 @param 	         
 @return 	      void
*/
void vRunsOffsetInFrontLsRun(uint32_t *steps)
{

   // u8motorIndex = 0;    //## Fixierung des Index
   IntervalTimer stepTimer;

   // set motor acceleration
   vSetMotorAcceleration();

   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax / 2); // zum Initialisieren halbe Geschwindigkeit

   stepMotor.setCurrentPosition(0);
   // Move to LS
   int32_t decSteps = 0;
   int32_t offset = vRunsMoveToLsSig(-3 * sMotorSettings.u32axisRange, &decSteps);
   *steps = offset + decSteps;
}

/*!
 @fn              vRunsOffsetBehindLsRun(uint32_t* steps)
 @brief           Moves to LS and writes the step offset in uint32_t* steps
 @author 	      Jonathan Haas
 @param 	         uint32_t* steps 
 @param 	         
 @return 	      void
*/
void vRunsOffsetBehindLsRun(uint32_t *steps)
{

   // u8motorIndex = 0;    //## Fixierung des Index
   IntervalTimer stepTimer;

   // set motor acceleration
   vSetMotorAcceleration();

   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax / 2); // zum Initialisieren halbe Geschwindigkeit

   stepMotor.setCurrentPosition(0);
   // Move to LS
   int32_t decSteps = 0;
   int32_t offset = vRunsMoveToLsSig(sMotorSettings.u32axisRange, &decSteps);
   *steps = offset - decSteps;
}

/*!
 @fn              void vRunsStartOffsetRun()
 @brief           Starts the offset run (template function)
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vRunsStartOffsetRun()
{

   uint32_t lsOffset = 0;
   uint32_t u32AxisRange = 0;
   // LCD print
   vMotorPowerDisable();
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.print("Pull axis on");
   lcd.setPosition(0, 1);
   lcd.print("outer stop");
   lcd.setPosition(0, 2);
   lcd.print("[BLACK] : Cancel");
   lcd.setPosition(0, 3);
   lcd.print("[OK] = Confirm");

   delay(300);
   while (digitalRead(PIN_JOYSTICK_CENTRE)) // Back: Abbruch & OK: Bestätigung
   {
      if (!digitalRead(PIN_BUTTON_BLACK))
      {
         return;
      }
   }
   vMotorPowerEnable();
   vRunsOffsetInFrontLsRun(&u32AxisRange);
   // LCD print
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Offset: %d", u32AxisRange);
   lcd.setPosition(0, 2);
   lcd.print("[BLACK] : Cancel");
   lcd.setPosition(0, 3);
   lcd.print("[OK] = Confirm");
   delay(300);
   while (digitalRead(PIN_JOYSTICK_CENTRE)) // Back: Abbruch & OK: Bestätigung
   {
      if (!digitalRead(PIN_BUTTON_BLACK))
      {
         return;
      }
   }

   vMotorPowerDisable();
   // LCD print
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.print("Pull axis on");
   lcd.setPosition(0, 1);
   lcd.print("inner stop");
   lcd.setPosition(0, 2);
   lcd.print("[BLACK] : Cancel");
   lcd.setPosition(0, 3);
   lcd.print("[OK] = Confirm");
   delay(300);
   while (digitalRead(PIN_JOYSTICK_CENTRE)) // Back: Abbruch & OK: Bestätigung
   {
      if (!digitalRead(PIN_BUTTON_BLACK))
      {
         return;
      }
   }
   vMotorPowerEnable();
   vRunsOffsetBehindLsRun(&lsOffset);
   // LCD print
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Offset: %d", lsOffset);
   lcd.setPosition(0, 2);
   lcd.print("[BLACK] : Cancel");
   lcd.setPosition(0, 3);
   lcd.print("[OK] = Confirm");
   delay(300);
   while (digitalRead(PIN_JOYSTICK_CENTRE)) // Back: Abbruch & OK: Bestätigung
   {
      if (!digitalRead(PIN_BUTTON_BLACK))
      {
         return;
      }
   }
   // LCD print
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Would you set");
   lcd.setPosition(0, 1);
   lcd.printf("%d as axis range?", u32AxisRange);
   lcd.setPosition(0, 2);
   lcd.print("[BLACK] : Cancel");
   lcd.setPosition(0, 3);
   lcd.print("[OK] = Confirm");
   delay(300);
   while (digitalRead(PIN_JOYSTICK_CENTRE)) // Back: Abbruch & OK: Bestätigung
   {
      if (!digitalRead(PIN_BUTTON_BLACK))
      {
         return;
      }
   }
   sMotorSettings.u32axisRange = u32AxisRange;
   // LCD print
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Axis range saved..");
   delay(1000);
}

/*!
 @fn              vRunsMoveToLs(, int32_t targetPosition)
 @brief           Moves motor specific motor (u8motorIndex) to absolute position (positionAbsolute)
 @author 	        Jonathan Haas
 @param 	        uint32_t positionAbsolute
 @return 	        void
*/
int32_t vRunsMoveToLsSig(int32_t targetPosition, int32_t *decSteps)
{
   int32_t startPosition = stepMotor.currentPosition();
   *decSteps = 0;
   // u8motorIndex = 0;    //## Fixierung des Index
   IntervalTimer stepTimer;

   // Move to LS
   stepMotor.moveTo(targetPosition);

   // LS Interrupt
   attachInterrupt(sMotorSettings.u8lsPin, lsinterrupt, CHANGE);

   // Start moving
   stepTimer.begin(TIMER0_ISR, TIMER_STEP_INTERVAL);

   // Move to LS
   while (digitalRead(PIN_BUTTON_BLACK) && sMotorSettings.u8lsflag == 0 && stepMotor.isRunning())
   {
      //Move until LS changes signal
   }

   // detach ls Interrupt
   detachInterrupt(sMotorSettings.u8lsPin);
   // clear ls flag
   sMotorSettings.u8lsflag = 0;
   // disable interrupt
   stepTimer.end();
   // Deceleration
   *decSteps = s32RunsMotorStop();

   int32_t movedSteps = abs(startPosition - stepMotor.currentPosition());

   return movedSteps;
}

/*!
 @fn              vRunsExampleRun(uint8_t num)
 @brief           Moves motor specific motor (u8motorIndex) to absolute position (positionAbsolute)
 @author 	        Jonathan Haas
 @param 	        uint32_t positionAbsolute
 @return 	        void
*/
void vRunsExampleRun(uint8_t run)
{
   lcd.clear();

   // num of positions
   for (uint8_t i = 0; i < sSampleRuns[run].u32num_positions; i++)
   {
      // Move to samplerun position
      vRunsMoveTo(sSampleRuns[run].u32positions[i]);
   }
}

/*!
 @fn              vRunsMoveToSpecialPos(uint8_t pos)
 @brief           Moves to n specific position (Links/Rechts/Mitte)
 @author 	        Jonathan Haas
 @param 	        uint32_t positionAbsolute
 @return 	        void
*/
void vRunsMoveToSpecialPos(uint8_t u8pos)
{
   lcd.clear();

   switch (u8pos)
   {
   case POS_LEFT:
      vRunsMoveTo(sMotorSettings.u32axisZeropoint);
      break;
   case POS_RIGHT:
      vRunsMoveTo(sMotorSettings.u32axisRange);
      break;
   case POS_MIDDLE:
      vRunsMoveTo(sMotorSettings.u32axisRange / 2);
      break;
   default:
      break;
   }
}

/*!
 @fn              void vRunsMoveTo(uint32_t positionAbsolute,)
 @brief           Moves motor specific motor (u8motorIndex) to absolute position (positionAbsolute)
 @author 	        Jonathan Haas
 @param 	        uint32_t positionAbsolute
 @return 	        void
*/
void vRunsMoveTo(int32_t positionAbsolute)
{
   timeElapsed = 0;
   IntervalTimer stepTimer;

   // set target position
   stepMotor.moveTo(positionAbsolute);
   // Start moving
   stepTimer.begin(TIMER0_ISR, TIMER_STEP_INTERVAL);
   // move to target position
   while (stepMotor.isRunning() && digitalRead(PIN_BUTTON_BLACK))
   {
      // Print Status every 200ms
      if (timeElapsed > DISPLAY_PRINT_DELAY)
      {
         vPrintStatus();
         timeElapsed = 0;
      }
   }
   // Stop movement
   stepTimer.end();
}

/*!
 @fn              void vRunsTestMoveTo(uint32_t positionAbsolute,)
 @brief           Moves motor in a simplified way (u8motorIndex) to absolute position (positionAbsolute)
 @author 	        Markus Schappacher
 @param 	        uint32_t positionAbsolute
 @return 	        void
*/
void vRunsTestMoveTo()
{
   int32_t i32step = 500;
   int32_t i32do = 0;
   digitalWrite(PIN_ENABLE, LOW); // Enable aktiv --> Motor bestromt
   analogWrite(PIN_VREF, 80);     // 80 = 270mA
   digitalWrite(PIN_DIR, LOW);    // Schrittmotor Richtung
   for (i32do = 0; i32do < i32step; i32do++)
   {
      digitalWrite(PIN_STEP, LOW); // Step-Pulse
      delay(2);
      if (!digitalRead(PIN_BUTTON_BLACK)) // Wenn escape gedrückt ist, dann
      {
         // Run set close flag
      }
      digitalWrite(PIN_STEP, HIGH); // Step-Pulse
      delay(2);
   }
   digitalWrite(PIN_ENABLE, HIGH); // Enable inaktiv --> Motor nicht bestromt
   LCDML.FUNC_goBackToMenu();      // geht auf die aufrufende Menuebene
   LCDML.FUNC_close();             // Abschluss
                                   //## LCDML.FUNC_goBackToMenu();
}

/*!
 @fn              void vRunsSerialMode()
 @brief           Start receiving serial commands for specific motor () and execute movements etc.
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vRunsSerialMode()
{
   uint8_t command = 0; // Serial command
   int32_t value = 0;   // serial command value

   // Read serial input while command is not 'e' (End)
   do
   {
      String cmd_string;
   
      // get serial input
      if (Serial.available())
      {
         cmd_string = Serial.readString(30);
         Serial.print(cmd_string);
      }

      // split string into command char
      command = cmd_string[0];

      // Print target positions
    vPrintSettings();

      // get value of command from string
      value = atoi((const char *)&cmd_string[2]);

      // execute commands
      switch (command)
      {
      case 'i':
         vMotorPowerEnable();
         vRunsInitRun(sMotorSettings.u32axisZeropoint);
         vMotorPowerDisable();
         break;
      case 'w':
         //Serial.printf("Move %d WL \n",value);
         vRunsMoveToWl(value, MON_TYPE_SF2);
         break;
      case 'm':
         vMotorPowerEnable();
         //Serial.printf("Move Grating %d Steps \n",value);
         //vRunsInitRun(sMotorSettings.u32axisZeropoint,AXIS_ONE);
         vRunsMoveTo(value);
         vMotorPowerDisable();
         break;
      default:
         break;
      }

   } while (command != 'e' && digitalRead(PIN_BUTTON_BLACK));
}

/*!
 @fn              void vRunsStepLoseCheck()
 @brief           Starts the the StepLoseRun which runs several example runs and calculates and prints lost steps
 @author 	      Jonathan Haas
 @param 	         
 @return 	      void
*/
void vRunsStepLoseCheck()
{
   IntervalTimer stepTimer;
   int32_t lostSteps;
   // Steps that are used for deceleration
   int32_t declSteps = 0;

   // First init to ls
   vRunsInitRun(sMotorSettings.u32axisZeropoint);
   // clear lcd
   lcd.clear();

   // Run 5 times example run [1]
   for (int j = 0; j < 5; j++)
   {
      // Run examle run [1]
      vRunsExampleRun(1);
   }

   // Move to farest position on axis
   vRunsMoveTo(sMotorSettings.u32axisRange);

   // Set half speed on to LS
   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax / 2);

   // Move to LS and writes decleration steps in [declSteps]
   vRunsMoveToLsSig(-sMotorSettings.u32axisRange, &declSteps);
   // Calculate lost steps
   lostSteps = stepMotor.currentPosition() - sMotorSettings.u32axisZeropoint - declSteps;

   // Set LS positon to zero
   stepMotor.setCurrentPosition(sMotorSettings.u32axisZeropoint + declSteps);
   stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax);

   // print info
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Step diff: %d", lostSteps);
   lcd.setPosition(0, 3);
   lcd.print("[BLACK] : Back");
}

/*!
 @fn              void vProcessSlitsRun()
 @brief           Starts slit run on   AXIS_TYPE_SF2_EX_SLIT_IN
                                       AXIS_TYPE_SF2_EX_SLIT_MID
                                       AXIS_TYPE_SF2_EX_SLIT_OUT

 @author 	      Jonathan Haas / Markus Schappacher 
 @param 	         int8_t sampleRun, uint8_t step
 @return 	      void
*/
void vProcessSlitsRun(uint8_t sampleRun, uint8_t step)
{

   if (step == 1)
   {
      // Motor und samples auf Achse konfigurieren
      vLoadSettings(AXIS_TYPE_SF2_EX_SLIT_IN);
      vSetExampleRuns(AXIS_TYPE_SF2_EX_SLIT_IN);
      vInitializeMotor();

      sMotorSettings.u32loop = step;
      vMotorPowerEnable();
      sMotorSettings.u8isInit = 0; // Init erzwingen

      if (sMotorSettings.u8isInit == 0)
      {
         vRunsInitRun(sMotorSettings.u32axisZeropoint);
         sMotorSettings.u8isInit = 1;
      }

      vPrintStatus();
      vRunsMoveTo(sSampleRuns[sampleRun].u32positions[0]);
      // vMotorPowerStandby();
      vMotorPowerDisable();
      // Print status infos on display
      vPrintStatus();
   }

   if (step == 2)
   {
      // Motor und samples auf Achse konfigurieren
      vLoadSettings(AXIS_TYPE_SF2_EX_SLIT_MID);
      vSetExampleRuns(AXIS_TYPE_SF2_EX_SLIT_MID);
      vInitializeMotor();

      sMotorSettings.u32loop = step;
      vMotorPowerEnable();
      sMotorSettings.u8isInit = 0; // Init erzwingen

      if (sMotorSettings.u8isInit == 0)
      {
         vRunsInitRun(sMotorSettings.u32axisZeropoint);
         sMotorSettings.u8isInit = 1;
      }
      vPrintStatus();
      vRunsMoveTo(sSampleRuns[sampleRun].u32positions[0]);
      // vMotorPowerStandby();
      vMotorPowerDisable();
      // Print status infos on display
      vPrintStatus();
   }

   if (step == 3)
   {
      // Motor und samples auf Achse konfigurieren
      vLoadSettings(AXIS_TYPE_SF2_EX_SLIT_OUT);
      vSetExampleRuns(AXIS_TYPE_SF2_EX_SLIT_OUT);
      vInitializeMotor();

      sMotorSettings.u32loop = step;
      vMotorPowerEnable();
      sMotorSettings.u8isInit = 0; // Init erzwingen

      if (sMotorSettings.u8isInit == 0)
      {
         vRunsInitRun(sMotorSettings.u32axisZeropoint);
         sMotorSettings.u8isInit = 1;
      }

      vPrintStatus();
      vRunsMoveTo(sSampleRuns[sampleRun].u32positions[0]);
      // vMotorPowerStandby();
      vMotorPowerDisable();
      // Print status infos on display
      vPrintStatus();
   }
}

/*!
 @fn              void vProcessWLRun()
 @brief           Starts Wavelength Setting with AXIS_TYPE_SF2_Grating

 @author 	      Jonathan Haas / Markus Schappacher 
 @param 	         int8_t sampleRun, uint8_t step
 @return 	      void
*/
void vProcessWLRun(uint8_t sampleRun, uint8_t step)
{
}

/*!
 @fn              int32_t s32RunsMotorStop()
 @brief           Führt die Bremsrampe aus und gibt die Anzahl der dafür ausgeführten Schritte zurück.
 @author 	      Jonathan Haas / Markus Schappacher 
 @param 	         void
 @return 	      int32_t Anzahl der ausgeführten Schritte
*/
int32_t s32RunsMotorStop(void)
{
   // Calc new target to deceleration
   stepMotor.stop();

   // Return
   int32_t steps = stepMotor.distanceToGo();

   // run deceleration steps
   while (stepMotor.isRunning())
   {
      stepMotor.run();
   }

   return steps;
}

/*!
 @fn              void vRunsMoveToWl(uint16_t u16wl)
 @brief           Moves grating and filter for wavelength (u16wl)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vRunsMoveToWl(uint16_t u16wl, uint8_t monochromatorType)
{
   vRunsMoveGratingToWl(u16wl, monochromatorType);
   vRunsMoveFilterToWl(u16wl, monochromatorType);
}

/*!
 @fn              void vRunsMoveToWl(uint16_t u16wl)
 @brief           Öffnet den Slit auf die übergebene Breite 0.5 <= Breite <= 4
 @author 	      Jonathan Haas
 @param 	         uint16_t u8slitAxis -> Slit Achse
@param 	         float u8slitAxis -> Slit-Breite
 @return 	      void
*/
void vRunsMoveToSlitPos(uint8_t u8slitAxis, float fSlitWidth)
{
   // Lade Settings anhand Axis-Type
   vLoadSettings(u8slitAxis);
   // Konfiguriere Motor-Hardware
   vInitializeMotor();
   // Lade die samples anhand des Achsen-Typs
   vSetExampleRuns(sMotorSettings.u8axisType);

   float pos = -13.085*(fSlitWidth*fSlitWidth)+(283.04*fSlitWidth)+271.79;
    
   vMotorPowerEnable();
   vRunsInitRun(sMotorSettings.u32axisZeropoint);
   sMotorSettings.u8isInit = 1;
   vRunsMoveTo(pos);
   vMotorPowerDisable();
}

/*!
 @fn              void vRunsMoveGratingToWl(uint16_t u16wl)
 @brief           Moves only grating for wavelength (u16wl)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vRunsMoveGratingToWl(uint16_t u16wl, uint8_t monochromatorType)
{
   // Lade den Gratingachsentype anhand des Monochromatortypen
   uint8_t axisType = u8GetGratingAxis(monochromatorType);
   // Lade Settings anhand Axis-Type (param)
   vLoadSettings(axisType);
   // Konfiguriere Motor-Hardware
   vInitializeMotor();
   // Lade die samples anhand des Achsen-Typs
   vSetExampleRuns(sMotorSettings.u8axisType);
   vMotorPowerEnable();

   if (sMotorSettings.u8isInit == 0)
   {
      vRunsInitRun(0);
      sMotorSettings.u8isInit = 1;
   }

   // Run specific filter movements according Monochromatortype
   switch (monochromatorType)
   {
   case MON_TYPE_H1034:
      vGratingmoveH1034(u16wl);
      break;
   case MON_TYPE_MDM5:
      vGratingmoveMDM5(u16wl);
      break;
   case MON_TYPE_SF2:
      vGratingmoveSF2(u16wl);
      break;
   case MON_TYPE_H1511:
      vGratingmoveH1511(u16wl);
      break;
   case MON_TYPE_H1512:
      vGratingmoveH1512(u16wl);
      break;
   case MON_TYPE_H4EX_FIX:
      vGratingmoveH4EXfix(u16wl);
      break;
   default:
      break;
   }
  vMotorPowerDisable();
}

/*!
 @fn              void vRunsMoveFilterToWl(uint16_t u16wl)
 @brief           Moves only filter for wavelength (u16wl)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vRunsMoveFilterToWl(uint16_t u16wl, uint8_t monochromatorType)
{
   // Lade den Gratingachsentype anhand des Monochromatortypen
   uint8_t axisType = u8GetFilterAxis(monochromatorType);
   // Lade Settings anhand Axis-Type (param)
   vLoadSettings(axisType);
   // Konfiguriere Motor-Hardware
   vInitializeMotor();
   // Lade die samples anhand des Achsen-Typs
   vSetExampleRuns(sMotorSettings.u8axisType);
   vMotorPowerEnable();
   if (sMotorSettings.u8isInit == 0)
   {
      vRunsInitRun(0);
      sMotorSettings.u8isInit = 1;
   }
   switch (monochromatorType)
   {
   case MON_TYPE_H1034:
      vFiltermoveH1034(u16wl);
      break;
   case MON_TYPE_MDM5:
      vFiltermoveMDM5(u16wl);
      break;
   case MON_TYPE_SF2:
      vFiltermoveSF2(u16wl);
      break;
   default:
      break;
   }
   vMotorPowerDisable();
}

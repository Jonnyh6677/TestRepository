#include "menucallbacks.h"

//********************************************************************
//
//                    Menu callback functions
//
// *******************************************************************

/*!
 @fn              mFunc_clearEeprom(uint8_t param)
 @brief           Sets the whole EEPROM to '255'
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_clearEeprom(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {

      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.print("[Enter] Clr. EEPROM");

      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {

      if (LCDML.BT_checkEnter())
      {
         // Lösche EEPROM
         vClearEeprom();

         // Lade sämtliche Settings für 'AXIS_TYPE_DEFAULT'
         vSetDefaultSettings(AXIS_TYPE_DEFAULT);
         vSetExampleRuns(AXIS_TYPE_DEFAULT);
         vInitializeMotor();

         lcd.clear();
         lcd.setPosition(0, 0);
         lcd.printf("EEPROM cleared!");
         delay(LCD_SHOW_DELAY);
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              void mFunc_startMoveSteps(uint8_t param)
 @brief           Moves a specific motor (param) the choosen steps
 @author 	      Jonathan Haas
 @param 	         uint8_t param (0, unbedeutend)
 @return 	      void
*/
void mFunc_startMoveStepsInit(uint8_t param)
{
   static int32_t s32steps;
   if (LCDML.FUNC_setup())
   {
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32steps);
      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.print(" : Steps");
      lcd.setPosition(0, 2);
      lcd.printf("Cur Pos: %d", stepMotor.currentPosition());
      lcd.setPosition(0, 3);
      lcd.print("[OK]    : Start");
      LCDML.FUNC_setLoopInterval(100);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }
      if (LCDML.BT_checkEnter())
      {
         vMotorPowerEnable();
         sMotorSettings.u8isInit = 0; // Init erzwingen

         if (sMotorSettings.u8isInit == 0)
         {
            vRunsInitRun(sMotorSettings.u32axisZeropoint);
            sMotorSettings.u8isInit = 1;
         }
         vPrintStatus();
         // vRunsSlitPos();
         vRunsMoveTo(s32steps);
         delay(100);
         vMotorPowerStandby(); // param zeigt auf Nummer des Sample-Runs, nicht auf Achse
         // Print status infos on display
         vPrintStatus(); //## 0 statt param wegen falscher Speed + Accel werte

         // LCD print
         lcd.clear();
         digitControl.Print();
         lcd.setPosition(7, 0);
         lcd.printf(" : Steps", s32steps);
         lcd.setPosition(0, 2);
         lcd.printf("Cur Pos: %d", stepMotor.currentPosition());
         lcd.setPosition(0, 3);
         lcd.print("[OK]    : Start");
      }
   }
}

/*!
 @fn              mFunc_startSlitsRun(uint8_t param)
 @brief           Runs an new Slit setting
 @author 	      M.Schappacher
 @param 	         uint8_t param -> 2..6, welche vorbelegte Slitweite soll benutzt werden 
 @return 	      void
*/
void mFunc_startSlitsRun(uint8_t sampleRun)
{
   if (LCDML.FUNC_setup())
   {
      vProcessSlitsRun(sampleRun, 1);
      vProcessSlitsRun(sampleRun, 2);
      vProcessSlitsRun(sampleRun, 3);
      delay(500);
   }
   LCDML.FUNC_goBackToMenu();
}

/*!
 @fn              mFunc_startSlitsRun(uint8_t param)
 @brief           Positioniert ein Slit (axis) entsprechend der Eingabe (0.5 mm Schritte)
 @author 	      J.Haas
 @param 	         uint8_t axis -> 2..6, entsprechende Slit Achse
 @return 	      void
*/
void mFunc_startSlitStepRun(uint8_t axis)
{
static float fValue;

   if (LCDML.FUNC_setup())
   {
      fValue = 0.5;

      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.printf("%.1f    : Slit Width",fValue);
      lcd.setPosition(0, 2);
      lcd.print("[OK]   : Start");
      lcd.setPosition(0, 3);
      lcd.print("[BLACK]: Back");
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         if(fValue < 4)
         {
            fValue = fValue + 0.5;
            lcd.setPosition(0, 0);
            lcd.printf("%.1f    : Slit Width",fValue);
         }
      }
      if (LCDML.BT_checkDown())
      {
         if(fValue > 0.5)
         {
            fValue = fValue - 0.5;
            lcd.setPosition(0, 0);
            lcd.printf("%.1f    : Slit Width",fValue);
         }
      }
      if (LCDML.BT_checkEnter())
      {
         vRunsMoveToSlitPos(axis, fValue);
      }
   }
}

/*!
 @fn              mFunc_startWLRun(uint8_t param)
 @brief           Runs an new Wavelength setting
 @author 	      M.Schappacher
 @param 	         uint8_t param -> 
 @return 	      void
*/
void mFunc_startWLRun(uint8_t mochromatorType)
{
 static int32_t s32value;

   if (LCDML.FUNC_setup())
   {
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32value);

      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.printf(" : WL",s32value);
      lcd.setPosition(0, 2);
      lcd.print("[OK]    : Start");
      lcd.setPosition(0, 3);
      lcd.print("[BLACK] : Back");
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }
      if (LCDML.BT_checkEnter())
      {
         vRunsMoveToWl((uint16_t)s32value, mochromatorType);
         lcd.clear();
         digitControl.Print();
         lcd.setPosition(7, 0);
         lcd.printf(" : WL",s32value);
         lcd.setPosition(0, 2);
         lcd.print("[OK]    : Start");
         lcd.setPosition(0, 3);
         lcd.print("[BLACK] : Back");
      }
   }
}


/*!
 @fn              void mFunc_back(uint8_t param)
 @brief           navigate one layer back in menu
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_back(uint8_t param)
// *********************************************************************
{
   if (LCDML.FUNC_setup()) // ****** SETUP *********
   {
      // end function and go an layer back
      LCDML.FUNC_goBackToMenu(1); // leave this function and go a layer back
   }
}

/*!
 @fn              void mFunc_startInitRun(uint8_t param)
 @brief           runs initrun and set zero point on lichtschranke
                  zu "sMotorSettings.u32initPosition"
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_startInitRun(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // Turn motor power on
      vMotorPowerEnable();
      // start init run and set zero point to parameter
      vRunsInitRun(sMotorSettings.u32axisZeropoint);
      vPrintStatus();

      LCDML.FUNC_setLoopInterval(200);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkQuit())
      {
         // Run set close flag
         LCDML.FUNC_goBackToMenu();
      }
   }

   if (LCDML.FUNC_close())
   {
      // Turn motor power off
      vMotorPowerStandby();
   }
}

/*!
 @fn                 mFunc_startOffsetRun(uint8_t param)
 @brief              Starts the offset run
 @author 	         Jonathan Haas
 @param 	            uint8_t param
 @return 	         void
*/
void mFunc_startOffsetRun(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // Turn motor power on
      vMotorPowerEnable();
      vRunsStartOffsetRun();
      LCDML.FUNC_setLoopInterval(200);
      LCDML.FUNC_goBackToMenu();
   }

   if (LCDML.FUNC_close())
   {
      // Turn motor power off
      vMotorPowerStandby();
   }
}

/*!
 @fn              void mFunc_startSerialMode(uint8_t param)
 @brief           runs the serial mode
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_startSerialMode(uint8_t param)
{
   if (LCDML.FUNC_setup()) // ****** SETUP *********
   {
      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.print("Serieller Modus");

      lcd.setPosition(0, 1);
      lcd.print("[e] = exit");

      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop()) // ****** LOOP *********
   {
      // start serial mode
      vRunsSerialMode();

      // end function and go an layer back and print menu
      LCDML.FUNC_goBackToMenu();
   }

   if (LCDML.FUNC_close()) // ****** STABLE END *********
   {
   }
}

/*!
 @fn              mFunc_enableMotor(uint8_t param)
 @brief           turns motor power on
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_enableMotor(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      LCDML.FUNC_setLoopInterval(10);
      vMotorPowerEnable();
   }

   if (LCDML.FUNC_loop())
   {
      // Run set close flag
      LCDML.FUNC_goBackToMenu();
   }

   if (LCDML.FUNC_close())
   {
   }
}

/*!
 @fn              void mFunc_disableMotor(uint8_t param)
 @brief           turns motor power off
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_disableMotor(uint8_t param)
{

   if (LCDML.FUNC_setup())
   {
      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {
      // turn motor power ff
      vMotorPowerDisable();

      // Run set close flag
      LCDML.FUNC_goBackToMenu();
   }

   if (LCDML.FUNC_close())
   {
      // end function and go an layer back and print menu
      LCDML.FUNC_goBackToMenu();
   }
}

/*!
 @fn              void mFunc_setSpeed(uint8_t param)
 @brief           increment / decrement motor speed according user input ("Up" / "Down")
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_setSpeed(uint8_t param)
{
   static int32_t s32value;

   if (LCDML.FUNC_setup())
   {
      s32value = sMotorSettings.u32motorSpeedMax;
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32value);
      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.print(" : Steps/Sec");
      lcd.setPosition(0, 2);
      lcd.print("[OK]    : Apply");
      lcd.setPosition(0, 3);
      lcd.print("[BLACK] : Back");
      LCDML.FUNC_setLoopInterval(100);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }
      if (LCDML.BT_checkEnter())
      {
         // Save new speed value in settings
         sMotorSettings.u32motorSpeedMax = s32value;
         // calc max speed according AD converter
         stepMotor.setMaxSpeed(sMotorSettings.u32motorSpeedMax);
         stepMotor.setAcceleration(sMotorSettings.u32motorAcceleration);
         // end function and go an layer back and print menu
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              mFunc_setAxisRange(uint8_t param)
 @brief           Sets the axis range
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_setAxisRange(uint8_t param)
{
   static int32_t s32value;
   if (LCDML.FUNC_setup())
   {
      s32value = sMotorSettings.u32axisRange;
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32value);
      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.printf(" : Range");
      lcd.setPosition(0, 2);
      lcd.print("[OK]    : Apply");
      lcd.setPosition(0, 3);
      lcd.print("[BLACK] : Back");
      LCDML.FUNC_setLoopInterval(100);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }

      if (LCDML.BT_checkEnter())
      {
         // Save new range value in settings
         sMotorSettings.u32axisRange = s32value;
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              void mFunc_setAcceleration(uint8_t param)
 @brief           increment / decrement motor acceleration according user input ("Up" / "Down")
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_setAcceleration(uint8_t param)
{
   static int32_t s32value;
   if (LCDML.FUNC_setup())
   {
      s32value = sMotorSettings.u32motorAcceleration;
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32value);
      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.printf(" : Steps/Sec");
      lcd.setPosition(0, 2);
      lcd.print("[OK]    : Apply");
      lcd.setPosition(0, 3);
      lcd.print("[BLACK] : Back");
      LCDML.FUNC_setLoopInterval(100);
   }
   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }
      if (LCDML.BT_checkEnter())
      {
         // Save new speed value in settings
         sMotorSettings.u32motorAcceleration = s32value;
         // calc max speed according AD converter
         stepMotor.setAcceleration(sMotorSettings.u32motorAcceleration);
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              void mFunc_setVref(uint8_t param)
 @brief           Set the Vref with DAC
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_setVref(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.print("[Up]   := +");
      lcd.setPosition(0, 1);
      lcd.print("[Down] := -");
      lcd.setPosition(0, 2);
      lcd.print("[Left] := Back");
      lcd.setPosition(0, 3);
      lcd.printf("I: %1.3f A", (((sMotorSettings.u8vref / 255.0) * 3.3) / 5.8 + 0.04));

      LCDML.FUNC_setLoopInterval(1);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         // Increment vref dac value
         if (sMotorSettings.u8vref < 255 - 10)
         {
            sMotorSettings.u8vref += 10;
         }
         else
         {
            sMotorSettings.u8vref = 250;
         }
         // write dac value
         analogWrite(PIN_VREF, sMotorSettings.u8vref);
         lcd.setPosition(0, 3);
         lcd.printf("I: %1.3f A", (((sMotorSettings.u8vref / 255.0) * 3.3) / 5.8 + 0.04));
         // lcd.printf("I: %f", ((sMotorSettings.u8vref/255.0)*3.3) / 3.8);
      }

      if (LCDML.BT_checkDown())
      {
         // Decrement vref dac value
         if (sMotorSettings.u8vref > 0 + 10)
         {
            sMotorSettings.u8vref -= 10;
         }
         else
         {
            sMotorSettings.u8vref = 0;
         }
         // write dac value
         analogWrite(PIN_VREF, sMotorSettings.u8vref);
         lcd.setPosition(0, 3);
         lcd.printf("I: %1.3f A", (((sMotorSettings.u8vref / 255.0) * 3.3) / 5.8 + 0.04));
         // lcd.printf("I: %f", ((sMotorSettings.u8vref/255.0)*3.3) / 3.8);
      }

      // Go one layer back
      if (LCDML.BT_checkLeft())
      {
         // Run set close flag
         LCDML.FUNC_goBackToMenu();
      }
   }

   if (LCDML.FUNC_close())
   {
      // end function and go an layer back and print menu
      LCDML.FUNC_goBackToMenu();
   }
}

/*!
 @fn              void mFunc_printStatus(uint8_t param)
 @brief           prints motor status and settings
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_printStatus(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // LCD print
      vPrintStatus();
      LCDML.FUNC_setLoopInterval(200);
   }

   if (LCDML.FUNC_loop())
   {
   }
}

/*!
 @fn              mFunc_initSettings
 @brief           init monochromator specific settings
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_initSettings(uint8_t axisType)
{

   if (LCDML.FUNC_setup())
   {
      // Lade Settings anhand Axis-Type (param)
      vLoadSettings(axisType);
      // Konfiguriere Motor-Hardware
      vInitializeMotor();
      // Lade die samples anhand des Achsen-Typs
      vSetExampleRuns(sMotorSettings.u8axisType);

      LCDML.FUNC_setLoopInterval(100);
   }

   if (LCDML.FUNC_loop())
   {
      LCDML.FUNC_goBackToMenu();
   }
}

/*!
 @fn              mFunc_saveSettingsToEeprom
 @brief           Writes settings to eeprom
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_saveSettingsToEeprom(uint8_t param)
{

   if (LCDML.FUNC_setup())
   {
      //vSettingsInit(param);
      LCDML.FUNC_setLoopInterval(100);
     
      // Write last used axis in eeprom
      vWriteLastAxisType(sMotorSettings.u8axisType);

      // Write a flag that axis settings were saved
      vWriteAxisFlag(sMotorSettings.u8axisType);

      // Write now settings in eeprom
      vWriteSettingsToEeprom(sMotorSettings.u8axisType);

      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.printf("Settings saved...");
      timeElapsed = 0;
   }

   if (LCDML.FUNC_loop())
   {
      if (timeElapsed > LOAD_SAVE_DELAY)
      {
         LCDML.FUNC_goBackToMenu();
      }
   }

   if (LCDML.FUNC_close())
   {
   }
}

/*!
 @fn              mFunc_startExampleRun(uint8_t param)
 @brief           Runs an sample run
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_startExampleRun(uint8_t sampleRun)
{
   if (LCDML.FUNC_setup())
   {
      // enable motor power
      vMotorPowerEnable();
      // start specific example run
      vRunsExampleRun(sampleRun);
      // disable motor power
      //## vMotorPowerDisable();
      vMotorPowerStandby(); // param zeigt auf Nummer des Sample-Runs, nicht auf Achse
      // Print status infos on display
      vPrintStatus(); //## 0 statt param wegen falscher Speed + Accel werte
      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkLeft())
      {
         // Go one layer back in menu
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              void mFunc_startMoveSteps(uint8_t param)
 @brief           Moves a specific motor (param) the choosen steps
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_startMoveSteps(uint8_t param)
{
   static int32_t s32steps;
   if (LCDML.FUNC_setup())
   {
      // Initialize DigitControl and print it
      digitControl = DigitControl(&s32steps);
      // LCD print
      lcd.clear();
      digitControl.Print();
      lcd.setPosition(7, 0);
      lcd.printf(" : Steps", s32steps);
      lcd.setPosition(0, 2);
      lcd.printf("Cur Pos: %d", stepMotor.currentPosition());
      lcd.setPosition(0, 3);
      lcd.print("[OK]    : Start");
      LCDML.FUNC_setLoopInterval(100);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         digitControl.IncrementValue();
      }
      if (LCDML.BT_checkDown())
      {
         digitControl.DecrementValue();
      }
      if (LCDML.BT_checkRight())
      {
         digitControl.MoveDecimalPosRight();
      }
      if (LCDML.BT_checkLeft())
      {
         digitControl.MoveDecimalPosLeft();
      }
      if (LCDML.BT_checkEnter())
      {
         // Run specific filter movements according Monochromatortype
         vMotorPowerEnable();
         //vRunsInitRun(sMotorSettings.u32axisZeropoint,param);
         vRunsMoveTo(s32steps);
         //## vMotorPowerDisable();
         vMotorPowerStandby();
         // LCD print
         lcd.clear();
         digitControl.Print();
         lcd.setPosition(7, 0);
         lcd.printf(" : Steps", s32steps);
         lcd.setPosition(0, 2);
         lcd.printf("Cur Pos: %d", stepMotor.currentPosition());
         lcd.setPosition(0, 3);
         lcd.print("[OK]    : Start");
      }
   }
}

/*!
 @fn              mFunc_startStepCheck(uint8_t param)
 @brief           Start special run to check if motor loses steps
 @author 	      Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_startStepCheck(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // enable motor power
      vMotorPowerEnable();
      // start Run
      vRunsStepLoseCheck();
      // disable motor power
      //## vMotorPowerDisable();
      vMotorPowerStandby();
      LCDML.FUNC_setLoopInterval(10);
   }
}

/*!
 @fn              mFunc_startLongTimeRun(uint8_t param)
 @brief           Start long time run to check robustness
 @author 	        M. Schappacher
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_startLongTimeRun(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      // enable motor power
      vMotorPowerEnable();
      timeElapsed = 2000; //schneller Start durchBeginn mit 2s
      vPrintStatus();
      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {
      if (timeElapsed > 3000) // Wartezeit 3 sec
      {
         sMotorSettings.u32loop++;
         // start Run
         vMotorPowerEnable();
         vRunsExampleRun(0);
         // disable motor power
         //## vMotorPowerDisable();
         vMotorPowerStandby();
         timeElapsed = 0;
      }
   }
   if (LCDML.FUNC_close())
   {
   }
}

/*!
 @fn              void mFunc_setDefaultSettings(uint8_t param)
 @brief           Loads the default settings fpr specific axis
 @author 	      Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_setDefaultSettings(uint8_t param)
{
   if (LCDML.FUNC_setup())
   {
      vSetDefaultSettings(sMotorSettings.u8axisType);
      vInitializeMotor();
      LCDML.FUNC_setLoopInterval(100);
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.printf("Settings loaded...");
      timeElapsed = 0;
   }

   if (LCDML.FUNC_loop())
   {
      if (timeElapsed > LOAD_SAVE_DELAY)
      {
         LCDML.FUNC_goBackToMenu();
      }
   }

   if (LCDML.FUNC_close())
   {
   }
}

/*!
 @fn              void mFunc_SetAxisName(uint8_t line)
 @brief           Changes the name of the menu entry
 @author 	      Jonathan Haas
 @param 	          uint8_t line
 @return 	        void
*/
void mFunc_showAxisName(uint8_t line)
// *********************************************************************
{
   char buf[20];

   sprintf(buf, ">%s", sMotorSettings.acAxisName);
   // use the line from function parameters
   lcd.setPosition(1, line);
   lcd.print(buf);
}

/*!
 @fn              mFunc_startMoveToSpecialPos(uint8_t pos)
 @brief           Moves to special Pos
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_startMoveToSpecialPos(uint8_t pos)
{
   if (LCDML.FUNC_setup())
   {
      // enable motor power
      vMotorPowerEnable();
      // start specific example run
      vRunsMoveToSpecialPos(pos);
      // disable motor power
      //## vMotorPowerDisable();
      vMotorPowerStandby(); // param zeigt auf Nummer des Sample-Runs, nicht auf Achse
      LCDML.FUNC_setLoopInterval(10);
      vPrintStatus();
   }
}

/*!
 @fn              mFunc_setRotationDir(uint8_t param)
 @brief           Moves to special Pos
 @author 	        Jonathan Haas
 @param 	        uint8_t param
 @return 	        void
*/
void mFunc_setRotationDir(uint8_t param)
{
   static uint8_t u8rotationDir;
   if (LCDML.FUNC_setup())
   {

      u8rotationDir = sMotorSettings.u8dir;
      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.print("[Up]    := 1");
      lcd.setPosition(0, 1);
      lcd.print("[Down]  := 0");
      lcd.setPosition(0, 2);
      lcd.print("[Left]  := Back");
      lcd.setPosition(0, 3);
      lcd.printf("Rotation:= %d", u8rotationDir);

      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         u8rotationDir = 1;
         lcd.setPosition(0, 3);
         lcd.printf("Rotation:= %d", u8rotationDir);
      }

      if (LCDML.BT_checkDown())
      {
         u8rotationDir = 0;
         lcd.setPosition(0, 3);
         lcd.printf("Rotation:= %d", u8rotationDir);
      }
      if (LCDML.BT_checkEnter())
      {
         sMotorSettings.u8dir = u8rotationDir;
         lcd.printf("Rotation:= %d", sMotorSettings.u8dir);
         vSetMotorDirection();
         LCDML.FUNC_goBackToMenu();
      }
   }
}

/*!
 @fn              mFunc_setSensorPolarity(uint8_t param)
 @brief           Adapts to different sensors for initialization
 @author 	      Markus Schappacher / Jonathan Haas
 @param 	         uint8_t param
 @return 	      void
*/
void mFunc_setSensorPolarity(uint8_t param)
{
   static uint8_t u8sensorPolarity;
   if (LCDML.FUNC_setup())
   {

      u8sensorPolarity = sMotorSettings.u8LsActive;
      // LCD print
      lcd.clear();
      lcd.setPosition(0, 0);
      lcd.print("[Up]    := 1");
      lcd.setPosition(0, 1);
      lcd.print("[Down]  := 0");
      lcd.setPosition(0, 2);
      lcd.print("[Left]  := Back");
      lcd.setPosition(0, 3);
      lcd.printf("Polarity:= %d", u8sensorPolarity);

      LCDML.FUNC_setLoopInterval(10);
   }

   if (LCDML.FUNC_loop())
   {
      if (LCDML.BT_checkUp())
      {
         u8sensorPolarity = 1;
         lcd.setPosition(0, 3);
         lcd.printf("Polarity:= %d", u8sensorPolarity);
      }

      if (LCDML.BT_checkDown())
      {
         u8sensorPolarity = 0;
         lcd.setPosition(0, 3);
         lcd.printf("Polarity:= %d", u8sensorPolarity);
      }
      if (LCDML.BT_checkEnter())
      {
         sMotorSettings.u8LsActive = u8sensorPolarity;
         lcd.printf("Polarity:= %d", sMotorSettings.u8LsActive);
         vSetSensorPolarity();
         LCDML.FUNC_goBackToMenu();
      }
   }
}

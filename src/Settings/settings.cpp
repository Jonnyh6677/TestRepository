#include "settings.h"


/*!
 @fn              vInitializeSettings(void)
 @brief           Diese Funktion wird in der setup() Funktion des Arduino-Frameworks ausgeführt. (Initialisierung des Teensys)
                  Hier wird überprüft ob bereits eine Achse im EEPROM hinterlegt wurde.
                  Falls ja werden die entsprechenden Settings aus dem EEPROM geladen und in die globale Struktur "sMotorSettings_t sMotorSettings" geschrieben. Andernfalls werden Default-Settings gesetzt.
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vInitializeSettings(void)
{ 
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Settings loaded!");
   lcd.setPosition(0, 1);

   // Lese zuerst das flag ob bereits eine letzte Achse hinterlegt ist
   int8_t s8LastAxisType = u8ReadLastAxisType();

   // Adresse LAST_AXIS_ADDR (zuletzt benutzte Achse) ist default mit NO_LAST_AXIS_AVAILABLE (-1) hinterlegt (Keine Achse hinterlegt := NO_LAST_AXIS_AVAILABLE)
   if (s8LastAxisType != NO_LAST_AXIS_AVAILABLE)
   {
      // Read now settings from eeprom
      vReadSettingsFromEeprom(s8LastAxisType);
      // lcd.printf("[EEPROM]");
   }
   else
   {
      // Setze Default-Werte
      vSetDefaultSettings(AXIS_TYPE_DEFAULT);
      // lcd.printf("[DEFAULT]");
   }
   sMotorSettings.u8isInit = 0;
   timeElapsed = 0;
   while (timeElapsed < LOAD_SAVE_DELAY)
      ;
}

/*!
 @fn              vLoadSettings(uint8_t axisType)
 @brief           Lädt die Settings entsprechd des Achsen-Typs (axisType) aus dem EEPROM und schreibt diese in die globale Struktur "sMotorSettings_t aSettings".
                  Wurde im EEPROM für diesen Achsen-Typ noch keine Settings abgelegt, werden Dafault-Werte gesetzt.
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vLoadSettings(uint8_t u8axisType)
{
   lcd.clear();
   lcd.setPosition(0, 0);
   lcd.printf("Settings loaded!");
   lcd.setPosition(0, 1);

   // Read flag if axis settings already saved
   int8_t u8SavedFlag = u8ReadAxisFlag(u8axisType);

   // Für diesen Achsen-Typ ist bereits etwas im Eeprom hinterlegt
   if (u8SavedFlag == AXIS_SAVED)
   {
      // Read now settings from eeprom
      vReadSettingsFromEeprom(u8axisType);
      // lcd.printf("[EEPROM]");
   }
   else
   {
      // Setze Default-Werte anhand des Achsen-Typs wenn noch nichts für diese Achsen-Typ im EEPROM abgelegt ist
      vSetDefaultSettings(u8axisType);
      // lcd.printf("[DEFAULT]");
   }
   timeElapsed = 0;
   while (timeElapsed < LOAD_SAVE_DELAY)
      ;
}

/*!
 @fn              vSetExampleRuns(uint8_t u8axisType)
 @brief           Schreibt Positionen für diverse "Sample Runs" für den entsprechenden
                  Achsen-Typ in den globalen Array 'sSampleRuns'.

                  Achtung ## Wenn die Fahrbewegungsbeispiele erweitert werden, dann müssen in der Headerdatei unbedingt die
                  nötige Anzahl der Felder erhöht werden (samplerun[hier])
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vSetExampleRuns(uint8_t u8axisType)
{
   switch (u8axisType)
   {
   case AXIS_TYPE_421_TRANSPORT_X:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      break;

   case AXIS_TYPE_421_TRANSPORT_Y:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      break;

   case AXIS_TYPE_430_TRANSPORT_X:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{(uint32_t)-150}, 1}; // Plate Out normal
      sSampleRuns[3] = {{2886}, 1}; // Plate Out right
      sSampleRuns[4] = {{3250}, 1}; // Detect Plate Pos
      sSampleRuns[5] = {{3420}, 1}; // 100% ABS Value Pos
      break;

   case AXIS_TYPE_430_TRANSPORT_Y:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{4430}, 1}; // Plate Out normal + right
      sSampleRuns[3] = {{640}, 1};  // Detect Plate Pos
      sSampleRuns[4] = {{700}, 1};  // 100% ABS Value Pos
      break;

   case AXIS_TYPE_430_TOP_BOTTOM:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange * 3 / 4,
                         sMotorSettings.u32axisRange / 2,
                         sMotorSettings.u32axisRange * 9 / 10, 0},
                        4};
      sSampleRuns[1] = {{sMotorSettings.u32axisRange * 5 / 10,
                         sMotorSettings.u32axisRange * 8 / 10,
                         sMotorSettings.u32axisRange * 3 / 10,
                         sMotorSettings.u32axisRange * 9 / 10, 0},
                        5};
      sSampleRuns[2] = {{0}, 1};    // (-110) offener Lichtweg
      sSampleRuns[3] = {{1378}, 1}; // (1500) Linse in Lichtweg
      sSampleRuns[4] = {{2834}, 1}; // (2900) 45° Spiegel in Lichtweg
      break;

   case AXIS_TYPE_430_TOP_OPTIC_Z:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4, 0},
                        5};
      break;

   case AXIS_TYPE_430_BOT_OPTIC_Z:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      break;

   case AXIS_TYPE_430_EX_SOURCE:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{(uint32_t)-150}, 1}; // Blitzlampe
      sSampleRuns[3] = {{590}, 1};  // IR Blocker
      sSampleRuns[4] = {{1693}, 1}; // AS Laser
      sSampleRuns[5] = {{2795}, 1}; // LED Quelle
      break;

   case AXIS_TYPE_430_PMT_AXIS:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{33}, 1};   // Extended IR PMT
      sSampleRuns[3] = {{1220}, 1}; // LUM PMT
      break;

   case AXIS_TYPE_421_MPC_Z:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0,
                         7 * sMotorSettings.u32axisRange / 10,
                         8 * sMotorSettings.u32axisRange / 10,
                         2 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10, 0},
                        10};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4, 0},
                        5};
      break;

   case AXIS_TYPE_421_MPC_Z_2:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0,
                         7 * sMotorSettings.u32axisRange / 10,
                         8 * sMotorSettings.u32axisRange / 10,
                         2 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10, 0},
                        10};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4, 0},
                        5};
      break;

   case AXIS_TYPE_421_MPC_Z_3:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         7 * sMotorSettings.u32axisRange / 10,
                         0,
                         5 * sMotorSettings.u32axisRange / 10},
                        4};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2},
                        5};
      break;

   case AXIS_TYPE_421_MPC_Z_4:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         7 * sMotorSettings.u32axisRange / 10,
                         0,
                         5 * sMotorSettings.u32axisRange / 10},
                        4};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2,
                         0,
                         2 * sMotorSettings.u32axisRange / 4,
                         1 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2},
                        12};
      break;

   case AXIS_TYPE_421_LENS_CHANGE:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0,
                         7 * sMotorSettings.u32axisRange / 10,
                         8 * sMotorSettings.u32axisRange / 10,
                         2 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10, 0},
                        10};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4, 0},
                        5};
      sSampleRuns[2] = {{-200}, 1};  // Linse FI
      sSampleRuns[3] = {{1375}, 1};  // Linse LUM 
      sSampleRuns[4] = {{2950}, 1};  // Bottom Messung
      sSampleRuns[5] = {{0}, 1};     // INIT
      break;

   case AXIS_TYPE_472_TRANSPORT_X:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{(uint32_t)-150}, 1}; // Plate Out normal
      sSampleRuns[3] = {{2886}, 1}; // Plate Out right
      sSampleRuns[4] = {{(uint32_t)-190}, 1}; // Detect Plate Pos
      sSampleRuns[5] = {{3420}, 1}; // 100% ABS Value Pos
      break;

   case AXIS_TYPE_472_TRANSPORT_Y:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{4430}, 1}; // Plate Out normal + right
      sSampleRuns[3] = {{(uint32_t)-150}, 1}; // Detect Plate Pos
      sSampleRuns[4] = {{700}, 1};  // 100% ABS Value Pos
      break;

   case AXIS_TYPE_472_OPTIC_MODUL:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{3150}, 1}; // Optik Modul 1
      sSampleRuns[3] = {{2470}, 1}; // Optik Modul 2
      sSampleRuns[4] = {{1790}, 1}; // Optik Modul 3
      sSampleRuns[5] = {{1110}, 1}; // Optik Modul 4
      sSampleRuns[6] = {{430}, 1};  // Optik Modul 5
      sSampleRuns[7] = {{(uint32_t)-250}, 1}; // Optik Modul 6
      break;

   case AXIS_TYPE_472_PMT_AXIS:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{420}, 1};  // FLUO PMT
      sSampleRuns[3] = {{1320}, 1}; // HTRF PMT
      break;

   case AXIS_TYPE_472_EX_SOURCE:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0},
                        5};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         10 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10,
                         6 * sMotorSettings.u32axisRange / 10,
                         5 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10,
                         3 * sMotorSettings.u32axisRange / 10,
                         4 * sMotorSettings.u32axisRange / 10, 0},
                        13};
      sSampleRuns[2] = {{35}, 1};   // Blitzlampe
      sSampleRuns[3] = {{822}, 1};  // HTRF Laser
      sSampleRuns[4] = {{1688}, 1}; // AS Laser / Spectrometer
      break;

   case AXIS_TYPE_472_INJ_X:
   case AXIS_TYPE_472_TOP_OPTIC_Z:
   case AXIS_TYPE_471_TOP_OPTIC_Z:
   case AXIS_TYPE_472_TOP_BOTTOM:
   case AXIS_TYPE_472_BOT_OPTIC_Z:

      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         sMotorSettings.u32axisRange / 2, 0,
                         sMotorSettings.u32axisRange, 0,
                         7 * sMotorSettings.u32axisRange / 10,
                         8 * sMotorSettings.u32axisRange / 10,
                         2 * sMotorSettings.u32axisRange / 10,
                         7 * sMotorSettings.u32axisRange / 10, 0},
                        10};
      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4, 0},
                        5};
      break;

   case AXIS_TYPE_472_INJ_Z:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         7 * sMotorSettings.u32axisRange / 10,
                         0,
                         5 * sMotorSettings.u32axisRange / 10},
                        4};

      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2},
                        5};
      break;

   case AXIS_TYPE_SF2_EX_SLIT_IN:
      sSampleRuns[2] = {{1201},  1};    //  4 mm
      sSampleRuns[3] = {{991},   1};    //  3 mm
      sSampleRuns[4] = {{781},   1};    //  2 mm 
      sSampleRuns[5] = {{571},   1};    //  1 mm  
      sSampleRuns[6] = {{391},   1};    //0.5 mm
      break;

   case AXIS_TYPE_SF2_EX_SLIT_MID:
      sSampleRuns[2] = {{1202},  1};    //  4 mm
      sSampleRuns[3] = {{992},   1};    //  3 mm
      sSampleRuns[4] = {{782},   1};    //  2 mm 
      sSampleRuns[5] = {{572},   1};    //  1 mm  
      sSampleRuns[6] = {{392},   1};    //0.5 mm
      break;

   case AXIS_TYPE_SF2_EX_SLIT_OUT:
      sSampleRuns[2] = {{1203},  1};    //  4 mm
      sSampleRuns[3] = {{993},   1};    //  3 mm
      sSampleRuns[4] = {{783},   1};    //  2 mm 
      sSampleRuns[5] = {{573},   1};    //  1 mm  
      sSampleRuns[6] = {{393},   1};    //0.5 mm
      break;
   
   case AXIS_Type_SF2_Grating:
      sSampleRuns[2] = {{4000},  1};    //  
      break;
   
   case AXIS_Type_SF2_OrderSort:
      sSampleRuns[0] = {{2000},  1};    //  
      sSampleRuns[1] = {{4150},  1};    //  
      sSampleRuns[2] = {{6300},  1};    //  
      break;

   case AXIS_TYPE_USER:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         7 * sMotorSettings.u32axisRange / 10,
                         0,
                         5 * sMotorSettings.u32axisRange / 10},
                        4};

      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2},
                        5};
      break;

   default:
      sSampleRuns[0] = {{sMotorSettings.u32axisRange,
                         7 * sMotorSettings.u32axisRange / 10,
                         0,
                         5 * sMotorSettings.u32axisRange / 10},
                        4};

      sSampleRuns[1] = {{1 * sMotorSettings.u32axisRange / 4,
                         2 * sMotorSettings.u32axisRange / 4,
                         3 * sMotorSettings.u32axisRange / 4,
                         4 * sMotorSettings.u32axisRange / 4,
                         sMotorSettings.u32axisRange / 2},
                        5};
      break;
   }
}


/*!
 @fn              vSetDefaultSettings(uint8_t axisType)
 @brief           Schreibt die Default-Settings entsprechd des Achsen-Typs (axisType) in die globale Struktur "sMotorSettings_t aSettings".
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vSetDefaultSettings(uint8_t u8axisType)
{
   switch (u8axisType)
   {
   case AXIS_TYPE_DEFAULT:
      // Axis One settings
      sMotorSettings.u32axisRange = 3150u; // 40mm Fahrweg bei 78,74Schritte pro mm = 3150 Schritte
      sMotorSettings.u32motorAcceleration = 14000u;
      sMotorSettings.u32motorSpeedMax = 1500u;
      sMotorSettings.u8LsActive = LOW;
      sMotorSettings.u8dir = 1;
      sMotorSettings.u16lsRangeSteps = 222u;
      sMotorSettings.u8enablePin = PIN_ENABLE;
      sMotorSettings.u8lsPin = PIN_LSSIG;
      sMotorSettings.u8axisType = AXIS_TYPE_DEFAULT;
      sMotorSettings.u32axisZeropoint = 22;
      sMotorSettings.u8vref = 80;                                    // Strom ca. 272mA
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##                   - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "Default");
      break;
   case AXIS_TYPE_421_TRANSPORT_X:
      // Axis One settings                                                //## Nimo X-Achse     ----> Werte sind halbiert, da der Motor statt 0,9° Schrittwinkel 1,8° hat !!!!
      sMotorSettings.u32axisRange = 4000u;                           //## 1700u      - länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 38000u;                  //## 19000u     - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 3500u;                       //## 1750u      - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                               //## LOW        - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                                      //## 1          - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 400u;                         //## 200u       - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;                       //## PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                            //## PIN_LSSIG  - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                           //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                             //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_421_TRANSPORT_X;         //##            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           //## 0
      sMotorSettings.u8vref = 240;                                   //## 240=575mA   200=468mA         - Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "421 X-Transport");
      break;

   case AXIS_TYPE_421_TRANSPORT_Y:
      // Axis One settings                                                //## Nimo Y-Achse     ----> Motor-Werte wie X Achse CLARIO etc.
      sMotorSettings.u32axisRange = 4500u;                   //## 7000u      - länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 38000u;          //## 38000u     - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 3500u;               //## 3500u      - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = HIGH;                      //## LOW        - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                              //## 1          - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 400u;                 //## 200u       - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;               //## PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                    //## PIN_LSSIG  - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                   //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                     //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_421_TRANSPORT_Y; //##            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           //## 0
      sMotorSettings.u8vref = 130;                                   //## 130         - Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "421 Y-Transport");
      break;

   case AXIS_TYPE_421_MPC_Z_3:
      // Axis One settings                                 //## Getriebemotor 1:30 Z-Achse für Transportsystem  - Mikroplattenträger (altes Kunstoffsystem)
      sMotorSettings.u32axisRange = 2000u;               //## 2000u          - länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 15000u;      //## 15000u         - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1200u;           //## 1200u          - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                   //## LOW            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                          //## 1 (0)          - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 1100u;            //## 1100u          - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;           //## PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                //## PIN_LSSIG      - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;               //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                 //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_421_MPC_Z_3; //##                - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 950;                         //## 950 (0)
      sMotorSettings.u8vref = 200;                                   //## 240=575mA  200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##                - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "421 MPC Z 1:30");
      break;

   case AXIS_TYPE_421_MPC_Z_4:
      // Axis One settings                                 //## Spindelmotor Z-Achse für Transportsystem  - Mikroplattenträger (MPC Transportsystem II)
      sMotorSettings.u32axisRange = 1500u;               //## 1500u          - länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 15000u;      //## 15000u         - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 2000u;           //## 2000u          - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                   //## LOW            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 0;                          //## 0              - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 300u;             //## 300u           - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;           //## PIN_ENABLE     - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                //## PIN_LSSIG      - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;               //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                 //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_421_MPC_Z_4; //##                - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           //## 0
      sMotorSettings.u8vref = 150;                                   //## 240=575mA  200=468mA 150=375mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##                - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "421 MPC Z Spindle");
      break;

   case AXIS_TYPE_421_LENS_CHANGE:
      sMotorSettings.u32axisRange = 3150u;                  // 40 mm Fahrweg bei 78,74 Schritte pro mm = 3150 Schritte
      sMotorSettings.u32motorAcceleration = 20000u;         //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 2000u;              //            - maximale Clock-Frequenz - danach Schritteiler 1/4
      sMotorSettings.u8LsActive = LOW;                      //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                             //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 600u;                //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;              // PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                   // PIN_LSSIG  - PIN für Initfahrt   
      sMotorSettings.u8stepPin = PIN_STEP;                  //            - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                    //            - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_421_LENS_CHANGE;
      sMotorSettings.u32axisZeropoint = 0;
      sMotorSettings.u8vref = 160;                          // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                           //##            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "421 Objekt.Haydon");
      break;

   case AXIS_TYPE_430_TRANSPORT_X:
      // Axis One settings                                                // CLARIO X-Achse
      sMotorSettings.u32axisRange = 4000u;                   //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 38000u;          //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 3500u;               //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                       //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                              //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 300u;                 //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;               // PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                    // PIN_LSSIG  - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                   //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                     //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_TRANSPORT_X; //            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // 0
      sMotorSettings.u8vref = 250;                                   // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                                          // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 2; //            - Standby Strom für den Motor
      sMotorSettings.u32loop = 0;                                    //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 X-Transport");
      break;

   case AXIS_TYPE_430_TRANSPORT_Y:
      // Axis One settings                                                // CLARIO Y-Achse
      sMotorSettings.u32axisRange = 4500u;                   //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 38000u;          //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 3500u;               //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = HIGH;                      //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                              //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 250u;                 //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;               // PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                    // PIN_LSSIG  - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                   //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                     //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_TRANSPORT_Y; //            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // 0
      sMotorSettings.u8vref = 250;                                   // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                                          // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 2; //            - Standby Strom für den Motor
      sMotorSettings.u32loop = 0;                                    //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 Y-Transport");
      break;

   case AXIS_TYPE_430_TOP_BOTTOM: //  Top / Bottom Optic Umschaltung
      // Axis One settings
      sMotorSettings.u32axisRange = 2910u;                  //             - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 14000u;         //             - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1500u;              //             - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                      //             - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                             //             - Hauptdrehrichtung des Motors
      sMotorSettings.u16lsRangeSteps = 200u;                //             - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;              // PIN_ENABLE  - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                   // PIN_LSSIG   - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                  //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                    //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_TOP_BOTTOM; //             - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                  // 0
      sMotorSettings.u8vref = 110;                          // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                                 // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;                     //             - Standby Strom für den Motor
      sMotorSettings.u32loop = 0;                           //             - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 top/bottom");
      break;

   case AXIS_TYPE_430_TOP_OPTIC_Z:
      // Axis One settings                                   //  Top Optic Z CLARIO
      sMotorSettings.u32axisRange = 1940u;                   //             - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 14000u;          //             - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1500u;               //             - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                       //             - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 0;                              //             - Hauptdrehrichtung des Motors
      sMotorSettings.u16lsRangeSteps = 200u;                 //             - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;               // PIN_ENABLE  - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                    // PIN_LSSIG   - PIN für Initfahrt     -
      sMotorSettings.u8stepPin = PIN_STEP;                   //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                     //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_TOP_OPTIC_Z; //             - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0; // 0
      sMotorSettings.u8vref = 110;         // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;    //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;          //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 top Optic");
      break;

   case AXIS_TYPE_430_BOT_OPTIC_Z:
      // Axis One settings                                   //  Bottom Optic Z CLARIO
      sMotorSettings.u32axisRange = 1310u;                   //             - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 14000u;          //             - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1500u;               //             - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                       //             - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                              //             - Hauptdrehrichtung des Motors
      sMotorSettings.u16lsRangeSteps = 200u;                 //             - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;               // PIN_ENABLE  - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                    // PIN_LSSIG   - PIN für Initfahrt     -
      sMotorSettings.u8stepPin = PIN_STEP;                   //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                     //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_BOT_OPTIC_Z; //             - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                   // 0
      sMotorSettings.u8vref = 110;                           // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                                  // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;                      //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                            //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 bot Optic");
      break;

   case AXIS_TYPE_430_EX_SOURCE:
      // Axis One settings                                   //  CLARIOstar Plus 4-fach Excitationslichtquwllwnumschaltung
      sMotorSettings.u32axisRange = 1790u;                 //             - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 14000u;        //             - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1500u;             //             - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                     //             - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                            //             - Hauptdrehrichtung des Motors
      sMotorSettings.u16lsRangeSteps = 220u;               //             - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;             // PIN_ENABLE  - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                  // PIN_LSSIG   - PIN für Initfahrt     -
      sMotorSettings.u8stepPin = PIN_STEP;                 //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                   //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_EX_SOURCE; //             - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                 // 0
      sMotorSettings.u8vref = 110;                         // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                                // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;                    //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                          //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 Exc Source");
      break;

   case AXIS_TYPE_430_PMT_AXIS:
      // Axis One settings                                   //  CLARIOstar Plus Dual PMT Achse
      sMotorSettings.u32axisRange = 1300u;                //             - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 18000u;       //             - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 2000u;            //             - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                    //             - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 0;                           //             - Hauptdrehrichtung des Motors
      sMotorSettings.u16lsRangeSteps = 150u;              //             - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;            // PIN_ENABLE  - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                 // PIN_LSSIG   - PIN für Initfahrt     -
      sMotorSettings.u8stepPin = PIN_STEP;                //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                  //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_430_PMT_AXIS; //             - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                // 0
      sMotorSettings.u8vref = 110;                        // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                               // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;                   //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                         //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "430 PMT Axis");
      break;

   case AXIS_TYPE_472_INJ_X:
      // Axis One settings                                 //## Transportsystem für Nadelträger X-Richtung: Achtung 1/4 Schritt
      sMotorSettings.u32axisRange = 1410u;             //              - länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 22000u;    //              - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 2500u;         //              - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                 //              - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 0;                        //              - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 250u;           //              - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;         // PIN_ENABLE   - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;              // PIN_LSSIG    - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;             //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;               //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_472_INJ_X; // AXIS_TYPE_   - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;             // 0
      sMotorSettings.u8vref = 250;                     // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                            // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 40;               //              - Standby Strom für den Motor
      sMotorSettings.u32loop = 0;                      //              - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "472 Inject X  1/4");
      break;

   case AXIS_TYPE_472_INJ_Z:
      // Axis One settings                                 //## Transportsystem für Nadelträger Z-Richtung
      sMotorSettings.u32axisRange = 1470u;             //               - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 14000u;    //               - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1500u;         //               - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                 //               - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                        //               - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 150u;           //               - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;         // PIN_ENABLE    - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;              // PIN_LSSIG     - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;             //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;               //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_472_INJ_Z; //               - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;             // 0
      sMotorSettings.u8vref = 150;                     // 250=598mA 240=575 230=553 220=531 210=509 200=486 190=464 180=442 170=419 160=397 150=375mA
                                                            // 140=352mA 130=330 120=308 110=285 100=263  90=241 80=218mA 70=196  60=174  50=152mA Stromeinstellung
      sMotorSettings.u8vrefStandby = 0;                //               - Standby Strom für den Motor
      sMotorSettings.u32loop = 0;                      //               - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "472 Injector Z");

   case AXIS_TYPE_SF2_EX_SLIT_IN:
      // Axis One settings                                           //Getriebemotor für Slitantrieb
      sMotorSettings.u32axisRange = 1400u;                           //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 4000u;                   //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1000u;                       //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = HIGH;                              //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                                      //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 300u;                         //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE4;                      //  PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG4;                           //  PIN_LSSIG      - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP4;                          //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR4;                            //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_SF2_EX_SLIT_IN;          //                 - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // (0)
      sMotorSettings.u8vref = 80;                                    // 240=575mA  200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //##  - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //##                - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "SF2 Ex Slit In");
      break;

   case AXIS_TYPE_SF2_EX_SLIT_MID:
      // Axis One settings                                 //Getriebemotor für Slitantrieb
      sMotorSettings.u32axisRange = 1400u;                           //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 4000u;                   //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1000u;                       //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = HIGH;                              //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                                      //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 300u;                         //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE5;                      //            - PIN_ENABLE von Motor 5 = Enable Motor 4
      sMotorSettings.u8lsPin = PIN_LSSIG5;                           //            - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP5;                          //              - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR5;                            //              - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_SF2_EX_SLIT_MID;         //                 - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // (0)
      sMotorSettings.u8vref = 80;                                    // 240=575mA  200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5; //          - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //          - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "SF2 Ex Slit Mid");
      break;

   case AXIS_TYPE_SF2_EX_SLIT_OUT:
      // Axis One settings                                 //Getriebemotor für Slitantrieb
      sMotorSettings.u32axisRange = 1400u;                           //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 4000u;                   //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 1000u;                       //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = HIGH;                              //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                                      //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 300u;                         //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE3;                      //  PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG3;                           //  PIN_LSSIG - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP3;                          //            - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR3;                            //            - PIN für Direction
      sMotorSettings.u8axisType = AXIS_TYPE_SF2_EX_SLIT_OUT;         //            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // (0)
      sMotorSettings.u8vref = 80;                                    // 240=575mA    200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5;      //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "SF2 Ex Slit Out");
      break;


      case AXIS_Type_SF2_Grating:
      // Axis One settings                                    //Motor für Gratings zur WL - Einstellung
      sMotorSettings.u32axisRange = 200000u;                         //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 70000u;                  //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 10500u;                       //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                               //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 0;                                      //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 2000u;                        //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE;                       //  PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG;                            //  PIN_LSSIG - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP;                           //            - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR;                             //            - PIN für Direction
      sMotorSettings.u8axisType = AXIS_Type_SF2_Grating;             //                 - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // (0)
      sMotorSettings.u8vref = 127;                                   // 240=575mA    200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5;      //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "SF2 Ex Grating");
      break;

      case AXIS_Type_SF2_OrderSort:
      // Axis One settings                                 //Getriebemotor für Slitantrieb
      sMotorSettings.u32axisRange = 200000u;                         //            - Länge der Achse in Schritte
      sMotorSettings.u32motorAcceleration = 50000u;                  //            - max. Beschleunigung
      sMotorSettings.u32motorSpeedMax = 8000u;                       //            - maximale Clock-Frequenz - danach Schritteiler
      sMotorSettings.u8LsActive = LOW;                               //            - Lichtschranke Low / High-Aktiv
      sMotorSettings.u8dir = 1;                                      //            - Hauptrichtung
      sMotorSettings.u16lsRangeSteps = 100u;                         //            - Strecke für Herausfahren aus der LS
      sMotorSettings.u8enablePin = PIN_ENABLE2;                      //  PIN_ENABLE - PIN für Enable
      sMotorSettings.u8lsPin = PIN_LSSIG2;                           //  PIN_LSSIG - PIN für Initfahrt
      sMotorSettings.u8stepPin = PIN_STEP2;                          //            - PIN für Schritte
      sMotorSettings.u8dirPin = PIN_DIR2;                            //            - PIN für Direction
      sMotorSettings.u8axisType = AXIS_Type_SF2_OrderSort;           //            - Welcher Typ von Achse?
      sMotorSettings.u32axisZeropoint = 0;                           // (0)
      sMotorSettings.u8vref = 80;                                    // 240=575mA    200=468mA 100=340mA   80=270mA Stromeinstellung
      sMotorSettings.u8vrefStandby = sMotorSettings.u8vref / 5;      //            - Standby Strom für den Motor ist 20% des Nennstromes
      sMotorSettings.u32loop = 0;                                    //            - aktuelle Anzahl ausgeführter Loops im Dauerlauf
      strcpy(sMotorSettings.acAxisName, "SF2 Ex OrderFilter");
      break;


   }
   sMotorSettings.u8isInit = 0;
   sMotorSettings.u8lsflag = 0;     
}

/*!
 @fn              void vClearEeprom(void)
 @brief           Stellt den Originalzustand des EEPROMs wieder her (Schreibt in jedes Byte den Wert '-1')
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vClearEeprom(void)
{
   int address = 0;
   int8_t value = -1;
   while(address < 4096)
   {
      writeEeprom<int8_t>(address++, &value);
   }
}

/*!
 @fn              int8_t u8ReadLastAxisType()
 @brief           Liest anhand der Addresse 'LAST_AXIS_ADDR' aus ob und welche Achse als letzte im EEPROM geschrieben wurde.
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      int8_t  NO_LAST_AXIS_AVAILABLE == Keine Achse bisher im EEPROM abgelegt
                         'AxisType' == Speziellen define-Wert der Achse
*/
int8_t u8ReadLastAxisType(void)
{
   int8_t s8LastAxisType;
   readEeprom<int8_t>(LAST_AXIS_ADDR, &s8LastAxisType);
   return s8LastAxisType;
}

/*!
 @fn              void vReadSettingsFromEeprom
 @brief           Berechnet anhand des übergebenen Achsen-Typs die Ziel-Adresse im EEPROM und schreibt ab Beginn dieser Adresse die Settings.
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void vReadSettingsFromEeprom(uint8_t u8AxisType)
{
   uint32_t u32Address = u8AxisType * (sizeof(sMotorSettings_t) + 1) + 2;
   readEeprom<sMotorSettings_t>(u32Address, &sMotorSettings);
}

/*!
 @fn              int8_t u8ReadAxisFlag(uint8_t u8axisType)
 @brief           Berechnet anhand des übergebenen Achsen-Typs die Adresse für ein Flag, welches definiert ob besagte Achse bereits im EEPROM beschrieben wurde.
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      int8_t 1 == Settings für Achse vorhanden
                        -1 == Settings für Achse nicht vorhanden
*/
int8_t u8ReadAxisFlag(uint8_t u8AxisType)
{
   int8_t u8SavedFlag = 0;
   uint32_t u32Address = u8AxisType * sizeof(sMotorSettings_t) + 1;
   readEeprom<int8_t>(u32Address, &u8SavedFlag);
   return u8SavedFlag;
}




void vWriteSettingsToEeprom(uint8_t u8AxisType)
{
   uint32_t u32Address = u8AxisType * (sizeof(sMotorSettings_t) + 1) + 2;
   writeEeprom<sMotorSettings_t>(u32Address, &sMotorSettings);
}
void vWriteLastAxisType(uint8_t u8AxisType)
{
   writeEeprom<uint8_t>(LAST_AXIS_ADDR, &u8AxisType);
}
void vWriteAxisFlag(uint8_t u8AxisType)
{
   int8_t u8SavedFlag = AXIS_SAVED;
   uint32_t u32Address = u8AxisType * sizeof(sMotorSettings_t) + 1;
   writeEeprom<int8_t>(u32Address, &u8SavedFlag);
}
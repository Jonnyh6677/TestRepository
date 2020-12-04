#ifndef SETTINGS_h
#define SETTINGS_h

#include "MotorDriver.h"

#define PIN_SEROUT 1

// Pin settings
#define PIN_SEROUT 1
#define PIN_LSSIG 2
#define PIN_LSSIG_TXA 8
#define PIN_ENABLE 3
#define PIN_DIR 4
#define PIN_STEP 5
#define PIN_VREF A21

// Motor 2
#define PIN_LSSIG2 25
#define PIN_ENABLE2 9
#define PIN_DIR2 10
#define PIN_STEP2 11
#define PIN_VREF2 A22

// Motor 3
#define PIN_LSSIG3 31
#define PIN_ENABLE3 27
#define PIN_DIR3 28
#define PIN_STEP3 29

// Motor 4
#define PIN_LSSIG4 34
#define PIN_ENABLE4 39
#define PIN_DIR4 38
#define PIN_STEP4 37

// Motor 5
#define PIN_LSSIG5 33     // 33
#define PIN_ENABLE5 39    // 39 entspricht pin_enable4
#define PIN_DIR5 35       // 35
#define PIN_STEP5 36      // 36

#define PIN_JOYSTICK_UP 22
#define PIN_JOYSTICK_RIGHT 20
#define PIN_JOYSTICK_DOWN 19
#define PIN_JOYSTICK_LEFT 23
#define PIN_JOYSTICK_CENTRE 21

#define PIN_BUTTON_BLACK 18
#define PIN_BUTTON_WHITE 17

// Varianten um die Settings zu setzen/laden
#define AXIS_SETTINGS_INIT -1
#define AXIS_SETTINGS_DEFAULT -2
#define AXIS_SETTINGS_LOAD -3

// Art der Achse definieren
#define AXIS_TYPE_DEFAULT 0
#define AXIS_TYPE_421_TRANSPORT_X 1
#define AXIS_TYPE_421_TRANSPORT_Y 2
#define AXIS_TYPE_430_TRANSPORT_X 21
#define AXIS_TYPE_430_TRANSPORT_Y 22
#define AXIS_TYPE_430_TOP_BOTTOM 3
#define AXIS_TYPE_430_TOP_OPTIC_Z 4
#define AXIS_TYPE_430_BOT_OPTIC_Z 23
#define AXIS_TYPE_430_EX_SOURCE 24
#define AXIS_TYPE_430_PMT_AXIS 25
#define AXIS_TYPE_421_MPC_Z 5
#define AXIS_TYPE_421_MPC_Z_2 6
#define AXIS_TYPE_421_MPC_Z_3 7
#define AXIS_TYPE_421_MPC_Z_4 8
#define AXIS_TYPE_421_LENS_CHANGE 9
#define AXIS_TYPE_472_INJ_X 10
#define AXIS_TYPE_472_INJ_Z 11
#define AXIS_TYPE_USER 12
#define AXIS_TYPE_472_TRANSPORT_X 13
#define AXIS_TYPE_472_TRANSPORT_Y 14
#define AXIS_TYPE_472_OPTIC_MODUL 15
#define AXIS_TYPE_472_PMT_AXIS 16
#define AXIS_TYPE_472_TOP_OPTIC_Z 17
#define AXIS_TYPE_471_TOP_OPTIC_Z 26
#define AXIS_TYPE_472_TOP_BOTTOM 18
#define AXIS_TYPE_472_BOT_OPTIC_Z 19
#define AXIS_TYPE_472_EX_SOURCE 20
#define AXIS_TYPE_SF2_EX_SLIT_IN 27
#define AXIS_TYPE_SF2_EX_SLIT_MID 28
#define AXIS_TYPE_SF2_EX_SLIT_OUT 29
#define AXIS_Type_SF2_Grating 30
#define AXIS_Type_SF2_OrderSort 31

// Aktuell Monochromatoren
#define MON_TYPE_H1034        0
#define MON_TYPE_MDM5         1
#define MON_TYPE_SF2          2
#define MON_TYPE_H1511        3
#define MON_TYPE_H1512        4
#define MON_TYPE_H4EX_FIX     5

// Entprell delay
#define DEBOUNCE_TIME 280

// Display Print Delay
#define DISPLAY_PRINT_DELAY 50

// Motor Step Timer
#define TIMER_STEP_INTERVAL 30

// Delay beim Load / Save setting screen
#define LOAD_SAVE_DELAY 1000
#define LCD_SHOW_DELAY 1200

// Motor defines
#define AXIS_ONE 0 // welche physikalische Motorstufe verwendet werden soll
#define AXIS_TWO 1



// EEPROM defines
/*
EEPROM Adresse an welcher die letzte Achse abgelegt wurde. Wenn noch keine 
noch keine Settings für eine Achse im EEPROM gespeichert wurden, steht hier der Wert '-1' (Default EEPROM Wert)
*/
#define LAST_AXIS_ADDR 0        

/*
Definiert, wie bei 'LAST_AXIS_ADDR' beschrieben, den Wert, welcher Ausgelesen
wird, wenn bisher noch keine Settings für eine Achse im EEPROM gespeichert wurden.
*/
#define NO_LAST_AXIS_AVAILABLE -1 

// Wert für das das 'Axis Saved Flag'. Gibt an ob für diesen 'Achsen-Typ' (u8axisType) bereits Settings im EEPROM abgelegt sind
#define AXIS_SAVED 1              



typedef struct
{
   uint32_t u32positions[20];
   uint8_t u32num_positions;
} SampleRun_t;

typedef struct
{
   uint32_t u32axisRange;
   uint32_t u32axisZeropoint;
   uint32_t u32motorAcceleration;
   uint32_t u32motorSpeedMax;
   uint32_t u8vref;
   uint32_t u8vrefStandby;
   uint32_t u32loop;
   uint16_t u16lsRangeSteps;
   uint8_t u8lsflag;
   uint8_t u8enablePin;
   uint8_t u8LsActive;
   uint8_t u8dir;
   uint8_t u8axisType;
   uint8_t u8lsPin;
   uint8_t u8isInit;
   uint8_t u8lsTxaPin;
   uint8_t u8LsTxaActive;
   uint8_t u8lsFlag;
   uint8_t u8stepPin;
   uint8_t u8dirPin;
   char acAxisName[20];
} sMotorSettings_t;

// Externe Variablen (Globale Variablen)
extern sMotorSettings_t sMotorSettings;
extern SampleRun_t sSampleRuns[12]; // Anzahl der möglichen Beispielfahrten
extern elapsedMillis timeElapsed;

// Setting Funktionen
void vSettingsInit(uint8_t u8monochromatorType, int8_t s8action);
void vSetExampleRuns(uint8_t u8axisType);
void vInitializeSettings(void);
void vSetDefaultSettings(uint8_t u8axisType);
void vLoadSettings(uint8_t u8axisType);

//EEPROM Zugriff
void vReadSettingsFromEeprom(uint8_t u8AxisType);
int8_t u8ReadLastAxisType();
int8_t u8ReadAxisFlag(uint8_t u8AxisType);

void vWriteSettingsToEeprom(uint8_t u8AxisType);
void vWriteLastAxisType(uint8_t u8AxisType);
void vWriteAxisFlag(uint8_t u8AxisType);

void vClearEeprom(void);

#endif

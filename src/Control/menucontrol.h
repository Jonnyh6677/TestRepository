#ifndef MENUCONTROL_h
#define MENUCONTROL_h

#include "MotorDriver.h"


// Menu Display, Control, Clear Functions
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// settings for LCD
#define _LCDML_DISP_cols   20
#define _LCDML_DISP_rows   4
#define _LCDML_DISP_cnt    110                  // gesamte Anzahl der Menuelemente


#define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
#define _LCDML_DISP_cfg_scrollbar                  0      // enable a scrollbar


// Control Pins (Joystick) and Settings
#define _LCDML_CONTROL_digital_low_active      1    // 0 = high active (pulldown) button, 1 = low active (pullup)                                                  // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
#define _LCDML_CONTROL_digital_enable_quit     1
#define _LCDML_CONTROL_digital_enable_lr       1

#define _LCDML_CONTROL_digital_enter           PIN_JOYSTICK_CENTRE  // Joystick Center
#define _LCDML_CONTROL_digital_up              PIN_JOYSTICK_UP  // Joystick Up
#define _LCDML_CONTROL_digital_down            PIN_JOYSTICK_DOWN  // Joystick Down

#define _LCDML_CONTROL_digital_left            PIN_JOYSTICK_LEFT  // Joystick Left
#define _LCDML_CONTROL_digital_right           PIN_JOYSTICK_RIGHT  // Joystick Right

#define _LCDML_CONTROL_digital_quit            PIN_BUTTON_BLACK  // Joystick Right
#endif

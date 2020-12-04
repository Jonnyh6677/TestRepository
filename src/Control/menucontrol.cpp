#include "menucontrol.h"
//********************************************************************
//
//                    Control, Clear Framework Functions
//
// *******************************************************************

unsigned long g_LCDML_DISP_press_time = 0;

void lcdml_menu_clear()
/* ******************************************************************** */
{
  lcd.clear();
  lcd.setPosition(0, 0);
}


void lcdml_menu_control(void)
{
  // If something must init, put in in the setup condition
  if(LCDML.BT_setup()) {
    // runs only once
    // init buttons
    pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);
    # if(_LCDML_CONTROL_digital_enable_quit == 1)
      pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
    # endif
    # if(_LCDML_CONTROL_digital_enable_lr == 1)
      pinMode(_LCDML_CONTROL_digital_left     , INPUT_PULLUP);
      pinMode(_LCDML_CONTROL_digital_right    , INPUT_PULLUP);
    # endif
  }

  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif

  uint8_t but_stat = 0x00;

  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_left)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_right)));
  #endif

  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= DEBOUNCE_TIME) {
      g_LCDML_DISP_press_time = millis(); // reset press time

      if (bitRead(but_stat, 0)) { LCDML.BT_enter(); }
      if (bitRead(but_stat, 1)) { LCDML.BT_up();    }
      if (bitRead(but_stat, 2)) { LCDML.BT_down();  }
      if (bitRead(but_stat, 3)) { LCDML.BT_quit();  }
      if (bitRead(but_stat, 4)) { LCDML.BT_left();  }
      if (bitRead(but_stat, 5)) { LCDML.BT_right(); }
    }
  }
}


#ifndef FILTERMOVE_h
#define FILTERMOVE_h

#include "MotorDriver.h"

void vFiltermoveH1034(uint16_t u16wl);
void vFiltermoveMDM5(uint16_t u16wl);
void vFiltermoveSF2(uint16_t u16wl);
uint8_t u8GetFilterAxis(uint8_t monochromatorType);
#endif

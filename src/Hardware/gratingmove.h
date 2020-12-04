#ifndef GRATINGMOVE_h
#define GRATINGMOVE_h

#include "Motordriver.h"

void vGratingmoveH1034(uint16_t u16wl);
void vGratingmoveMDM5(uint16_t u16wl);
void vGratingmoveSF2(uint16_t u16wl);
void vGratingmoveH1511(uint16_t u16wl);
void vGratingmoveH1512(uint16_t u16wl);
void vGratingmoveH4EXfix(uint16_t u16wl);

uint8_t u8GetGratingAxis(uint8_t monochromatorType);

#endif

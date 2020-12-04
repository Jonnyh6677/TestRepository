#include "gratingmove.h"

/*!
 @fn              void vFiltermoveH1034(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (H1034)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveH1034(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = -6411.190632697036 + 26.971774412894533 * u16wl + 0.0036172213952621467 * (u16wl * u16wl);
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              void vFiltermoveMDM5(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (MDM5)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveMDM5(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = 1266.53523801586 - 0.502962943547409 * u16wl - 0.000215939 * (u16wl * u16wl);
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              void vFiltermoveSF2(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (SF2)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveSF2(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = 492.492 + 6.323185 * u16wl + 0.0009421701 * (u16wl * u16wl); //2020-11-05 MS mit Blitzlampe 0202, 3mm FlüssigkeitsLL und 2mm Slit
   // float f32pos = -140.70523102 + 7.97413542 * u16wl - 0.00029366 * (u16wl * u16wl);  ursprünglich mit LED 2018
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              void vGratingmoveH1511(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (H1511)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveH1511(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = 14727 - 52.118 * u16wl - 0.0087 * (u16wl * u16wl);
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              void vGratingmoveH1512(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (H1512)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveH1512(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = 17903.222536441 - 55.03822529 * u16wl - 0.006666427 * (u16wl * u16wl);
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              void vGratingmoveH4EXfix(uint16_t u16wl)
 @brief           Move Grating to the corret position according WL.
                  This function is for a specific Monochromator Type (H4EX Fix)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vGratingmoveH4EXfix(uint16_t u16wl)
{
   // calc grating position (polynom)
   float f32pos = 11441.86 - 29.79560689 * u16wl - 0.00123467 * (u16wl * u16wl);
   // move to position
   vRunsMoveTo(f32pos);
}

/*!
 @fn              u8GetGratingAxis(uint8_t monochromatorType)
 @brief           This function returs monochromatorType corresponding axis define
 @author 	      Jonathan Haas
 @param 	         uint8_t monochromatorType
 @return 	      uint8_t
*/
uint8_t u8GetGratingAxis(uint8_t monochromatorType)
{
   switch (monochromatorType)
   {
   case MON_TYPE_H1034:
   case MON_TYPE_MDM5:
   case MON_TYPE_H1511:
   case MON_TYPE_H1512:
   case MON_TYPE_H4EX_FIX:
      return 0;
      break;
   case MON_TYPE_SF2:
      return AXIS_Type_SF2_Grating;
      break;
   default:
      return 0;
      break;
   }
}

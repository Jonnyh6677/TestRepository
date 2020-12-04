#include "filtermove.h"

/*!
 @fn              void vFiltermoveMDM5(uint16_t u16wl)
 @brief           Move filter to the corret position according WL.
                  This function is for a specific Monochromator Type (H1034)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vFiltermoveH1034(uint16_t u16wl)
{
   // None Filter
   if (u16wl <= 220)
   {
      vRunsMoveTo(145 * 8);
   }

   // Grey Filter
   else if ((u16wl > 220) && (u16wl <= 350))
   {
      vRunsMoveTo(255 * 8);
   }

   // Blue Filter
   else if ((u16wl > 350) && (u16wl <= 445))
   {
      vRunsMoveTo(332 * 8);
   }

   // Green Filter
   else if ((u16wl > 445) && (u16wl <= 555))
   {
      vRunsMoveTo(404 * 8);
   }

   // Orange Filter
   else if ((u16wl > 555) && (u16wl <= 650))
   {
      vRunsMoveTo(477 * 8);
   }

   // Red Filter
   else
   {
      vRunsMoveTo(552 * 8);
   }
}

/*!
 @fn              void vFiltermoveMDM5(uint16_t u16wl)
 @brief           Move filter to the corret position according WL.
                  This function is for a specific Monochromator Type (MDM5)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vFiltermoveMDM5(uint16_t u16wl)
{

   // Open
   if (u16wl <= 310)
   {
      vRunsMoveTo(0);
   }

   // Grey
   else if ((u16wl > 310) && (u16wl <= 375))
   {
      vRunsMoveTo(-96 + 5);
   }

   // Blue
   else if ((u16wl > 375) && (u16wl <= 535))
   {
      vRunsMoveTo(-384 + 5);
   }

   // Orage
   else if ((u16wl > 535) && (u16wl <= 592))
   {
      vRunsMoveTo(-480 + 5);
   }

   // Violett
   else if ((u16wl > 592) && (u16wl <= 654))
   {
      vRunsMoveTo(-576 + 5);
   }

   // Red
   else
   {
      vRunsMoveTo(-672 + 5);
   }
}

/*!
 @fn              void vFiltermoveSF2(uint16_t u16wl)
 @brief           Move filter to the corret position according WL.
                  This function is for a specific Monochromator Type (SF2)
 @author 	      Jonathan Haas
 @param 	         uint16_t u16wl
 @return 	      void
*/
void vFiltermoveSF2(uint16_t u16wl)
{

   // Open
   if (u16wl <= 325)
   {
      vRunsMoveTo(2000);
   }

   // Glas
   else if ((u16wl > 325) && (u16wl <= 520))
   {
      vRunsMoveTo(4150);
   }

   // Yellow
   else
   {
      vRunsMoveTo(6300);
   }
}

/*!
 @fn              u8GetFilterAxis(uint8_t monochromatorType)
 @brief           This function returs monochromatorType corresponding axis define
 @author 	      Jonathan Haas
 @param 	         uint8_t monochromatorType
 @return 	      uint8_t
*/
uint8_t u8GetFilterAxis(uint8_t monochromatorType)
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
      return AXIS_Type_SF2_OrderSort;
      break;
   default:
      return 0;
      break;
   }
}

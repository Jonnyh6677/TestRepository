#include "digitcontrol.h"

/*!
 @fn            DigitControl(int32_t* value, uint8_t lcdRow, uint8_t lcdCol)
 @brief         Konstruktor (Initialisiert das Objekt anhand übergebenen Werten oder auch Konstanten)
 @author 	    Jonathan Haas
 @param 	       int32_t* value := Pointer den zu manipulierenden Wert
                uint8_t lcdRow := Startindex der LCD Reihe (Y-Wert)
                uint8_t lcdCol := Startindex der LCD Spalte (X-Wert)
 @return 	    void
*/
DigitControl::DigitControl(int32_t* value, uint8_t lcdCol, uint8_t lcdRow)
{
    this->value = value;
    this->decimalPos = 0;
    this->lcdCol = lcdCol;
    this->lcdRow = lcdRow;
    this->DEC_NUM = 6;
}

/*!
 @fn              MoveDecimalPosLeft()
 @brief           Verschiebt die Dezimalstelle um eins nach Links
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::MoveDecimalPosLeft()
{
   if(decimalPos < DEC_NUM - 1)
   {
      decimalPos++;
      Print();
   }
}

/*!
 @fn              MoveDecimalPosRight()
 @brief           Verschiebt die Dezimalstelle um eins nach Rechts
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::MoveDecimalPosRight()
{
   if(decimalPos > 0)
   {
      decimalPos--;
      Print();
   }
}

/*!
 @fn              IncrementValue()
 @brief           Inkrementiert den Wert entsprechend der aktuellen Dezimalstelle
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::IncrementValue()
{
  switch(decimalPos)
   {
      case 0:
         (*value += 1);
         break;
      case 1:
         (*value += 10);
         break;
      case 2:
         (*value += 100);
         break;
      case 3:
         (*value += 1000);
         break;
      case 4:
         (*value += 10000);
         break;
      case 5:
         (*value += 100000);
         break;
      default:
         break;
      }
      *value = *value % 999999;
      Print();
}

/*!
 @fn              DecrementValue()
 @brief           Inkrementiert den Wert entsprechend der aktuellen Dezimalstelle
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::DecrementValue()
{
   switch(decimalPos)
   {
      case 0:
         (*value -= 1);
         break;
      case 1:
         (*value -= 10);
         break;
      case 2:
         (*value -= 100);
         break;
      case 3:
         (*value -= 1000);
         break;
      case 4:
         (*value -= 10000);
         break;
      case 5:
         (*value -= 100000);
         break;
      default:
         break;
      }
      *value = *value % 999999;
      Print();
}

/*!
 @fn              PrintValue()
 @brief           Gibt den aktuellen Wert auf dem LCD aus
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::PrintValue()
{
   lcd.setPosition(lcdCol, lcdRow); // ## lcdCol
   lcd.print("        ");
   lcd.setPosition(lcdCol , lcdRow); // ## lcdCol
   lcd.printf("%07d",*value); // ## Switch case 
}

/*!
 @fn              PrintCursor()
 @brief           Gibt den Cursor an aktueller Position auf dem LCD aus
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::PrintCursor()
{
   uint8_t cursorPos = lcdCol + DEC_NUM - decimalPos; // ## lcdCol + 
   lcd.setPosition(lcdCol, lcdRow + 1); // ## lcdCol
   lcd.print("         ");
   lcd.setPosition(cursorPos, lcdRow + 1); 
   lcd.print("^");
}

/*!
 @fn              Print()
 @brief           Public-Funktion (Kann von Außen aufgerufen werden)
                  Gibt die gesamte Steuerung auf dem LCD aus
 @author 	      Jonathan Haas
 @param 	         void
 @return 	      void
*/
void DigitControl::Print()
{
   PrintValue();
   PrintCursor();
}

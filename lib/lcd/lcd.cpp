#include "lcd.h"

SerialLCD::SerialLCD(uint8_t rx, uint8_t tx) :
    SoftwareSerial(rx, tx)
{
     SoftwareSerial::begin(LCD_BAUD);
}


void SerialLCD::clear()
{
    SoftwareSerial::write(0xFE);
    SoftwareSerial::write(0x01);
      delay(10);

}

void SerialLCD::init()
{
    SoftwareSerial::write(0x7C);
    SoftwareSerial::write(0x03);
      delay(10);
}




void SerialLCD::setBacklight(int brightness)
{
    brightness = 100 * 29 / brightness;
    SoftwareSerial::write(0x7C);
    SoftwareSerial::write(128+brightness);
   delay(10);
}

void SerialLCD::setPosition(int col, int row)
{

    SoftwareSerial::write(0xFE);   //command flag
    switch(row)
    {
      case 0:
        SoftwareSerial::write(128 + col);
        break;
      case 1:
        SoftwareSerial::write(192 + col);
        break;
      case 2:
        SoftwareSerial::write(148 + col);
        break;
      case 3:
        SoftwareSerial::write(212 + col);
        break;
      default:
        SoftwareSerial::write(128 + col);
        break;

    }
      delay(10);
}

void SerialLCD::setVisible(bool visible)
{
    SoftwareSerial::print(0xFE);
    SoftwareSerial::print(visible ? 0x0C : 0x08);
      delay(10);
}

void SerialLCD::scrollLeft()
{
    SoftwareSerial::print(0xFE);
    SoftwareSerial::print(0x18);
      delay(10);
}

void SerialLCD::scrollRight()
{
    SoftwareSerial::print(0xFE);
    SoftwareSerial::print(0x1C);
      delay(10);

}

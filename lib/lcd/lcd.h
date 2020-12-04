#ifndef LCD_h
#define LCD_h

#include <SoftwareSerial.h>
#include <Arduino.h>

#define LCD_WIDTH 20
#define LCD_BAUD 9600



/**
 * SparkFun SerLCD v2.5 Controller
 */
class SerialLCD : public SoftwareSerial
{
  public:

    /**
     * Constructor.
     * @param tx Connected to rx pin of LCD
     * @param rx Not connected but needs to be specified for serial interface.
     */
    SerialLCD(uint8_t rx, uint8_t tx);

    /**
     * init display
     */
   void init();


    /**
     * Clear the LCD.
     */
    void clear();

    /**
     * Set backlight brightness;
     */
    void setBacklight(int brightness);

    /**
     * Set cursor position.
     */
    void setPosition(int col, int row);

    /**
     * Make LCD text visible or invisible.
     */
    void setVisible(bool visible);

    /**
     * Start scrolling to the left.
     */
    void scrollLeft();

    /**
     * Start scrolling to the right.
     */
    void scrollRight();


};
#endif

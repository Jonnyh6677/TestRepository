#include "interrupt.h"

/*!
 @fn              void TIMER0_ISR(void)
 @brief           Interrupt function for timer. Runs motor until flag is set (LS interrupt) or position is reached.
 @author 	      Jonathan Haas
 @return 	      void
*/
void TIMER0_ISR(void)
{
   if(stepMotor.isRunning() && sMotorSettings.u8lsflag == 0)
   {
      // move one step with acceleration
      stepMotor.run();
   }

}

/*!
 @fn              void lsinterrupt(void)
 @brief           Interrupt function for LS Pin. Sets the LS Flag to 1 if LS Signal (PIN_LSSIG/PIN_LSSIG2/PIN_LSSIG_TXA) changes.
 @author 	      Jonathan Haas
 @return 	      void
*/
void lsinterrupt(void)
{
   sMotorSettings.u8lsflag = 1;
}

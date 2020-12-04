#include "MotorDriver.h"

template <typename T>
void readEeprom(uint32_t address, T *destination)
{
   byte *currentByte = (byte *)destination;
   uint32_t currentAddress = address;

   for (uint32_t i = 0; i < sizeof(T); i++)
   {
      *currentByte = EEPROM.read(currentAddress);
      currentByte++;
      currentAddress++;
   }
}

template <typename T>
void writeEeprom(uint32_t address, T *source)
{
   byte *currentByte = (byte *)source;
   uint32_t currentAddress = address;

   for (uint32_t i = 0; i < sizeof(T); i++)
   {
      EEPROM.write(currentAddress, *currentByte);
      currentByte++;
      currentAddress++;
   }
}



/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#if USE_FALLBACK_EEPROM
  #define FLASH_EEPROM_EMULATION
#elif EITHER(I2C_EEPROM, SPI_EEPROM)
  #define USE_SHARED_EEPROM 1
#endif

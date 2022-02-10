/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// If no real or emulated EEPROM selected, fall back to SD emulation
#if USE_FALLBACK_EEPROM
  #define SDCARD_EEPROM_EMULATION
#elif EITHER(I2C_EEPROM, SPI_EEPROM)
  #define USE_SHARED_EEPROM 1
#endif

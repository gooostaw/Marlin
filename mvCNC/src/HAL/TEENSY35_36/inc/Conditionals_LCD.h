/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#if HAS_SPI_TFT || HAS_FSMC_TFT
  #error "Sorry! TFT displays are not available for HAL/TEENSY35_36."
#endif

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#if HAS_SPI_TFT || HAS_FSMC_TFT
  #error "Sorry! TFT displays are not available for HAL/DUE."
#endif

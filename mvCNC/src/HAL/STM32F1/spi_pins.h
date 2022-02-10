/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * HAL for stm32duino.com based on Libmaple and compatible (STM32F1)
 */

/**
 * STM32F1 Default SPI Pins
 *
 *         SS     SCK     MISO    MOSI
 *       +-----------------------------+
 *  SPI1 | PA4    PA5     PA6     PA7  |
 *  SPI2 | PB12   PB13    PB14    PB15 |
 *  SPI3 | PA15   PB3     PB4     PB5  |
 *       +-----------------------------+
 * Any pin can be used for Chip Select (SD_SS_PIN)
 * SPI1 is enabled by default
 */
#ifndef SD_SCK_PIN
  #define SD_SCK_PIN  PA5
#endif
#ifndef SD_MISO_PIN
  #define SD_MISO_PIN PA6
#endif
#ifndef SD_MOSI_PIN
  #define SD_MOSI_PIN PA7
#endif
#ifndef SD_SS_PIN
  #define SD_SS_PIN   PA4
#endif
#undef SDSS
#define SDSS    SD_SS_PIN

#ifndef SPI_DEVICE
  #define SPI_DEVICE 1
#endif

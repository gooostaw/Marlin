/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Define SPI Pins: SCK, MISO, MOSI, SS
 */
#ifndef SD_SCK_PIN
  #define SD_SCK_PIN  PIN_SPI_SCK
#endif
#ifndef SD_MISO_PIN
  #define SD_MISO_PIN PIN_SPI_MISO
#endif
#ifndef SD_MOSI_PIN
  #define SD_MOSI_PIN PIN_SPI_MOSI
#endif
#ifndef SD_SS_PIN
  #define SD_SS_PIN   PIN_SPI_SS
#endif

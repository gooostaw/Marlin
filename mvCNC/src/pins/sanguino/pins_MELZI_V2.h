/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Melzi V2.0 as found at https://www.reprap.org/wiki/Melzi
 */

#define BOARD_INFO_NAME "Melzi V2"

// Alter timing for graphical display
#if IS_U8GLIB_ST7920
  #define BOARD_ST7920_DELAY_1                 0
  #define BOARD_ST7920_DELAY_2               400
  #define BOARD_ST7920_DELAY_3                 0
#endif

#include "pins_MELZI.h" // ... SANGUINOLOLU_12 ... SANGUINOLOLU_11

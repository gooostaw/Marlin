/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Melzi pin assignments
 */

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Melzi"
#endif

#define IS_MELZI 1

// Alter timing for graphical display
#if IS_U8GLIB_ST7920
  #ifndef BOARD_ST7920_DELAY_1
    #define BOARD_ST7920_DELAY_1               0
  #endif
  #ifndef BOARD_ST7920_DELAY_2
    #define BOARD_ST7920_DELAY_2             188
  #endif
  #ifndef BOARD_ST7920_DELAY_3
    #define BOARD_ST7920_DELAY_3               0
  #endif
#endif

#include "pins_SANGUINOLOLU_12.h" // ... SANGUINOLOLU_11

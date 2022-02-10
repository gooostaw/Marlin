/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * FELIXprinters v2.0/3.0 (RAMPS v1.4) pin assignments
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "Felix 2.0+ supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "Felix 2.0+"

//
// Heaters / Fans
//
// Power outputs EFBF or EFBE
#define MOSFET_D_PIN                          7

#include "pins_RAMPS.h"

//
// Misc. Functions
//
#define SDPOWER_PIN                           1

#define PS_ON_PIN                            12

//
// LCD / Controller
//
#if IS_ULTRA_LCD && IS_NEWPANEL

  #define SD_DETECT_PIN                       6

#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
#undef SPINDLE_LASER_PWM_PIN                      // Definitions in pins_RAMPS.h are not valid with this board
#undef SPINDLE_LASER_ENA_PIN
#undef SPINDLE_DIR_PIN

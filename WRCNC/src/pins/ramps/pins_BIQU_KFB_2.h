/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * KFB 2.0 – Arduino Mega2560 with RAMPS v1.4 pin assignments
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "KFB 2.0 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "KFB 2.0"

//
// Heaters / Fans
//
// Power outputs BEEF or BEFF
#define MOSFET_D_PIN        7

#include "pins_RAMPS.h"

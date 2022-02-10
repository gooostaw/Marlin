/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Sainsmart 2-in-1 pin assignments
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "Sainsmart 2-in-1 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "Sainsmart"

//
// Heaters / Fans
//
#define MOSFET_A_PIN                           9  // E
#define MOSFET_B_PIN                           7  // F PART FAN in front of board next to Extruder heat
     // MOSFET_C_PIN                           8  // B
#define MOSFET_D_PIN                          10  // F / E

#include "pins_RAMPS.h"

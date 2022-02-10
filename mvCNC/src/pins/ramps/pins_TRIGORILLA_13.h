/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Arduino Mega with RAMPS v1.3 for Anycubic
 */

#define BOARD_INFO_NAME "Anycubic RAMPS 1.3"

#define MOSFET_B_PIN                         44

#define E1_STEP_PIN                          -1
#define E1_DIR_PIN                           -1
#define E1_ENABLE_PIN                        -1
#define E1_CS_PIN                            -1

#define FAN2_PIN                              9

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                     9
#endif

#include "pins_RAMPS_13.h" // ... RAMPS

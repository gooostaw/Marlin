/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * CREALITY v4.3.1 (STM32F103RE / STM32F103RC) board pin assignments
 */

#define BOARD_INFO_NAME      "Creality v4.3.1"
#define DEFAULT_MACHINE_NAME "Creality3D"

//
// Steppers
//
#if MB(CREALITY_V431, CREALITY_V431_A, CREALITY_V431_B)

  #define X_STEP_PIN                        PB8
  #define X_DIR_PIN                         PB7

  #define Y_STEP_PIN                        PC2
  #define Y_DIR_PIN                         PB9

#endif

#if MB(CREALITY_V431_B, CREALITY_V431_C)

  #define E0_STEP_PIN                       PB3
  #define E0_DIR_PIN                        PB4

#endif

#include "pins_CREALITY_V4.h"

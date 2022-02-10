/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * CREALITY v4.2.7 (STM32F103RE / STM32F103RC) board pin assignments
 */

#define BOARD_INFO_NAME      "Creality v4.2.7"
#define DEFAULT_MACHINE_NAME "Creality3D"

//
// Steppers
//
#define X_STEP_PIN                          PB9
#define X_DIR_PIN                           PC2
#define Y_STEP_PIN                          PB7

#define Y_DIR_PIN                           PB8
#define Z_STEP_PIN                          PB5
#define Z_DIR_PIN                           PB6

#define E0_STEP_PIN                         PB3
#define E0_DIR_PIN                          PB4

#include "pins_CREALITY_V4.h"

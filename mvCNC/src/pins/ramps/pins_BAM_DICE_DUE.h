/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * BAM&DICE Due (Arduino Mega) pin assignments
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "2PrintBeta Due supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "2PrintBeta Due"

//
// M3/M4/M5 - Spindle/Laser Control
//
#define SPINDLE_LASER_ENA_PIN                 66  // Pullup or pulldown!
#define SPINDLE_DIR_PIN                       67
#define SPINDLE_LASER_PWM_PIN                 44  // Hardware PWM

//
// Temperature Sensors
//
#define TEMP_0_PIN                             9  // Analog Input
#define TEMP_1_PIN                            11  // Analog Input

#include "pins_RAMPS.h"

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * MKS BASE v1.6 with A4982 stepper drivers and digital micro-stepping
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS BASE 1.6 only supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "MKS BASE 1.6"
#define MKS_BASE_VERSION                      16

//
// Servos
//
#define SERVO1_PIN                            12  // Digital 12 / Pin 25

//
// Omitted RAMPS pins
//
#ifndef SERVO2_PIN
  #define SERVO2_PIN                          -1
#endif
#ifndef SERVO3_PIN
  #define SERVO3_PIN                          -1
#endif
#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN                        -1
#endif
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                      -1
#endif
#ifndef PS_ON_PIN
  #define PS_ON_PIN                           -1
#endif

#include "pins_MKS_BASE_common.h" // ... RAMPS

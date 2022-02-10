/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * MKS BASE v1.5 with A4982 stepper drivers and digital micro-stepping
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS BASE 1.5 only supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "MKS BASE 1.5"
#define MKS_BASE_VERSION 15

#include "pins_MKS_BASE_common.h" // ... RAMPS

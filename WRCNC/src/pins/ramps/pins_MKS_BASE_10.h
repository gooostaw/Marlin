/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * MKS BASE 1.0 – Arduino Mega2560 with RAMPS v1.4 pin assignments
 *
 * Rev B - Override pin definitions for CASE_LIGHT and M3/M4/M5 spindle control
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS BASE 1.0 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "MKS BASE 1.0"
#define MKS_BASE_VERSION 10

#include "pins_MKS_BASE_common.h" // ... RAMPS

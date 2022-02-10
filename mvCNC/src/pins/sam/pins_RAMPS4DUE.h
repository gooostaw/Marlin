/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Arduino Mega or Due with RAMPS4DUE pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS4DUE_EFB (Hotend, Fan, Bed)
 *  RAMPS4DUE_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS4DUE_EFF (Hotend, Fan0, Fan1)
 *  RAMPS4DUE_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS4DUE_SF  (Spindle, Controller Fan)
 *
 *  Differences between
 *  RAMPS_14 | RAMPS4DUE
 *       A13 | A9/D63 (shares the same pin with AUX2_4PIN)
 *       A14 | A10/D64 (shares the same pin with AUX2_5PIN)
 *       A15 | NC
 */

#define ALLOW_SAM3X8E
#define BOARD_INFO_NAME "RAMPS4DUE"

//
// Temperature Sensors
//
#define TEMP_0_PIN          9   // Analog Input
#define TEMP_1_PIN         -1   // Analog Input
#define TEMP_BED_PIN       10   // Analog Input

#include "../ramps/pins_RAMPS.h"

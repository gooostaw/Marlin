/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Geeetech GT2560 Revision A+ board pin assignments
 */

#define BOARD_INFO_NAME "GT2560 Rev.A+"

#include "pins_GT2560_REV_A.h"

#if DISABLED(BLTOUCH)
  #define SERVO0_PIN  32
#endif

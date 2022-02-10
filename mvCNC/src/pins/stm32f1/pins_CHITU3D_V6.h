/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#define BOARD_INFO_NAME "Chitu3D V6"

#define Z2_ENABLE_PIN                       PF3
#define Z2_STEP_PIN                         PF5
#define Z2_DIR_PIN                          PF1

#ifndef FIL_RUNOUT2_PIN
  #define FIL_RUNOUT2_PIN                   PF13
#endif

#include "pins_CHITU3D_common.h"

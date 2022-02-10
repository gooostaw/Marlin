/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#if HOTENDS > 3 || E_STEPPERS > 3
  #error "BIGTREE SKR Pro V1.1 supports up to 3 hotends / E-steppers."
#endif

#define BOARD_INFO_NAME "BTT SKR Pro V1.1"

#include "pins_BTT_SKR_PRO_common.h"

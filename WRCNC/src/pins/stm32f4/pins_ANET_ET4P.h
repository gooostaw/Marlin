/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define BOARD_INFO_NAME "Anet ET4P 1.x"

//
// TMC2208 Configuration_adv defaults for Anet ET4P-MB_V1.x
//
#if !AXIS_DRIVER_TYPE_X(TMC2208_STANDALONE) || !AXIS_DRIVER_TYPE_Y(TMC2208_STANDALONE) || !AXIS_DRIVER_TYPE_Z(TMC2208_STANDALONE) || !AXIS_DRIVER_TYPE_E0(TMC2208_STANDALONE)
  #error "ANET_ET4P requires ([XYZ]|E0)_DRIVER_TYPE set to TMC2208_STANDALONE."
#endif

#include "pins_ANET_ET4.h"

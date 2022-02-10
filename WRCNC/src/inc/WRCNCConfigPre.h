/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifndef __WRCNC_FIRMWARE__
#define __WRCNC_FIRMWARE__
#endif

//
// Prefix header to acquire configurations
//
#include <stdint.h>

#ifndef __WRCNC_DEPS__
  #include "../HAL/platforms.h"
#endif

#include "../core/macros.h"
#include "../core/boards.h"
#include "../../Configuration.h"

#ifdef CUSTOM_VERSION_FILE
  #if __has_include(STRINGIFY(../../CUSTOM_VERSION_FILE))
    #include STRINGIFY(../../CUSTOM_VERSION_FILE)
  #endif
#endif

#include "Version.h"

#include "Conditionals_LCD.h"

#ifndef __WRCNC_DEPS__
  #include HAL_PATH(../HAL, inc/Conditionals_LCD.h)
#endif

#include "../core/drivers.h"
#include "../../Configuration_adv.h"

#include "Conditionals_adv.h"

#ifndef __WRCNC_DEPS__
  #include HAL_PATH(../HAL, inc/Conditionals_adv.h)
#endif

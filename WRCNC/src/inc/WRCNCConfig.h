/**
 * Webber Ranch CNC Firmware
*/
#pragma once

//
// Prefix header for all WRCNC sources
//

#include "WRCNCConfigPre.h"

#ifndef __WRCNC_DEPS__
  #include "../HAL/HAL.h"
#endif

#include "../pins/pins.h"

#ifndef __WRCNC_DEPS__
  #include HAL_PATH(../HAL, timers.h)
  #include HAL_PATH(../HAL, spi_pins.h)
#endif

#include "Conditionals_post.h"

#ifndef __WRCNC_DEPS__

  #include HAL_PATH(../HAL, inc/Conditionals_post.h)

  #include "../core/types.h"  // Ahead of sanity-checks

  #include "SanityCheck.h"
  #include HAL_PATH(../HAL, inc/SanityCheck.h)

  // Include all core headers
  #include "../core/language.h"
  #include "../core/utility.h"
  #include "../core/serial.h"

#endif

#include "../core/multi_language.h"

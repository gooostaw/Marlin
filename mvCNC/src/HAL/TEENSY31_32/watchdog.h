/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "HAL.h"

// Arduino Due core now has watchdog support

void watchdog_init();

inline void HAL_watchdog_refresh() {
  // Watchdog refresh sequence
  WDOG_REFRESH = 0xA602;
  WDOG_REFRESH = 0xB480;
}

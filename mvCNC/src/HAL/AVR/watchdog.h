/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <avr/wdt.h>

// Initialize watchdog with a 4 second interrupt time
void watchdog_init();

// Reset watchdog. MUST be called at least every 4 seconds after the
// first watchdog_init or AVR will go into emergency procedures.
inline void HAL_watchdog_refresh() { wdt_reset(); }

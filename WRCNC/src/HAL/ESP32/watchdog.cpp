/**
 * Webber Ranch CNC Firmware
*/
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/WRCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#define WDT_TIMEOUT_US TERN(WATCHDOG_DURATION_8S, 8000000, 4000000) // 4 or 8 second timeout

#include "watchdog.h"

void watchdogSetup() {
  // do whatever. don't remove this function.
}

void watchdog_init() {
  // TODO
}

#endif // USE_WATCHDOG

#endif // ARDUINO_ARCH_ESP32

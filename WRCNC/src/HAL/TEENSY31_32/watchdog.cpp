/**
 * Webber Ranch CNC Firmware
*/
#ifdef __MK20DX256__

#include "../../inc/WRCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#include "watchdog.h"

#define WDT_TIMEOUT_MS TERN(WATCHDOG_DURATION_8S, 8000, 4000) // 4 or 8 second timeout

void watchdog_init() {
  WDOG_TOVALH = 0;
  WDOG_TOVALL = WDT_TIMEOUT_MS;
  WDOG_STCTRLH = WDOG_STCTRLH_WDOGEN;
}

#endif // USE_WATCHDOG

#endif // __MK20DX256__

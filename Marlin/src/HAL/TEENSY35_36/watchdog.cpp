/**
 * Webber Ranch CNC Firmware
*/
#if defined(__MK64FX512__) || defined(__MK66FX1M0__)

#include "../../inc/MarlinConfig.h"

#if ENABLED(USE_WATCHDOG)

#include "watchdog.h"

#define WDT_TIMEOUT_MS TERN(WATCHDOG_DURATION_8S, 8000, 4000) // 4 or 8 second timeout

void watchdog_init() {
  WDOG_TOVALH = 0;
  WDOG_TOVALL = WDT_TIMEOUT_MS;
  WDOG_STCTRLH = WDOG_STCTRLH_WDOGEN;
}

#endif // USE_WATCHDOG

#endif // __MK64FX512__ || __MK66FX1M0__

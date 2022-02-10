/**
 * Webber Ranch CNC Firmware
*/
#ifdef __PLAT_LINUX__

#include "../../inc/WRCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#include "watchdog.h"

#define WDT_TIMEOUT_US TERN(WATCHDOG_DURATION_8S, 8000000, 4000000) // 4 or 8 second timeout

void watchdog_init() {}
void HAL_watchdog_refresh() {}

#endif

#endif // __PLAT_LINUX__

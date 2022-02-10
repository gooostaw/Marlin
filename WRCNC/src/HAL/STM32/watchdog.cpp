/**
 * Webber Ranch CNC Firmware
*/

#include "../platforms.h"

#ifdef HAL_STM32

#include "../../inc/WRCNCConfigPre.h"

#if ENABLED(USE_WATCHDOG)

#define WDT_TIMEOUT_US TERN(WATCHDOG_DURATION_8S, 8000000, 4000000) // 4 or 8 second timeout

#include "../../inc/WRCNCConfig.h"

#include "watchdog.h"
#include <IWatchdog.h>

void watchdog_init() {
  #if DISABLED(DISABLE_WATCHDOG_INIT)
    IWatchdog.begin(WDT_TIMEOUT_US);
  #endif
}

void HAL_watchdog_refresh() {
  IWatchdog.reload();
  #if DISABLED(PINS_DEBUGGING) && PIN_EXISTS(LED)
    TOGGLE(LED_PIN);  // heartbeat indicator
  #endif
}

#endif // USE_WATCHDOG
#endif // HAL_STM32

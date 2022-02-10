/**
 * Webber Ranch CNC Firmware
*/
#ifdef __IMXRT1062__

/**
 * HAL Watchdog for Teensy 4.0 (IMXRT1062DVL6A) / 4.1 (IMXRT1062DVJ6A)
 */

#include "../../inc/WRCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#include "watchdog.h"

#define WDT_TIMEOUT TERN(WATCHDOG_DURATION_8S, 8, 4) // 4 or 8 second timeout

constexpr uint8_t timeoutval = (WDT_TIMEOUT - 0.5f) / 0.5f;

void watchdog_init() {
  CCM_CCGR3 |= CCM_CCGR3_WDOG1(3);  // enable WDOG1 clocks
  WDOG1_WMCR = 0;                   // disable power down PDE
  WDOG1_WCR |= WDOG_WCR_SRS | WDOG_WCR_WT(timeoutval);
  WDOG1_WCR |= WDOG_WCR_WDE | WDOG_WCR_WDT | WDOG_WCR_SRE;
}

void HAL_watchdog_refresh() {
  // Watchdog refresh sequence
  WDOG1_WSR = 0x5555;
  WDOG1_WSR = 0xAAAA;
}

#endif // USE_WATCHDOG
#endif // __IMXRT1062__

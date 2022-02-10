/**
 * Modern Vintage CNC Firmware
*/

/**
 * HAL for stm32duino.com based on Libmaple and compatible (STM32F1)
 */

#ifdef __STM32F1__

#include "../../inc/mvCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#include <libmaple/iwdg.h>
#include "watchdog.h"

/**
 *  The watchdog clock is 40Khz. So for a 4s or 8s interval use a /256 preescaler and 625 or 1250 reload value (counts down to 0).
 */
#define STM32F1_WD_RELOAD TERN(WATCHDOG_DURATION_8S, 1250, 625) // 4 or 8 second timeout

void HAL_watchdog_refresh() {
  #if DISABLED(PINS_DEBUGGING) && PIN_EXISTS(LED)
    TOGGLE(LED_PIN);  // heartbeat indicator
  #endif
  iwdg_feed();
}

void watchdogSetup() {
  // do whatever. don't remove this function.
}

/**
 * @brief  Initialized the independent hardware watchdog.
 *
 * @return No return
 *
 * @details The watchdog clock is 40Khz. So for a 4s or 8s interval use a /256 preescaler and 625 or 1250 reload value (counts down to 0).
 */
void watchdog_init() {
  #if DISABLED(DISABLE_WATCHDOG_INIT)
    iwdg_init(IWDG_PRE_256, STM32F1_WD_RELOAD);
  #endif
}

#endif // USE_WATCHDOG
#endif // __STM32F1__

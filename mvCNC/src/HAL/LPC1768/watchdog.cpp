/**
 * Modern Vintage CNC Firmware
*/
#ifdef TARGET_LPC1768

#include "../../inc/mvCNCConfig.h"

#if ENABLED(USE_WATCHDOG)

#include <lpc17xx_wdt.h>
#include "watchdog.h"

#define WDT_TIMEOUT_US TERN(WATCHDOG_DURATION_8S, 8000000, 4000000) // 4 or 8 second timeout

void watchdog_init() {
  #if ENABLED(WATCHDOG_RESET_MANUAL)
    // We enable the watchdog timer, but only for the interrupt.

    // Configure WDT to only trigger an interrupt
    // Disable WDT interrupt (just in case, to avoid triggering it!)
    NVIC_DisableIRQ(WDT_IRQn);

    // We NEED memory barriers to ensure Interrupts are actually disabled!
    // ( https://dzone.com/articles/nvic-disabling-interrupts-on-arm-cortex-m-and-the )
    __DSB();
    __ISB();

    // Configure WDT to only trigger an interrupt
    // Initialize WDT with the given parameters
    WDT_Init(WDT_CLKSRC_IRC, WDT_MODE_INT_ONLY);

    // Configure and enable WDT interrupt.
    NVIC_ClearPendingIRQ(WDT_IRQn);
    NVIC_SetPriority(WDT_IRQn, 0); // Use highest priority, so we detect all kinds of lockups
    NVIC_EnableIRQ(WDT_IRQn);
  #else
    WDT_Init(WDT_CLKSRC_IRC, WDT_MODE_RESET);
  #endif
  WDT_Start(WDT_TIMEOUT_US);
}

void HAL_watchdog_refresh() {
  WDT_Feed();
  #if DISABLED(PINS_DEBUGGING) && PIN_EXISTS(LED)
    TOGGLE(LED_PIN);  // heartbeat indicator
  #endif
}

// Timeout state
bool watchdog_timed_out() { return TEST(WDT_ReadTimeOutFlag(), 0); }
void watchdog_clear_timeout_flag() { WDT_ClrTimeOutFlag(); }

#endif // USE_WATCHDOG
#endif // TARGET_LPC1768

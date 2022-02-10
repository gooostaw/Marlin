/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

  esp_err_t esp_task_wdt_reset();

#ifdef __cplusplus
  }
#endif

// Initialize watchdog with a 4 second interrupt time
void watchdog_init();

// Reset watchdog.
inline void HAL_watchdog_refresh() { esp_task_wdt_reset(); }

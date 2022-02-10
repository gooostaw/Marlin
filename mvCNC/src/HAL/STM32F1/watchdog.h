/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * HAL for stm32duino.com based on Libmaple and compatible (STM32F1)
 */

#include <libmaple/iwdg.h>

// Initialize watchdog with a 4 or 8 second countdown time
void watchdog_init();

// Reset watchdog. MUST be called every 4 or 8 seconds after the
// first watchdog_init or the STM32F1 will reset.
void HAL_watchdog_refresh();

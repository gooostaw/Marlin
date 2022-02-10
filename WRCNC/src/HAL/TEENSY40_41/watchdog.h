/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * HAL Watchdog for Teensy 4.0 (IMXRT1062DVL6A) / 4.1 (IMXRT1062DVJ6A)
 */

void watchdog_init();

void HAL_watchdog_refresh();

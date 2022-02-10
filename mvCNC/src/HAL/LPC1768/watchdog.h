/**
 * Modern Vintage CNC Firmware
*/
#pragma once

void watchdog_init();
void HAL_watchdog_refresh();

bool watchdog_timed_out();
void watchdog_clear_timeout_flag();

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../core/millis_t.h"

class HotendIdleProtection {
public:
  static void check();
private:
  static constexpr millis_t hp_interval = SEC_TO_MS(HOTEND_IDLE_TIMEOUT_SEC);
  static millis_t next_protect_ms;
  static void check_hotends(const millis_t &ms);
  static void check_e_motion(const millis_t &ms);
  static void timed_out();
};

extern HotendIdleProtection hotend_idle;

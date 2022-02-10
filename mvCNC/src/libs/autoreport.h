/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../inc/mvCNCConfig.h"

template <typename Helper>
struct AutoReporter {
  millis_t next_report_ms;
  uint8_t report_interval;
  #if HAS_MULTI_SERIAL
    SerialMask report_port_mask;
    AutoReporter() : report_port_mask(SerialMask::All) {}
  #endif

  inline void set_interval(uint8_t seconds, const uint8_t limit=60) {
    report_interval = _MIN(seconds, limit);
    next_report_ms = millis() + SEC_TO_MS(seconds);
  }

  inline void tick() {
    if (!report_interval) return;
    const millis_t ms = millis();
    if (ELAPSED(ms, next_report_ms)) {
      next_report_ms = ms + SEC_TO_MS(report_interval);
      PORT_REDIRECT(report_port_mask);
      Helper::report();
      PORT_RESTORE();
    }
  }
};

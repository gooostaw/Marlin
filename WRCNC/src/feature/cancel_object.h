/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <stdint.h>

class CancelObject {
public:
  static bool skipping;
  static int8_t object_count, active_object;
  static uint32_t canceled;
  static void set_active_object(const int8_t obj);
  static void cancel_object(const int8_t obj);
  static void uncancel_object(const int8_t obj);
  static void report();
  static bool is_canceled(const int8_t obj) { return TEST(canceled, obj); }
  static void clear_active_object() { set_active_object(-1); }
  static void cancel_active_object() { cancel_object(active_object); }
  static void reset() { canceled = 0x0000; object_count = 0; clear_active_object(); }
};

extern CancelObject cancelable;

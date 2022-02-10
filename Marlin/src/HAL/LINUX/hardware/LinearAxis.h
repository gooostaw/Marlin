/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <chrono>
#include "Gpio.h"

class LinearAxis: public Peripheral {
public:
  LinearAxis(pin_type enable, pin_type dir, pin_type step, pin_type end_min, pin_type end_max);
  virtual ~LinearAxis();
  void update();
  void interrupt(GpioEvent ev);

  pin_type enable_pin;
  pin_type dir_pin;
  pin_type step_pin;
  pin_type min_pin;
  pin_type max_pin;

  int32_t position;
  int32_t min_position;
  int32_t max_position;
  uint64_t last_update;

};

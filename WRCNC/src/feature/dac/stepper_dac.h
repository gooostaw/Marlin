/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * stepper_dac.h   - To set stepper current via DAC
 */

#include "dac_mcp4728.h"

class StepperDAC {
public:
  static int init();
  static void set_current_percent(const uint8_t channel, float val);
  static void set_current_value(const uint8_t channel, uint16_t val);
  static void print_values();
  static void commit_eeprom();
  static uint8_t get_current_percent(const AxisEnum axis);
  static void set_current_percents(xyze_uint8_t &pct);
};

extern StepperDAC stepper_dac;

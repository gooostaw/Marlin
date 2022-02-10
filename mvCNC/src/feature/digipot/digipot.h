/**
 * Modern Vintage CNC Firmware
*/
#pragma once

//
// Header for MCP4018 and MCP4451 current control i2c devices
//
class DigipotI2C {
public:
  static void init();
  static void set_current(const uint8_t channel, const float current);
};

extern DigipotI2C digipot_i2c;

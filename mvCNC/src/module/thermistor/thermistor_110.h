/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE_110 1

// Pt100 with 1k0 pullup
constexpr temp_entry_t temptable_110[] PROGMEM = {
  // only a few values are needed as the curve is very flat
  PtLine(  0, 100, 1000),
  PtLine( 50, 100, 1000),
  PtLine(100, 100, 1000),
  PtLine(150, 100, 1000),
  PtLine(200, 100, 1000),
  PtLine(250, 100, 1000),
  PtLine(300, 100, 1000)
};

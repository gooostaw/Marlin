/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE_1010 1

// Pt1000 with 1k0 pullup
constexpr temp_entry_t temptable_1010[] PROGMEM = {
  PtLine(  0, 1000, 1000),
  PtLine( 25, 1000, 1000),
  PtLine( 50, 1000, 1000),
  PtLine( 75, 1000, 1000),
  PtLine(100, 1000, 1000),
  PtLine(125, 1000, 1000),
  PtLine(150, 1000, 1000),
  PtLine(175, 1000, 1000),
  PtLine(200, 1000, 1000),
  PtLine(225, 1000, 1000),
  PtLine(250, 1000, 1000),
  PtLine(275, 1000, 1000),
  PtLine(300, 1000, 1000)
};

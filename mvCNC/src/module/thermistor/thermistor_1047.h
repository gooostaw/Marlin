/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE_1047 1

// Pt1000 with 4k7 pullup
constexpr temp_entry_t temptable_1047[] PROGMEM = {
  // only a few values are needed as the curve is very flat
  PtLine(  0, 1000, 4700),
  PtLine( 50, 1000, 4700),
  PtLine(100, 1000, 4700),
  PtLine(150, 1000, 4700),
  PtLine(200, 1000, 4700),
  PtLine(250, 1000, 4700),
  PtLine(300, 1000, 4700),
  PtLine(350, 1000, 4700),
  PtLine(400, 1000, 4700),
  PtLine(450, 1000, 4700),
  PtLine(500, 1000, 4700)
};

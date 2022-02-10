/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE_147 1

// Pt100 with 4k7 pullup
constexpr temp_entry_t temptable_147[] PROGMEM = {
  // only a few values are needed as the curve is very flat
  PtLine(  0, 100, 4700),
  PtLine( 50, 100, 4700),
  PtLine(100, 100, 4700),
  PtLine(150, 100, 4700),
  PtLine(200, 100, 4700),
  PtLine(250, 100, 4700),
  PtLine(300, 100, 4700)
};

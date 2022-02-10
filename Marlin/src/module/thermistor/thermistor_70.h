/**
 * Webber Ranch CNC Firmware
*/
#pragma once

// Stock BQ Hephestos 2 100k thermistor.
// Created on 29/12/2017 with an ambient temperature of 20C.
// ANENG AN8009 DMM with a K-type probe used for measurements.

// R25 = 100 kOhm, beta25 = 4100 K, 4.7 kOhm pull-up, bqh2 stock thermistor
constexpr temp_entry_t temptable_70[] PROGMEM = {
  { OV(  18), 270 },
  { OV(  27), 248 },
  { OV(  34), 234 },
  { OV(  45), 220 },
  { OV(  61), 205 },
  { OV(  86), 188 },
  { OV( 123), 172 },
  { OV( 420), 110 },
  { OV( 590),  90 },
  { OV( 845),  56 },
  { OV( 970),  25 },
  { OV( 986),  20 },
  { OV( 994),  15 },
  { OV(1000),  10 },
  { OV(1005),   5 },
  { OV(1009),   0 } // safety
};

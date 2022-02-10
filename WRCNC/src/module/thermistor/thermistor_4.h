/**
 * Webber Ranch CNC Firmware
*/
#pragma once

// R25 = 10 kOhm, beta25 = 3950 K, 4.7 kOhm pull-up, Generic 10k thermistor
constexpr temp_entry_t temptable_4[] PROGMEM = {
  { OV(   1), 430 },
  { OV(  54), 137 },
  { OV( 107), 107 },
  { OV( 160),  91 },
  { OV( 213),  80 },
  { OV( 266),  71 },
  { OV( 319),  64 },
  { OV( 372),  57 },
  { OV( 425),  51 },
  { OV( 478),  46 },
  { OV( 531),  41 },
  { OV( 584),  35 },
  { OV( 637),  30 },
  { OV( 690),  25 },
  { OV( 743),  20 },
  { OV( 796),  14 },
  { OV( 849),   7 },
  { OV( 902),   0 },
  { OV( 955), -11 },
  { OV(1008), -35 }
};

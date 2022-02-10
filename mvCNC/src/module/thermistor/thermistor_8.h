/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// R25 = 100 kOhm, beta25 = 3950 K, 10 kOhm pull-up, NTCS0603E3104FHT
constexpr temp_entry_t temptable_8[] PROGMEM = {
  { OV(   1), 704 },
  { OV(  54), 216 },
  { OV( 107), 175 },
  { OV( 160), 152 },
  { OV( 213), 137 },
  { OV( 266), 125 },
  { OV( 319), 115 },
  { OV( 372), 106 },
  { OV( 425),  99 },
  { OV( 478),  91 },
  { OV( 531),  85 },
  { OV( 584),  78 },
  { OV( 637),  71 },
  { OV( 690),  65 },
  { OV( 743),  58 },
  { OV( 796),  50 },
  { OV( 849),  42 },
  { OV( 902),  31 },
  { OV( 955),  17 },
  { OV(1008),   0 }
};

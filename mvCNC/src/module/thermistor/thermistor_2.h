/**
 * Modern Vintage CNC Firmware
*/
#pragma once

//
// R25 = 200 kOhm, beta25 = 4338 K, 4.7 kOhm pull-up, ATC Semitec 204GT-2
// Verified by linagee. Source: https://www.mouser.com/datasheet/2/362/semitec%20usa%20corporation_gtthermistor-1202937.pdf
// Calculated using 4.7kohm pullup, voltage divider math, and manufacturer provided temp/resistance
//
constexpr temp_entry_t temptable_2[] PROGMEM = {
  { OV(   1), 848 },
  { OV(  30), 300 }, // top rating 300C
  { OV(  34), 290 },
  { OV(  39), 280 },
  { OV(  46), 270 },
  { OV(  53), 260 },
  { OV(  63), 250 },
  { OV(  74), 240 },
  { OV(  87), 230 },
  { OV( 104), 220 },
  { OV( 124), 210 },
  { OV( 148), 200 },
  { OV( 176), 190 },
  { OV( 211), 180 },
  { OV( 252), 170 },
  { OV( 301), 160 },
  { OV( 357), 150 },
  { OV( 420), 140 },
  { OV( 489), 130 },
  { OV( 562), 120 },
  { OV( 636), 110 },
  { OV( 708), 100 },
  { OV( 775),  90 },
  { OV( 835),  80 },
  { OV( 884),  70 },
  { OV( 924),  60 },
  { OV( 955),  50 },
  { OV( 977),  40 },
  { OV( 993),  30 },
  { OV(1004),  20 },
  { OV(1012),  10 },
  { OV(1016),   0 }
};

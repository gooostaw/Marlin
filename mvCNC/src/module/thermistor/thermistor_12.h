/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// R25 = 100 kOhm, beta25 = 4700 K, 4.7 kOhm pull-up, (personal calibration for Makibox hot bed)
constexpr temp_entry_t temptable_12[] PROGMEM = {
  { OV(  35), 180 }, // top rating 180C
  { OV( 211), 140 },
  { OV( 233), 135 },
  { OV( 261), 130 },
  { OV( 290), 125 },
  { OV( 328), 120 },
  { OV( 362), 115 },
  { OV( 406), 110 },
  { OV( 446), 105 },
  { OV( 496), 100 },
  { OV( 539),  95 },
  { OV( 585),  90 },
  { OV( 629),  85 },
  { OV( 675),  80 },
  { OV( 718),  75 },
  { OV( 758),  70 },
  { OV( 793),  65 },
  { OV( 822),  60 },
  { OV( 841),  55 },
  { OV( 875),  50 },
  { OV( 899),  45 },
  { OV( 926),  40 },
  { OV( 946),  35 },
  { OV( 962),  30 },
  { OV( 977),  25 },
  { OV( 987),  20 },
  { OV( 995),  15 },
  { OV(1001),  10 },
  { OV(1010),   0 },
  { OV(1023), -40 }
};

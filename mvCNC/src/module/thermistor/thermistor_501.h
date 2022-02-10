/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// 100k Zonestar thermistor. Adjusted By Hally
constexpr temp_entry_t temptable_501[] PROGMEM = {
   { OV(   1), 713 },
   { OV(  14), 300 }, // Top rating 300C
   { OV(  16), 290 },
   { OV(  19), 280 },
   { OV(  23), 270 },
   { OV(  27), 260 },
   { OV(  31), 250 },
   { OV(  37), 240 },
   { OV(  47), 230 },
   { OV(  57), 220 },
   { OV(  68), 210 },
   { OV(  84), 200 },
   { OV( 100), 190 },
   { OV( 128), 180 },
   { OV( 155), 170 },
   { OV( 189), 160 },
   { OV( 230), 150 },
   { OV( 278), 140 },
   { OV( 336), 130 },
   { OV( 402), 120 },
   { OV( 476), 110 },
   { OV( 554), 100 },
   { OV( 635),  90 },
   { OV( 713),  80 },
   { OV( 784),  70 },
   { OV( 846),  60 },
   { OV( 897),  50 },
   { OV( 937),  40 },
   { OV( 966),  30 },
   { OV( 986),  20 },
   { OV(1000),  10 },
   { OV(1010),   0 }
};

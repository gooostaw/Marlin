/**
 * Webber Ranch CNC Firmware
*/
#pragma once

// Zonestar (Z8XM2) Heated Bed thermistor. Added By AvanOsch
// These are taken from the Zonestar settings in original Repetier firmware: Z8XM2_ZRIB_LCD12864_V51.zip
constexpr temp_entry_t temptable_503[] PROGMEM = {
   { OV(  12), 300 },
   { OV(  27), 270 },
   { OV(  47), 250 },
   { OV(  68), 230 },
   { OV(  99), 210 },
   { OV( 120), 200 },
   { OV( 141), 190 },
   { OV( 171), 180 },
   { OV( 201), 170 },
   { OV( 261), 160 },
   { OV( 321), 150 },
   { OV( 401), 140 },
   { OV( 451), 130 },
   { OV( 551), 120 },
   { OV( 596), 110 },
   { OV( 626), 105 },
   { OV( 666), 100 },
   { OV( 697), 90 },
   { OV( 717), 85 },
   { OV( 798), 69 },
   { OV( 819), 65 },
   { OV( 870), 55 },
   { OV( 891), 51 },
   { OV( 922), 39 },
   { OV( 968), 28 },
   { OV( 980), 23 },
   { OV( 991), 17 },
   { OV( 1001), 9 },
   { OV(1021), -27 },
   { OV(1023), -200}
};

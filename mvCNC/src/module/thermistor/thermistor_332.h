/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#define OVM(V) OV((V)*(0.327/0.327))

// R25 = 100 kOhm, beta25 = 4092 K, 4.7 kOhm pull-up, bed thermistor
constexpr temp_entry_t temptable_332[] PROGMEM = {
  { OVM( 268), 150 },
  { OVM( 293), 145 },
  { OVM( 320), 141 },
  { OVM( 379), 133 },
  { OVM( 445), 122 },
  { OVM( 516), 108 },
  { OVM( 591),  98 },
  { OVM( 665),  88 },
  { OVM( 737),  79 },
  { OVM( 801),  70 },
  { OVM( 857),  55 },
  { OVM( 903),  46 },
  { OVM( 939),  39 },
  { OVM( 954),  33 },
  { OVM( 966),  27 },
  { OVM( 977),  22 },
  { OVM( 999),  15 },
  { OVM(1004),   5 },
  { OVM(1008),   0 },
  { OVM(1012),  -5 },
  { OVM(1016), -10 },
  { OVM(1020), -15 }
};

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// User-defined table 2
// Dummy Thermistor table.. It will ALWAYS read a fixed value.
#ifndef DUMMY_THERMISTOR_999_VALUE
  #define DUMMY_THERMISTOR_999_VALUE 25
#endif

constexpr temp_entry_t temptable_999[] PROGMEM = {
  { OV(   1), DUMMY_THERMISTOR_999_VALUE },
  { OV(1023), DUMMY_THERMISTOR_999_VALUE }
};

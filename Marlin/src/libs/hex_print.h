/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <stdint.h>

//
// Utility functions to create and print hex strings as nybble, byte, and word.
//

constexpr char hex_nybble(const uint8_t n) {
  return (n & 0xF) + ((n & 0xF) < 10 ? '0' : 'A' - 10);
}
char* hex_byte(const uint8_t b);
char* hex_word(const uint16_t w);
char* hex_address(const void * const w);

void print_hex_nybble(const uint8_t n);
void print_hex_byte(const uint8_t b);
void print_hex_word(const uint16_t w);
void print_hex_address(const void * const w);
void print_hex_long(const uint32_t w, const char delimiter);

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../core/macros.h"

/**
 * Math helper functions for 32 bit CPUs
 */
static FORCE_INLINE uint32_t MultiU32X24toH32(uint32_t longIn1, uint32_t longIn2) {
  return ((uint64_t)longIn1 * longIn2 + 0x00800000) >> 24;
}

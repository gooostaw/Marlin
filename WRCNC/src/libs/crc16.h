/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <stdint.h>

void crc16(uint16_t *crc, const void * const data, uint16_t cnt);

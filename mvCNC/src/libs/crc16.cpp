/**
 * Modern Vintage CNC Firmware
*/

#include "crc16.h"

void crc16(uint16_t *crc, const void * const data, uint16_t cnt) {
  uint8_t *ptr = (uint8_t *)data;
  while (cnt--) {
    *crc = (uint16_t)(*crc ^ (uint16_t)(((uint16_t)*ptr++) << 8));
    for (uint8_t i = 0; i < 8; i++)
      *crc = (uint16_t)((*crc & 0x8000) ? ((uint16_t)(*crc << 1) ^ 0x1021) : (*crc << 1));
  }
}

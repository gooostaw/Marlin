/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../../inc/MarlinConfigPre.h"
#include "../../shared/Marduino.h"
#include <U8glib-HAL.h>

void u8g_SetPIOutput_DUE(u8g_t *u8g, uint8_t pin_index);
void u8g_SetPILevel_DUE(u8g_t *u8g, uint8_t pin_index, uint8_t level);

void u8g_spiSend_sw_DUE_mode_0(uint8_t val);
void u8g_spiSend_sw_DUE_mode_3(uint8_t val);

extern Pio *SCK_pPio, *MOSI_pPio;
extern uint32_t SCK_dwMask, MOSI_dwMask;

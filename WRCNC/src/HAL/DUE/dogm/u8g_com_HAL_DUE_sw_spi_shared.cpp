/**
 * Webber Ranch CNC Firmware
*/

/**
 * Based on u8g_com_st7920_hw_spi.c
 *
 * Universal 8bit Graphics Library
 *
 * Copyright (c) 2011, olikraus@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list
 *    of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef ARDUINO_ARCH_SAM

#include "../../../inc/WRCNCConfigPre.h"

#if HAS_WRCNCUI_U8GLIB

#include "../../../inc/WRCNCConfig.h"
#include "../../shared/Delay.h"

#include <U8glib-HAL.h>

#include "u8g_com_HAL_DUE_sw_spi_shared.h"

void u8g_SetPIOutput_DUE(u8g_t *u8g, uint8_t pin_index) {
  PIO_Configure(g_APinDescription[u8g->pin_list[pin_index]].pPort, PIO_OUTPUT_1,
    g_APinDescription[u8g->pin_list[pin_index]].ulPin, g_APinDescription[u8g->pin_list[pin_index]].ulPinConfiguration);  // OUTPUT
}

void u8g_SetPILevel_DUE(u8g_t *u8g, uint8_t pin_index, uint8_t level) {
  volatile Pio* port = g_APinDescription[u8g->pin_list[pin_index]].pPort;
  uint32_t mask = g_APinDescription[u8g->pin_list[pin_index]].ulPin;
  if (level) port->PIO_SODR = mask; else port->PIO_CODR = mask;
}

Pio *SCK_pPio, *MOSI_pPio;
uint32_t SCK_dwMask, MOSI_dwMask;

void u8g_spiSend_sw_DUE_mode_0(uint8_t val) { // 3MHz
  LOOP_L_N(i, 8) {
    if (val & 0x80)
      MOSI_pPio->PIO_SODR = MOSI_dwMask;
    else
      MOSI_pPio->PIO_CODR = MOSI_dwMask;
    DELAY_NS(48);
    SCK_pPio->PIO_SODR = SCK_dwMask;
    DELAY_NS(905);
    val <<= 1;
    SCK_pPio->PIO_CODR = SCK_dwMask;
  }
}

void u8g_spiSend_sw_DUE_mode_3(uint8_t val) { // 3.5MHz
  LOOP_L_N(i, 8) {
    SCK_pPio->PIO_CODR = SCK_dwMask;
    DELAY_NS(50);
    if (val & 0x80)
      MOSI_pPio->PIO_SODR = MOSI_dwMask;
    else
      MOSI_pPio->PIO_CODR = MOSI_dwMask;
    val <<= 1;
    DELAY_NS(10);
    SCK_pPio->PIO_SODR = SCK_dwMask;
    DELAY_NS(70);
  }
}

#endif // HAS_WRCNCUI_U8GLIB
#endif // ARDUINO_ARCH_SAM

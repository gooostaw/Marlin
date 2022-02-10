/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "pins_BTT_SKR_MINI_E3_common.h"

#define BOARD_INFO_NAME "BTT SKR Mini E3 V1.2"

#ifndef NEOPIXEL_PIN
  #define NEOPIXEL_PIN                      PC7   // LED driving pin
#endif

/**
 * TMC2208/TMC2209 stepper drivers
 */
#if HAS_TMC_UART
  #define X_SERIAL_TX_PIN                   PB15
  #define X_SERIAL_RX_PIN        X_SERIAL_TX_PIN

  #define Y_SERIAL_TX_PIN                   PC6
  #define Y_SERIAL_RX_PIN        Y_SERIAL_TX_PIN

  #define Z_SERIAL_TX_PIN                   PC10
  #define Z_SERIAL_RX_PIN        Z_SERIAL_TX_PIN

  #define E0_SERIAL_TX_PIN                  PC11
  #define E0_SERIAL_RX_PIN      E0_SERIAL_TX_PIN

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif

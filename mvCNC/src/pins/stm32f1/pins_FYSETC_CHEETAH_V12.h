/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "env_validate.h"

#include "pins_FYSETC_CHEETAH.h"

#undef X_HARDWARE_SERIAL
#undef Y_HARDWARE_SERIAL
#undef Z_HARDWARE_SERIAL
#undef E0_HARDWARE_SERIAL

#undef RGB_LED_R_PIN
#undef RGB_LED_G_PIN
#undef RGB_LED_B_PIN

#define FAN1_PIN                            PB0   // Fan1

#if HAS_TMC_UART

  /**
   * TMC2208/TMC2209 stepper drivers
   */

  #define X_SERIAL_TX_PIN                   PA11
  #define X_SERIAL_RX_PIN                   PA12

  #define Y_SERIAL_TX_PIN                   PB6
  #define Y_SERIAL_RX_PIN                   PB7

  #define Z_SERIAL_TX_PIN                   PB10
  #define Z_SERIAL_RX_PIN                   PB11

  #define E0_SERIAL_TX_PIN                  PA2
  #define E0_SERIAL_RX_PIN                  PA3

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif

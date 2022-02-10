/**
 * Modern Vintage CNC Firmware
*/
#pragma once

//
// FYSETC F6 v1.4 pin assignments
//

#define BOARD_INFO_NAME "FYSETC F6 1.4"

#define Z_MAX_PIN                              2

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   */
  #define X_SERIAL_TX_PIN                     71
  #define X_SERIAL_RX_PIN                     72

  #define Y_SERIAL_TX_PIN                     78
  #define Y_SERIAL_RX_PIN                     73

  #define Z_SERIAL_TX_PIN                     79
  #define Z_SERIAL_RX_PIN                     75

  #define E0_SERIAL_TX_PIN                    81
  #define E0_SERIAL_RX_PIN                    77

  #define E1_SERIAL_TX_PIN                    80
  #define E1_SERIAL_RX_PIN                    76

  #define E2_SERIAL_TX_PIN                    82
  #define E2_SERIAL_RX_PIN                    62
#endif

#include "pins_FYSETC_F6_13.h"

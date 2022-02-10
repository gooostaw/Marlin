/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * MKS SGen pin assignments
 *
 * Pins diagram:
 * https://github.com/makerbase-mks/MKS-SGen/blob/master/Hardware/MKS%20SGEN%20V1.0_001/MKS%20SGEN%20V1.0_001%20PIN.pdf
 */

#define BOARD_INFO_NAME   "MKS SGen"
#define BOARD_WEBSITE_URL "github.com/makerbase-mks/MKS-SGEN"

#define REQUIRE_LPC1769
#include "../lpc1768/pins_MKS_SBASE.h"

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   */
  #define X_SERIAL_TX_PIN                  P1_22  // J8-2
  #define X_SERIAL_RX_PIN        X_SERIAL_TX_PIN

  #define Y_SERIAL_TX_PIN                  P1_23  // J8-3
  #define Y_SERIAL_RX_PIN        Y_SERIAL_TX_PIN

  #define Z_SERIAL_TX_PIN                  P2_12  // J8-4
  #define Z_SERIAL_RX_PIN        Z_SERIAL_TX_PIN

  #define E0_SERIAL_TX_PIN                 P2_11  // J8-5
  #define E0_SERIAL_RX_PIN      E0_SERIAL_TX_PIN

  #define E1_SERIAL_TX_PIN                 P4_28  // J8-6
  #define E1_SERIAL_RX_PIN      E1_SERIAL_TX_PIN

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
#endif

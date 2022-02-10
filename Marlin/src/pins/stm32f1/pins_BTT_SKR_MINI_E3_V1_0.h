/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "pins_BTT_SKR_MINI_E3_common.h"

#define BOARD_INFO_NAME "BTT SKR Mini E3 V1.0"

/**
 * TMC220x stepper drivers
 * Hardware serial communication ports.
 */
#if HAS_TMC_UART
  #define X_HARDWARE_SERIAL  MSerial4
  #define Y_HARDWARE_SERIAL  MSerial4
  #define Z_HARDWARE_SERIAL  MSerial4
  #define E0_HARDWARE_SERIAL MSerial4

  // Default TMC slave addresses
  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS  0
  #endif
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS  2
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS  1
  #endif
  #ifndef E0_SLAVE_ADDRESS
    #define E0_SLAVE_ADDRESS 3
  #endif
#endif

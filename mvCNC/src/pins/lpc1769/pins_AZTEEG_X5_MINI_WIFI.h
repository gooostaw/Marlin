/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Azteeg X5 MINI WIFI pin assignments
 */

#include "env_validate.h"

#define BOARD_INFO_NAME "Azteeg X5 MINI WIFI"

//
// DIGIPOT slave addresses
//
#ifndef DIGIPOT_I2C_ADDRESS_A
  #define DIGIPOT_I2C_ADDRESS_A 0x58   // shifted slave address for first DIGIPOT (0x58 <- 0x2C << 1)
#endif
#ifndef DIGIPOT_I2C_ADDRESS_B
  #define DIGIPOT_I2C_ADDRESS_B 0x5C   // shifted slave address for second DIGIPOT (0x5C <- 0x2E << 1)
#endif

#include "pins_AZTEEG_X5_MINI.h"

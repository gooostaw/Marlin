/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * HAL_LPC1768/include/i2c_util.h
 */

#include "../../../inc/mvCNCConfigPre.h"

#ifndef I2C_MASTER_ID
  #define I2C_MASTER_ID 1
#endif

#if I2C_MASTER_ID == 0
  #define I2CDEV_M LPC_I2C0
#elif I2C_MASTER_ID == 1
  #define I2CDEV_M LPC_I2C1
#elif I2C_MASTER_ID == 2
  #define I2CDEV_M LPC_I2C2
#else
  #error "Master I2C device not defined!"
#endif

#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_libcfg_default.h>

#ifdef __cplusplus
  extern "C" {
#endif

void configure_i2c(const uint8_t clock_option);

#ifdef __cplusplus
  }
#endif

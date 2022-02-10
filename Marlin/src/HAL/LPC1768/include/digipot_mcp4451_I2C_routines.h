/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * digipot_mcp4451_I2C_routines.h
 * Adapted from https://www-users.cs.york.ac.uk/~pcc/MCP/HAPR-Course-web/CMSIS/examples/html/master_8c_source.html
 */

#ifdef __cplusplus
  extern "C" {
#endif

#include <lpc17xx_i2c.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_libcfg_default.h>
#include "i2c_util.h"

uint8_t digipot_mcp4451_start(uint8_t sla);
uint8_t digipot_mcp4451_send_byte(uint8_t data);

#ifdef __cplusplus
  }
#endif

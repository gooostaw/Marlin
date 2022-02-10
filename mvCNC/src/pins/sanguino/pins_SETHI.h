/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Sethi 3D_1 pin assignments - www.sethi3d.com.br
 */

/**
 * Rev B    26 DEC 2016
 *
 * added pointer to a current Arduino IDE extension
 *    this assumes that this board uses the Sanguino pin map
 */

/**
 * A useable Arduino IDE extension (board manager) can be found at
 * https://github.com/Lauszus/Sanguino
 *
 * This extension has been tested on Arduino 1.6.12 & 1.8.0
 *
 * Here's the JSON path:
 * https://raw.githubusercontent.com/Lauszus/Sanguino/master/package_lauszus_sanguino_index.json
 *
 * When installing select 1.0.2
 *
 * Installation instructions can be found at https://learn.sparkfun.com/pages/CustomBoardsArduino
 * Just use the above JSON URL instead of Sparkfun's JSON.
 *
 * Once installed select the Sanguino board and then select the CPU.
 */

#define ALLOW_MEGA644
#include "env_validate.h"

#define BOARD_INFO_NAME "Sethi 3D_1"

#ifndef GEN7_VERSION
  #define GEN7_VERSION                        12  // v1.x
#endif

//
// Limit Switches
//
#define X_STOP_PIN                             2
#define Y_STOP_PIN                             0
#define Z_MIN_PIN                              1
#define Z_MAX_PIN                              0

//
// Steppers
//
#define X_STEP_PIN                            19
#define X_DIR_PIN                             18
#define X_ENABLE_PIN                          24

#define Y_STEP_PIN                            23
#define Y_DIR_PIN                             22
#define Y_ENABLE_PIN                          24

#define Z_STEP_PIN                            26
#define Z_DIR_PIN                             25
#define Z_ENABLE_PIN                          24

#define E0_STEP_PIN                           28
#define E0_DIR_PIN                            27
#define E0_ENABLE_PIN                         24

//
// Temperature Sensors
//
#define TEMP_0_PIN                             1  // Analog Input
#define TEMP_BED_PIN                           2  // Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN                           4
#define HEATER_BED_PIN                         3

#ifndef FAN_PIN
  #if GEN7_VERSION >= 13
    // Gen7 v1.3 removed the fan pin
    #define FAN_PIN                           -1
  #else
    #define FAN_PIN                           31
  #endif
#endif

//
// Misc. Functions
//
#define PS_ON_PIN                             15

// All these generations of Gen7 supply thermistor power
// via PS_ON, so ignore bad thermistor readings
//#define BOGUS_TEMPERATURE_GRACE_PERIOD     2000

// our pin for debugging.
#define DEBUG_PIN                              0

// our RS485 pins
#define TX_ENABLE_PIN                         12
#define RX_ENABLE_PIN                         13

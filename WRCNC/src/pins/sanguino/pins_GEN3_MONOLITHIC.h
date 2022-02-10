/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Gen3 Monolithic Electronics pin assignments
 */

/**
 * Rev B    26 DEC 2016
 *
 * added pointer to a current Arduino IDE extension
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

#define REQUIRE_MEGA644P
#include "env_validate.h"

#define BOARD_INFO_NAME "Gen3 Monolithic"
#define DEBUG_PIN                              0

//
// Limit Switches
//
#define X_STOP_PIN                            20
#define Y_STOP_PIN                            25
#define Z_STOP_PIN                            30

//
// Steppers
//
#define X_STEP_PIN                            15
#define X_DIR_PIN                             18
#define X_ENABLE_PIN                          24  // actually uses Y_enable_pin

#define Y_STEP_PIN                            23
#define Y_DIR_PIN                             22
#define Y_ENABLE_PIN                          24  // shared with X_enable_pin

#define Z_STEP_PIN                            27
#define Z_DIR_PIN                             28
#define Z_ENABLE_PIN                          29

#define E0_STEP_PIN                           12
#define E0_DIR_PIN                            17
#define E0_ENABLE_PIN                          3

//
// Temperature Sensors
//
#define TEMP_0_PIN                             0  // Analog Input

//
// Heaters
//
#define HEATER_0_PIN                          16

//
// Misc. Functions
//
#define PS_ON_PIN                             14  // Alex, does this work on the card?

// Alex extras from Gen3+

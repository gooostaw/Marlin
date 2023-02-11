/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Cheap CNC (ESP32) pin assignments
 */

#include "env_validate.h"

#define BOARD_INFO_NAME "Cheap CNC"

//
// I2S (steppers & other output-only pins)
//
// #define I2S_STEPPER_STREAM
#if ENABLED(I2S_STEPPER_STREAM)
    #define I2S_WS 25
    #define I2S_BCK 26
    #define I2S_DATA 27
#endif

// Spindle

#define SPINDLE_LASER_ENA_PIN 23

//
// Limit Switches
//
#define X_MIN_PIN 18
#define Y_MIN_PIN NULL
#define Y2_MIN_PIN NULL
#define Z_MIN_PIN NULL

//
// Steppers
//
#define X_STEP_PIN 2
#define X_DIR_PIN 4
#define X_ENABLE_PIN NULL
// #define X_CS_PIN                             0

#define Y_STEP_PIN NULL
#define Y_DIR_PIN NULL
#define Y_ENABLE_PIN NULL
// #define Y_CS_PIN                            13

#define Y2_STEP_PIN NULL
#define Y2_DIR_PIN NULL
#define Y2_ENABLE_PIN NULL

#define Z_STEP_PIN NULL
#define Z_DIR_PIN NULL
#define Z_ENABLE_PIN NULL
// #define Z_CS_PIN                             5  // SS_PIN

// #define E0_STEP_PIN                       137
// #define E0_DIR_PIN                        138
// #define E0_ENABLE_PIN                     139
// #define E0_CS_PIN                           21

//
// Temperature Sensors
//
// #define TEMP_0_PIN                            36  // Analog Input
// #define TEMP_BED_PIN                          39  // Analog Input

//
// Heaters / Fans
//
// #define HEATER_0_PIN                           2
// #define FAN_PIN                               13
// #define HEATER_BED_PIN                         4

// SPI
// #define SDSS                                   5

#if HAS_TMC_UART
  //
  // TMC2209 stepper drivers
  //

  //
  // Hardware serial 1
  //
  #define X_HARDWARE_SERIAL              Serial1
  #define Y_HARDWARE_SERIAL              Serial1
  #define Y2_HARDWARE_SERIAL             Serial1
  #define Z_HARDWARE_SERIAL              Serial1
//   #define E0_HARDWARE_SERIAL             Serial1

  #define TMC_BAUD_RATE 250000

    // Default TMC slave addresses
  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS  0
  #endif
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS  1
  #endif
  #ifndef Y2_SLAVE_ADDRESS
    #define Y2_SLAVE_ADDRESS  3
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS  2
  #endif
//   #ifndef E0_SLAVE_ADDRESS
//     #define E0_SLAVE_ADDRESS 3
//   #endif

#endif

#ifndef HARDWARE_SERIAL1_RX
  #define HARDWARE_SERIAL1_RX                 16
#endif
#ifndef HARDWARE_SERIAL1_TX
  #define HARDWARE_SERIAL1_TX                 17
#endif
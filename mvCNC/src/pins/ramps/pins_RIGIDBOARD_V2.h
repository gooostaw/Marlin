/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * RIGIDBOARD V2 Arduino Mega with RAMPS v1.4 pin assignments
 */

#define BOARD_INFO_NAME "RigidBoard V2"

#include "pins_RIGIDBOARD.h" // ... RAMPS

//
// Steppers
//

// I2C based DAC like on the Printrboard REVF
#define HAS_MOTOR_CURRENT_DAC 1

// Channels available for DAC, For Rigidboard there are 4
#define DAC_STEPPER_ORDER { 0, 1, 2, 3 }

#define DAC_STEPPER_SENSE    0.05   // sense resistors on rigidboard stepper chips are .05 value
#define DAC_STEPPER_ADDRESS                   0
#define DAC_STEPPER_MAX                     4096  // was 5000 but max allowable value is actually 4096
#define DAC_STEPPER_VREF                      1   // internal Vref, gain 2x = 4.096V
#define DAC_STEPPER_GAIN                      1   // value of 1 here sets gain of 2
#define DAC_DISABLE_PIN                      42   // set low to enable DAC
#define DAC_OR_ADDRESS 0x01

#ifndef DAC_MOTOR_CURRENT_DEFAULT
  #define DAC_MOTOR_CURRENT_DEFAULT { 70, 80, 90, 80 } // Default drive percent - X, Y, Z, E axis
#endif

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * BIQU Tango pin assignments
 */

#define BOARD_INFO_NAME "Tango"

#define FAN_PIN                                8
#define FAN1_PIN                              -1

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                      7
#endif

#ifndef TEMP_0_PIN
  #if TEMP_SENSOR_0 == -1
    #define TEMP_0_PIN                        10  // Analog Input (connector *K1* on Tango thermocouple ADD ON is used)
  #else
    #define TEMP_0_PIN                        15  // Analog Input (default connector for thermistor *T0* on rumba board is used)
  #endif
#endif

#ifndef TEMP_1_PIN
  #if TEMP_SENSOR_1 == -1
    #define TEMP_1_PIN                         9  // Analog Input (connector *K2* on Tango thermocouple ADD ON is used)
  #else
    #define TEMP_1_PIN                        14  // Analog Input (default connector for thermistor *T1* on rumba board is used)
  #endif
#endif

#include "pins_RUMBA.h"

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * AZTEEG_X3 Arduino Mega with RAMPS v1.4 pin assignments
 */

#define REQUIRE_MEGA2560
#include "env_validate.h"

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "Azteeg X3 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#if ENABLED(CASE_LIGHT_ENABLE) && !PIN_EXISTS(CASE_LIGHT)
  #define CASE_LIGHT_PIN                       6  // Define before RAMPS pins include
#endif
#define BOARD_INFO_NAME "Azteeg X3"

//
// Servos
//
#define SERVO0_PIN                            44  // SERVO1 port
#define SERVO1_PIN                            55  // SERVO2 port

#include "pins_RAMPS_13.h" // ... RAMPS

//
// LCD / Controller
//
#undef STAT_LED_RED_PIN
#undef STAT_LED_BLUE_PIN

#if ANY(VIKI2, miniVIKI)

  #undef DOGLCD_A0
  #undef DOGLCD_CS
  #undef BTN_ENC
  #define DOGLCD_A0                           31
  #define DOGLCD_CS                           32
  #define BTN_ENC                             12

  #define STAT_LED_RED_PIN                    64
  #define STAT_LED_BLUE_PIN                   63

#else

  #define STAT_LED_RED_PIN                     6
  #define STAT_LED_BLUE_PIN                   11

#endif

//
// Misc
//
#if ENABLED(CASE_LIGHT_ENABLE) && PINS_EXIST(CASE_LIGHT, STAT_LED_RED) && STAT_LED_RED_PIN == CASE_LIGHT_PIN
  #undef STAT_LED_RED_PIN
#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
#undef SPINDLE_LASER_PWM_PIN                      // Definitions in pins_RAMPS.h are no good with the AzteegX3 board
#undef SPINDLE_LASER_ENA_PIN
#undef SPINDLE_DIR_PIN

#if HAS_CUTTER
  #undef SDA                                      // use EXP3 header
  #undef SCL
  #if SERVO0_PIN == 7
    #undef SERVO0_PIN
    #define SERVO0_PIN                        11
  #endif
  #define SPINDLE_LASER_PWM_PIN                7  // Hardware PWM
  #define SPINDLE_LASER_ENA_PIN               20  // Pullup!
  #define SPINDLE_DIR_PIN                     21
#endif

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Test TEENSY35_36 specific configuration values for errors at compile-time.
 */

#if ENABLED(EMERGENCY_PARSER)
  #error "EMERGENCY_PARSER is not yet implemented for Teensy 3.5/3.6. Disable EMERGENCY_PARSER to continue."
#endif

#if ENABLED(FAST_PWM_FAN) || SPINDLE_LASER_FREQUENCY
  #error "Features requiring Hardware PWM (FAST_PWM_FAN, SPINDLE_LASER_FREQUENCY) are not yet supported on Teensy 3.5/3.6."
#endif

#if HAS_TMC_SW_SERIAL
  #error "TMC220x Software Serial is not supported on Teensy 3.5/3.6."
#endif

#if ENABLED(POSTMORTEM_DEBUGGING)
  #error "POSTMORTEM_DEBUGGING is not yet supported on Teensy 3.5/3.6."
#endif

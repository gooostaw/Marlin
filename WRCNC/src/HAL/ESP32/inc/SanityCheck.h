/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#if ENABLED(EMERGENCY_PARSER)
  #error "EMERGENCY_PARSER is not yet implemented for ESP32. Disable EMERGENCY_PARSER to continue."
#endif

#if ENABLED(FAST_PWM_FAN) || SPINDLE_LASER_FREQUENCY
  #error "Features requiring Hardware PWM (FAST_PWM_FAN, SPINDLE_LASER_FREQUENCY) are not yet supported on ESP32."
#endif

#if HAS_TMC_SW_SERIAL
  #error "TMC220x Software Serial is not supported on ESP32."
#endif

#if BOTH(WIFISUPPORT, ESP3D_WIFISUPPORT)
  #error "Only enable one WiFi option, either WIFISUPPORT or ESP3D_WIFISUPPORT."
#endif

#if ENABLED(POSTMORTEM_DEBUGGING)
  #error "POSTMORTEM_DEBUGGING is not yet supported on ESP32."
#endif

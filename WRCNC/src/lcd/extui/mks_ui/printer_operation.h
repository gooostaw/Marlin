/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

#define MIN_FILE_PRINTED   100 //5000

void cnc_state_polling();
void filament_pin_setup();
void filament_check();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

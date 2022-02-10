/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_gcode(bool clear = false);
void lv_clear_gcode();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

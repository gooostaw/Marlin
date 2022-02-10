/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_filament_change();
void lv_clear_filament_change();
void disp_filament_type();
void disp_filament_temp();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_baby_stepping();
void lv_clear_baby_stepping();
void disp_baby_step_dist();
void disp_z_offset_value();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

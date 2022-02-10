/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_move_motor();
void lv_clear_move_motor();
void disp_move_dist();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

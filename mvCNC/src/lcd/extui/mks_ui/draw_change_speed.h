/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

#define MIN_EXT_SPEED_PERCENT    10
#define MAX_EXT_SPEED_PERCENT   999

void lv_draw_change_speed();
void lv_clear_change_speed();
void disp_speed_step();
void disp_print_speed();
void disp_speed_type();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

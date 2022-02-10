/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_extrusion();
void lv_clear_extrusion();
void disp_ext_type();
void disp_ext_step();
void disp_ext_speed();
void disp_hotend_temp();
void disp_extru_amount();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

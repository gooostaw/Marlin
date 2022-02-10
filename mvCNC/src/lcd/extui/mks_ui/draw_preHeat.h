/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_preHeat();
void lv_clear_preHeat();
void disp_temp_type();
void disp_step_heat();
void disp_desire_temp();
void disp_ext_heart();
void disp_add_dec();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_ready_print();
void mks_disp_test();
void disp_Limit_ok();
void disp_Limit_error();
void disp_det_error();
void disp_det_ok();
void lv_clear_ready_print();
void lv_temp_refr();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

#ifndef PGM_P
  #define PGM_P const char *
#endif

void lv_draw_error_message(FSTR_P const fmsg);
void lv_clear_error_message();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

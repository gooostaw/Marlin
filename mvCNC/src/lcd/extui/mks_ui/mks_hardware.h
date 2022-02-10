/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfigPre.h"

#include <lvgl.h>

// Functions for MKS_TEST
#if BOTH(MKS_TEST, SDSUPPORT)
  void mks_hardware_test();
  void mks_test_get();
  void mks_gpio_test();
  extern uint8_t mks_test_flag;
#else
  #define mks_test_flag 0
#endif

// String display and assets
void disp_string(uint16_t x, uint16_t y, const char * cstr, uint16_t charColor, uint16_t bkColor);
void disp_string(uint16_t x, uint16_t y, FSTR_P const fstr, uint16_t charColor, uint16_t bkColor);
void disp_assets_update();
void disp_assets_update_progress(FSTR_P const msg);

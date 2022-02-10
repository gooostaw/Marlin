/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

#define WIFI_AP_TEXT  "AP"
#define WIFI_STA_TEXT "STA"

void lv_draw_wifi_settings();
void lv_clear_wifi_settings();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

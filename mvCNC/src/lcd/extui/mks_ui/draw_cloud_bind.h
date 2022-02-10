/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_cloud_bind();
void lv_clear_cloud_bind();
void disp_bind_state();
void refresh_bind_ui();
void display_qrcode(uint8_t *qrcode_data);
void cloud_unbind();

#ifdef __cplusplus
  }
#endif

/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_TFT_LVGL_UI

#include <lv_conf.h>
#include "tft_lvgl_configuration.h"

#if ENABLED(MKS_WIFI_MODULE)

#include "draw_ui.h"

static lv_obj_t *scr;

TIPS_TYPE wifi_tips_type;
TIPS_DISP tips_disp;
tips_menu_def tips_menu;

void lv_draw_wifi_tips() {
  static lv_obj_t *text_tips, *wifi_name;

  scr = lv_screen_create(WIFI_TIPS_UI, "");

  wifi_name = lv_label_create(scr, (const char *)wifi_list.wifiName[wifi_list.nameIndex]);
  lv_obj_align(wifi_name, nullptr, LV_ALIGN_CENTER, 0, -20);

  text_tips = lv_label_create_empty(scr);
  if (wifi_tips_type == TIPS_TYPE_JOINING) {
    lv_label_set_text(text_tips, tips_menu.joining);
    lv_obj_align(text_tips, nullptr, LV_ALIGN_CENTER, 0, -60);
  }
  else if (wifi_tips_type == TIPS_TYPE_TAILED_JOIN) {
    lv_label_set_text(text_tips, tips_menu.failedJoin);
    lv_obj_align(text_tips, nullptr, LV_ALIGN_CENTER, 0, -60);
  }
  else if (wifi_tips_type == TIPS_TYPE_WIFI_CONECTED) {
    lv_label_set_text(text_tips, tips_menu.wifiConected);
    lv_obj_align(text_tips, nullptr, LV_ALIGN_CENTER, 0, -60);
  }

  tips_disp.timer = TIPS_TIMER_START;
  tips_disp.timer_count = 0;
}

void lv_clear_wifi_tips() { lv_obj_del(scr); }

#endif // MKS_WIFI_MODULE
#endif // HAS_TFT_LVGL_UI

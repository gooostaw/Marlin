/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/WRCNCConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../inc/WRCNCConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr;
static lv_obj_t *fw_type, *board;

enum { ID_A_RETURN = 1 };

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  switch (obj->mks_obj_id) {
    case ID_A_RETURN:
      goto_previous_ui();
      break;
  }
}

void lv_draw_about() {
  scr = lv_screen_create(ABOUT_UI);
  lv_big_button_create(scr, "F:/bmp_return.bin", common_menu.text_back, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_A_RETURN);

  fw_type = lv_label_create(scr, "Firmware: WRCNC " SHORT_BUILD_VERSION);
  lv_obj_align(fw_type, nullptr, LV_ALIGN_CENTER, 0, -20);

  board = lv_label_create(scr, "Board: " BOARD_INFO_NAME);
  lv_obj_align(board, nullptr, LV_ALIGN_CENTER, 0, -60);
}

void lv_clear_about() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI

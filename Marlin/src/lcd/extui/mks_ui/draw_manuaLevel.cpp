/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../gcode/queue.h"
#include "../../../inc/MarlinConfig.h"

extern const char G28_STR[];

extern lv_group_t *g;
static lv_obj_t *scr;

enum {
  ID_M_POINT1 = 1,
  ID_M_POINT2,
  ID_M_POINT3,
  ID_M_POINT4,
  ID_M_POINT5,
  ID_MANUAL_RETURN
};

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;

  switch (obj->mks_obj_id) {
    case ID_M_POINT1 ... ID_M_POINT5:
      if (queue.ring_buffer.empty()) {
        if (uiCfg.leveling_first_time) {
          uiCfg.leveling_first_time = false;
          queue.inject_P(G28_STR);
        }
        const int ind = obj->mks_obj_id - ID_M_POINT1;
        sprintf_P(public_buf_l, PSTR("G1Z10\nG1X%dY%d\nG1Z0"), gCfgItems.trammingPos[ind].x, gCfgItems.trammingPos[ind].y);
        queue.inject(public_buf_l);
      }
      break;
    case ID_MANUAL_RETURN:
      lv_clear_manualLevel();
      lv_draw_tool();
      break;
  }
}

void lv_draw_manualLevel() {
  scr = lv_screen_create(LEVELING_UI);
  // Create an Image button
  lv_obj_t *buttonPoint1 = lv_big_button_create(scr, "F:/bmp_leveling1.bin", leveling_menu.position1, INTERVAL_V, titleHeight, event_handler, ID_M_POINT1);
  lv_obj_clear_protect(buttonPoint1, LV_PROTECT_FOLLOW);
  lv_big_button_create(scr, "F:/bmp_leveling2.bin", leveling_menu.position2, BTN_X_PIXEL + INTERVAL_V * 2, titleHeight, event_handler, ID_M_POINT2);
  lv_big_button_create(scr, "F:/bmp_leveling3.bin", leveling_menu.position3, BTN_X_PIXEL * 2 + INTERVAL_V * 3, titleHeight, event_handler, ID_M_POINT3);
  lv_big_button_create(scr, "F:/bmp_leveling4.bin", leveling_menu.position4, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight, event_handler, ID_M_POINT4);
  lv_big_button_create(scr, "F:/bmp_leveling5.bin", leveling_menu.position5, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_M_POINT5);
  lv_big_button_create(scr, "F:/bmp_return.bin", common_menu.text_back, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_MANUAL_RETURN);
}

void lv_clear_manualLevel() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI

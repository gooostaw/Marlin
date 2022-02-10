/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../inc/MarlinConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr;

enum {
  ID_PARA_RETURN = 1,
  ID_PARA_MACHINE,
  ID_PARA_MOTOR,
  ID_PARA_LEVEL,
  ID_PARA_ADVANCE
};

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  switch (obj->mks_obj_id) {
    case ID_PARA_RETURN:
      lv_clear_machine_para();
      draw_return_ui();
      break;
    case ID_PARA_MACHINE:
      lv_clear_machine_para();
      lv_draw_machine_settings();
      break;
    case ID_PARA_MOTOR:
      lv_clear_machine_para();
      lv_draw_motor_settings();
      break;
    case ID_PARA_LEVEL:
      lv_clear_machine_para();
      lv_draw_level_settings();
      break;
    case ID_PARA_ADVANCE:
      lv_clear_machine_para();
      lv_draw_advance_settings();
      break;
  }
}

void lv_draw_machine_para() {
  scr = lv_screen_create(MACHINE_PARA_UI);
  lv_screen_menu_item(scr, MachinePara_menu.MachineSetting, PARA_UI_POS_X, PARA_UI_POS_Y, event_handler, ID_PARA_MACHINE, 0);
  lv_screen_menu_item(scr, MachinePara_menu.MotorSetting, PARA_UI_POS_X, PARA_UI_POS_Y * 2, event_handler, ID_PARA_MOTOR, 1);
  lv_screen_menu_item(scr, MachinePara_menu.leveling, PARA_UI_POS_X, PARA_UI_POS_Y * 3, event_handler, ID_PARA_LEVEL, 2);
  lv_screen_menu_item(scr, MachinePara_menu.AdvanceSetting, PARA_UI_POS_X, PARA_UI_POS_Y * 4, event_handler, ID_PARA_ADVANCE, 3);
  lv_big_button_create(scr, "F:/bmp_back70x40.bin", common_menu.text_back, PARA_UI_BACK_POS_X + 10, PARA_UI_BACK_POS_Y, event_handler, ID_PARA_RETURN, true);
}

void lv_clear_machine_para() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI

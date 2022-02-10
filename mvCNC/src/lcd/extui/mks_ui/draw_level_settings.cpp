/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../inc/mvCNCConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr;

enum {
  ID_LEVEL_RETURN = 1,
  ID_LEVEL_POSITION,
  ID_LEVEL_COMMAND,
  ID_LEVEL_ZOFFSET,
  ID_Z_OFFSET_WIZARD
};

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  lv_clear_level_settings();
  switch (obj->mks_obj_id) {
    case ID_LEVEL_RETURN:
      draw_return_ui();
      break;
    case ID_LEVEL_POSITION:
      lv_draw_tramming_pos_settings();
      break;
    case ID_LEVEL_COMMAND:
      keyboard_value = autoLevelGcodeCommand;
      lv_draw_keyboard();
      break;
    #if HAS_BED_PROBE
      case ID_LEVEL_ZOFFSET:
        lv_draw_auto_level_offset_settings();
        break;
      #if ENABLED(PROBE_OFFSET_WIZARD)
        case ID_Z_OFFSET_WIZARD:
          lv_draw_z_offset_wizard();
          break;
      #endif
    #endif
  }
}

void lv_draw_level_settings() {
  scr = lv_screen_create(LEVELING_PARA_UI, machine_menu.LevelingParaConfTitle);
  lv_screen_menu_item(scr, machine_menu.TrammingPosConf, PARA_UI_POS_X, PARA_UI_POS_Y, event_handler, ID_LEVEL_POSITION, 0);
  lv_screen_menu_item(scr, machine_menu.LevelingAutoCommandConf, PARA_UI_POS_X, PARA_UI_POS_Y * 2, event_handler, ID_LEVEL_COMMAND, 1);
  #if HAS_BED_PROBE
    lv_screen_menu_item(scr, machine_menu.LevelingAutoZoffsetConf, PARA_UI_POS_X, PARA_UI_POS_Y * 3, event_handler, ID_LEVEL_ZOFFSET, 2);
    #if ENABLED(PROBE_OFFSET_WIZARD)
      lv_screen_menu_item(scr, machine_menu.LevelingZoffsetWizard, PARA_UI_POS_X, PARA_UI_POS_Y * 4, event_handler, ID_Z_OFFSET_WIZARD, 3);
    #endif
  #endif
  lv_big_button_create(scr, "F:/bmp_back70x40.bin", common_menu.text_back, PARA_UI_BACK_POS_X + 10, PARA_UI_BACK_POS_Y, event_handler, ID_LEVEL_RETURN, true);
}

void lv_clear_level_settings() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI

/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if HAS_TFT_LVGL_UI && USE_SENSORLESS

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../module/planner.h"
#include "../../../module/probe.h"
#include "../../../module/stepper/indirection.h"
#include "../../../feature/tmc_util.h"

extern lv_group_t *g;
static lv_obj_t *scr;

enum {
  ID_SENSITIVITY_RETURN = 1,
  ID_SENSITIVITY_X,
  ID_SENSITIVITY_Y,
  ID_SENSITIVITY_Z,
  ID_SENSITIVITY_Z2
};

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  switch (obj->mks_obj_id) {
    case ID_SENSITIVITY_RETURN:
      lv_clear_homing_sensitivity_settings();
      draw_return_ui();
      break;
    case ID_SENSITIVITY_X:
      value = x_sensitivity;
      lv_clear_homing_sensitivity_settings();
      lv_draw_number_key();
      break;
    case ID_SENSITIVITY_Y:
      value = y_sensitivity;
      lv_clear_homing_sensitivity_settings();
      lv_draw_number_key();
      break;
    case ID_SENSITIVITY_Z:
      value = z_sensitivity;
      lv_clear_homing_sensitivity_settings();
      lv_draw_number_key();
      break;
    #if Z2_SENSORLESS
      case ID_SENSITIVITY_Z2:
        value = z2_sensitivity;
        lv_clear_homing_sensitivity_settings();
        lv_draw_number_key();
        break;
    #endif
  }
}

void lv_draw_homing_sensitivity_settings() {
  scr = lv_screen_create(HOMING_SENSITIVITY_UI, machine_menu.HomingSensitivityConfTitle);

  itoa(TERN(X_SENSORLESS, stepperX.homing_threshold(), 0), public_buf_l, 10);
  lv_screen_menu_item_1_edit(scr, machine_menu.X_Sensitivity, PARA_UI_POS_X, PARA_UI_POS_Y, event_handler, ID_SENSITIVITY_X, 0, public_buf_l);

  itoa(TERN(Y_SENSORLESS, stepperY.homing_threshold(), 0), public_buf_l, 10);
  lv_screen_menu_item_1_edit(scr, machine_menu.Y_Sensitivity, PARA_UI_POS_X, PARA_UI_POS_Y * 2, event_handler, ID_SENSITIVITY_Y, 1, public_buf_l);

  itoa(TERN(Z_SENSORLESS, stepperZ.homing_threshold(), 0), public_buf_l, 10);
  lv_screen_menu_item_1_edit(scr, machine_menu.Z_Sensitivity, PARA_UI_POS_X, PARA_UI_POS_Y * 3, event_handler, ID_SENSITIVITY_Z, 2, public_buf_l);

  #if Z2_SENSORLESS
    itoa(TERN(Z2_SENSORLESS, stepperZ2.homing_threshold(), 0), public_buf_l, 10);
    lv_screen_menu_item_1_edit(scr, machine_menu.Z2_Sensitivity, PARA_UI_POS_X, PARA_UI_POS_Y * 4, event_handler, ID_SENSITIVITY_Z2, 3, public_buf_l);
  #endif

  lv_big_button_create(scr, "F:/bmp_back70x40.bin", common_menu.text_back, PARA_UI_BACK_POS_X, PARA_UI_BACK_POS_Y, event_handler, ID_SENSITIVITY_RETURN, true);
}

void lv_clear_homing_sensitivity_settings() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI && USE_SENSORLESS

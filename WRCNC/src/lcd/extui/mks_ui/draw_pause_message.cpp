/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/WRCNCConfigPre.h"

#if BOTH(HAS_TFT_LVGL_UI, ADVANCED_PAUSE_FEATURE)

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../feature/pause.h"
#include "../../../inc/WRCNCConfig.h"

void lv_draw_pause_message(const PauseMessage msg) {
  switch (msg) {
    case PAUSE_MESSAGE_PARKING:  clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_PARKING); break;
    case PAUSE_MESSAGE_CHANGING: clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_CHANGING); break;
    case PAUSE_MESSAGE_UNLOAD:   clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_UNLOAD); break;
    case PAUSE_MESSAGE_WAITING:  clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_WAITING); break;
    case PAUSE_MESSAGE_INSERT:   clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_INSERT); break;
    case PAUSE_MESSAGE_LOAD:     clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_LOAD); break;
    case PAUSE_MESSAGE_PURGE:    clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_PURGE); break;
    case PAUSE_MESSAGE_RESUME:   clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_RESUME); break;
    case PAUSE_MESSAGE_HEAT:     clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_HEAT); break;
    case PAUSE_MESSAGE_HEATING:  clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_HEATING); break;
    case PAUSE_MESSAGE_OPTION:   pause_menu_response = PAUSE_RESPONSE_WAIT_FOR;
      clear_cur_ui(); lv_draw_dialog(DIALOG_PAUSE_MESSAGE_OPTION); break;
    case PAUSE_MESSAGE_STATUS:
    default: break;
  }
}

#endif // HAS_TFT_LVGL_UI && ADVANCED_PAUSE_FEATURE

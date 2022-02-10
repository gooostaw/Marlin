/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>
#include "tft_lvgl_configuration.h"
#include "SPI_TFT.h"
#include "../../../inc/mvCNCConfig.h"
#include "mks_hardware.h"

static lv_obj_t *scr;

void lv_draw_error_message(FSTR_P const fmsg) {
  FSTR_P fhalted = F("PRINTER HALTED"), fplease = F("Please Reset");
  SPI_TFT.LCD_clear(0x0000);
  if (fmsg) disp_string((TFT_WIDTH - strlen_P(FTOP(fmsg)) * 16) / 2, 100, fmsg, 0xFFFF, 0x0000);
  disp_string((TFT_WIDTH - strlen_P(FTOP(fhalted)) * 16) / 2, 140, fhalted, 0xFFFF, 0x0000);
  disp_string((TFT_WIDTH - strlen_P(FTOP(fplease)) * 16) / 2, 180, fplease, 0xFFFF, 0x0000);
}

void lv_clear_error_message() { lv_obj_del(scr); }

#endif // HAS_TFT_LVGL_UI

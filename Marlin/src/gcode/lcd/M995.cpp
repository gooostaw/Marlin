/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(TOUCH_SCREEN_CALIBRATION)

#include "../gcode.h"

#if HAS_TFT_LVGL_UI
  #include "../../lcd/extui/mks_ui/draw_touch_calibration.h"
#else
  #include "../../lcd/menu/menu.h"
#endif

/**
 * M995: Touch screen calibration for TFT display
 */
void GcodeSuite::M995() {

  #if HAS_TFT_LVGL_UI
    lv_draw_touch_calibration_screen();
  #else
    ui.goto_screen(touch_screen_calibration);
  #endif

}

#endif // TOUCH_SCREEN_CALIBRATION

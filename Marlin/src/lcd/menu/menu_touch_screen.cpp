/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfigPre.h"

#if BOTH(HAS_MARLINUI_MENU, TOUCH_SCREEN_CALIBRATION)

#include "menu_item.h"
#include "../marlinui.h"

void touch_screen_calibration() {

  ui.touch_calibration_screen();

}

#endif // TOUCH_SCREEN_CALIBRATION

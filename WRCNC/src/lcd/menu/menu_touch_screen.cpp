/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfigPre.h"

#if BOTH(HAS_WRCNCUI_MENU, TOUCH_SCREEN_CALIBRATION)

#include "menu_item.h"
#include "../wrcncui.h"

void touch_screen_calibration() {

  ui.touch_calibration_screen();

}

#endif // TOUCH_SCREEN_CALIBRATION

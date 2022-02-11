/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfigPre.h"

#if BOTH(HAS_MVCNCUI_MENU, TOUCH_SCREEN_CALIBRATION)

#include "menu_item.h"
#include "../mvcncui.h"

void touch_screen_calibration() {

  ui.touch_calibration_screen();

}

#endif // TOUCH_SCREEN_CALIBRATION

/**
 * Modern Vintage CNC Firmware
*/

//
// Job Recovery Menu
//

#include "../../inc/mvCNCConfigPre.h"

#if BOTH(HAS_MVCNCUI_MENU, POWER_LOSS_RECOVERY)

#include "menu_item.h"
#include "../../gcode/queue.h"
#include "../../sd/cardreader.h"
#include "../../feature/powerloss.h"

static void lcd_power_loss_recovery_resume() {
  ui.return_to_status();
  queue.inject(F("M1000"));
}

void lcd_power_loss_recovery_cancel() {
  recovery.cancel();
  ui.return_to_status();
}

// TODO: Display long filename with Cancel/Resume buttons
//       Requires supporting methods in PLR class.
void menu_job_recovery() {
  ui.defer_status_screen();
  START_MENU();
  STATIC_ITEM(MSG_OUTAGE_RECOVERY);
  ACTION_ITEM(MSG_RESUME_PRINT, lcd_power_loss_recovery_resume);
  ACTION_ITEM(MSG_STOP_PRINT, lcd_power_loss_recovery_cancel);
  END_MENU();
}

#endif // HAS_MVCNCUI_MENU && POWER_LOSS_RECOVERY

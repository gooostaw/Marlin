/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(POWER_LOSS_RECOVERY)

#include "../../gcode.h"
#include "../../../feature/powerloss.h"
#include "../../../module/motion.h"

#include "../../../lcd/mvcncui.h"
#if ENABLED(EXTENSIBLE_UI)
  #include "../../../lcd/extui/ui_api.h"
#elif ENABLED(DWIN_CREALITY_LCD)
  #include "../../../lcd/e3v2/creality/dwin.h"
#elif ENABLED(DWIN_CREALITY_LCD_ENHANCED)
  #include "../../../lcd/e3v2/proui/dwin.h"
#elif ENABLED(DWIN_CREALITY_LCD_JYERSUI)
  #include "../../../lcd/e3v2/jyersui/dwin.h" // Temporary fix until it can be better implemented
#endif

#define DEBUG_OUT ENABLED(DEBUG_POWER_LOSS_RECOVERY)
#include "../../../core/debug_out.h"

void menu_job_recovery();

inline void plr_error(FSTR_P const prefix) {
  #if ENABLED(DEBUG_POWER_LOSS_RECOVERY)
    DEBUG_ECHO_START();
    DEBUG_ECHOF(prefix);
    DEBUG_ECHOLNPGM(" Job Recovery Data");
  #else
    UNUSED(prefix);
  #endif
}

#if HAS_MVCNCUI_MENU
  void lcd_power_loss_recovery_cancel();
#endif

/**
 * M1000: Resume from power-loss (undocumented)
 *   - With 'S' go to the Resume/Cancel menu
 *   - With no parameters, run recovery commands
 */
void GcodeSuite::M1000() {

  if (recovery.valid()) {
    if (parser.seen_test('S')) {
      #if HAS_MVCNCUI_MENU
        ui.goto_screen(menu_job_recovery);
      #elif HAS_DWIN_E3V2_BASIC
        recovery.dwin_flag = true;
      #elif ENABLED(DWIN_CREALITY_LCD_JYERSUI) // Temporary fix until it can be better implemented
        CrealityDWIN.Popup_Handler(Resume);
      #elif ENABLED(EXTENSIBLE_UI)
        ExtUI::onPowerLossResume();
      #else
        SERIAL_ECHO_MSG("Resume requires LCD.");
      #endif
    }
    else if (parser.seen_test('C')) {
      #if HAS_MVCNCUI_MENU
        lcd_power_loss_recovery_cancel();
      #else
        recovery.cancel();
      #endif
      TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStopped());
    }
    else
      recovery.resume();
  }
  else
    plr_error(recovery.info.valid_head ? F("No") : F("Invalid"));

}

#endif // POWER_LOSS_RECOVERY

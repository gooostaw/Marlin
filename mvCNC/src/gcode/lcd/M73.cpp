/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(LCD_SET_PROGRESS_MANUALLY)

#include "../gcode.h"
#include "../../lcd/mvcncui.h"
#include "../../sd/cardreader.h"

#if ENABLED(DWIN_CREALITY_LCD_ENHANCED)
  #include "../../lcd/e3v2/proui/dwin.h"
#endif

/**
 * M73: Set percentage complete (for display on LCD)
 *
 * Example:
 *   M73 P25 ; Set progress to 25%
 */
void GcodeSuite::M73() {

  #if ENABLED(DWIN_CREALITY_LCD_ENHANCED)

    DWIN_Progress_Update();

  #else

    if (parser.seenval('P'))
      ui.set_progress((PROGRESS_SCALE) > 1
        ? parser.value_float() * (PROGRESS_SCALE)
        : parser.value_byte()
      );

    #if ENABLED(USE_M73_REMAINING_TIME)
      if (parser.seenval('R')) ui.set_remaining_time(60 * parser.value_ulong());
    #endif

  #endif
}

#endif // LCD_SET_PROGRESS_MANUALLY

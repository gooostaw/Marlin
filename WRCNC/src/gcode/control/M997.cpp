/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"

#if ENABLED(PLATFORM_M997_SUPPORT)

#if ENABLED(DWIN_CREALITY_LCD_ENHANCED)
  #include "../../lcd/e3v2/proui/dwin.h"
#endif

/**
 * M997: Perform in-application firmware update
 */
void GcodeSuite::M997() {

  TERN_(DWIN_CREALITY_LCD_ENHANCED, DWIN_RebootScreen());

  flashFirmware(parser.intval('S'));

}

#endif

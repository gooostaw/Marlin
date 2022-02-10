/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if HAS_MULTI_LANGUAGE

#include "../gcode.h"
#include "../../WRCNCCore.h"
#include "../../lcd/wrcncui.h"

/**
 * M414: Set the language for the UI
 *
 * Parameters
 *  S<index> : The language to select
 */
void GcodeSuite::M414() {

  if (parser.seenval('S'))
    ui.set_language(parser.value_byte());
  else
    M414_report();

}

void GcodeSuite::M414_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_UI_LANGUAGE));
  SERIAL_ECHOLNPGM("  M414 S", ui.language);
}

#endif // HAS_MULTI_LANGUAGE

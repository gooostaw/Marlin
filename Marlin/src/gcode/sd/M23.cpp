/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"
#include "../../lcd/marlinui.h"

/**
 * M23: Open a file
 *
 * The path is relative to the root directory
 */
void GcodeSuite::M23() {
  // Simplify3D includes the size, so zero out all spaces (#7227)
  for (char *fn = parser.string_arg; *fn; ++fn) if (*fn == ' ') *fn = '\0';
  card.openFileRead(parser.string_arg);

  TERN_(LCD_SET_PROGRESS_MANUALLY, ui.set_progress(0));
}

#endif // SDSUPPORT

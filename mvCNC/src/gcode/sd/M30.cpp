/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M30 <filename>: Delete SD Card file
 */
void GcodeSuite::M30() {
  if (card.isMounted()) {
    card.closefile();
    card.removeFile(parser.string_arg);
  }
}

#endif // SDSUPPORT

/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M26: Set SD Card file index
 */
void GcodeSuite::M26() {
  if (card.isMounted() && parser.seenval('S'))
    card.setIndex(parser.value_long());
}

#endif // SDSUPPORT

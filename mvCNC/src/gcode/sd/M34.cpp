/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if BOTH(SDCARD_SORT_ALPHA, SDSORT_GCODE)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M34: Set SD Card Sorting Options
 */
void GcodeSuite::M34() {
  if (parser.seen('S')) card.setSortOn(parser.value_bool());
  if (parser.seenval('F')) {
    const int v = parser.value_long();
    card.setSortFolders(v < 0 ? -1 : v > 0 ? 1 : 0);
  }
  //if (parser.seen('R')) card.setSortReverse(parser.value_bool());
}

#endif // SDCARD_SORT_ALPHA && SDSORT_GCODE

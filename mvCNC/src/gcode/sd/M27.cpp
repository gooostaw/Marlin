/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M27: Get SD Card status
 *      OR, with 'S<seconds>' set the SD status auto-report interval. (Requires AUTO_REPORT_SD_STATUS)
 *      OR, with 'C' get the current filename.
 */
void GcodeSuite::M27() {
  if (parser.seen_test('C')) {
    SERIAL_ECHOPGM("Current file: ");
    card.printSelectedFilename();
    return;
  }

  #if ENABLED(AUTO_REPORT_SD_STATUS)
    if (parser.seenval('S')) {
      card.auto_reporter.set_interval(parser.value_byte());
      return;
    }
  #endif

  card.report_status();
}

#endif // SDSUPPORT

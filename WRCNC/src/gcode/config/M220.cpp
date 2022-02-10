/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../module/motion.h"

/**
 * M220: Set speed percentage factor, aka "Feed Rate"
 *
 * Parameters
 *   S<percent> : Set the feed rate percentage factor
 *
 * Report the current speed percentage factor if no parameter is specified
 *
 * For MMU2 and MMU2S devices...
 *   B : Flag to back up the current factor
 *   R : Flag to restore the last-saved factor
 */
void GcodeSuite::M220() {

  static int16_t backup_feedrate_percentage = 100;
  if (parser.seen('B')) backup_feedrate_percentage = feedrate_percentage;
  if (parser.seen('R')) feedrate_percentage = backup_feedrate_percentage;

  if (parser.seenval('S')) feedrate_percentage = parser.value_int();

  if (!parser.seen_any()) {
    SERIAL_ECHOLNPGM("FR:", feedrate_percentage, "%");
  }
}

/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if ENABLED(GCODE_REPEAT_MARKERS)

#include "../gcode.h"
#include "../../feature/repeat.h"

/**
 * M808: Set / Goto a repeat marker
 *
 *  L<count> - Set a repeat marker with 'count' repetitions. If omitted, infinity.
 *
 * Examples:
 *
 *    M808 L   ; Set a loop marker with a count of infinity
 *    M808 L2  ; Set a loop marker with a count of 2
 *    M808     ; Decrement and loop if not zero.
 */
void GcodeSuite::M808() {

  // Handled early and ignored here in the queue.
  // Allowed to go into the queue for logging purposes.

  // M808 K sent from the host to cancel all loops
  if (parser.seen_test('K')) repeat.cancel();

}

#endif // GCODE_REPEAT_MARKERS

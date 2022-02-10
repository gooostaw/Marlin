/**
 * Modern Vintage CNC Firmware
*/

#include "../gcode.h"
#include "../queue.h" // for last_N

/**
 * M110: Set Current Line Number
 */
void GcodeSuite::M110() {

  if (parser.seenval('N'))
    queue.set_current_line_number(parser.value_long());

}

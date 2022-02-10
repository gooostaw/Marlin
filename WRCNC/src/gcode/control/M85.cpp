/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"

/**
 * M85: Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
 */
void GcodeSuite::M85() {

  if (parser.seen('S')) {
    reset_stepper_timeout();
    max_inactive_time = parser.value_millis_from_seconds();
  }

}

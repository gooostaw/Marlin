/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../module/endstops.h"

/**
 * M119: Output endstop states to serial output
 */
void GcodeSuite::M119() {

  endstops.report_states();

}

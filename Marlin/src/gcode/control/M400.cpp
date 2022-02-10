/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../module/stepper.h"

/**
 * M400: Finish all moves
 */
void GcodeSuite::M400() {

  planner.synchronize();

}

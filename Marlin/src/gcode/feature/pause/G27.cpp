/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfig.h"

#if ENABLED(NOZZLE_PARK_FEATURE)

#include "../../gcode.h"
#include "../../../libs/nozzle.h"
#include "../../../module/motion.h"

/**
 * G27: Park the nozzle
 */
void GcodeSuite::G27() {
  // Don't allow nozzle parking without homing first
  if (homing_needed_error()) return;
  nozzle.park(parser.ushortval('P'));
}

#endif // NOZZLE_PARK_FEATURE

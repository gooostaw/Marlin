/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if DISABLED(EMERGENCY_PARSER)

#include "../gcode.h"
#include "../../mvCNCCore.h" // for wait_for_heatup, kill, M112_KILL_STR
#include "../../module/motion.h" // for quickstop_stepper

/**
 * M108: Stop the waiting for heaters in M109, M190, M303. Does not affect the target temperature.
 */
void GcodeSuite::M108() {
  TERN_(HAS_RESUME_CONTINUE, wait_for_user = false);
  wait_for_heatup = false;
}

/**
 * M112: Full Shutdown
 */
void GcodeSuite::M112() {
  kill(FPSTR(M112_KILL_STR), nullptr, true);
}

/**
 * M410: Quickstop - Abort all planned moves
 *
 * This will stop the carriages mid-move, so most likely they
 * will be out of sync with the stepper position after this.
 */
void GcodeSuite::M410() {
  quickstop_stepper();
}

#endif // !EMERGENCY_PARSER

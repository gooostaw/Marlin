/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)

#include "../gcode.h"
#include "../../module/stepper.h"

/**
 * M540: Set whether SD card print should abort on endstop hit (M540 S<0|1>)
 */
void GcodeSuite::M540() {

  if (parser.seen('S'))
    planner.abort_on_endstop_hit = parser.value_bool();

}

#endif // SD_ABORT_ON_ENDSTOP_HIT

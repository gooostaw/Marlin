/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfigPre.h"

#if ENABLED(GCODE_MOTION_MODES)

#include "../gcode.h"

/**
 * G80: Cancel current motion mode
 */
void GcodeSuite::G80() {

  parser.cancel_motion_mode();

}

#endif // GCODE_MOTION_MODES

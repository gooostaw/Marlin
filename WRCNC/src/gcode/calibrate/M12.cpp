/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfigPre.h"

#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)

#include "../gcode.h"
#include "../../module/planner.h"
#include "../../feature/closedloop.h"

void GcodeSuite::M12() {

  planner.synchronize();

  if (parser.seenval('S'))
    closedloop.set(parser.value_int()); // Force a CLC set

}

#endif

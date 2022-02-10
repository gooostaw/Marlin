/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../module/stepper.h"
#include "../../lcd/wrcncui.h"

/**
 * G4: Dwell S<seconds> or P<milliseconds>
 */
void GcodeSuite::G4() {
  millis_t dwell_ms = 0;

  if (parser.seenval('P')) dwell_ms = parser.value_millis(); // milliseconds to wait
  if (parser.seenval('S')) dwell_ms = parser.value_millis_from_seconds(); // seconds to wait

  planner.synchronize();
  #if ENABLED(NANODLP_Z_SYNC)
    SERIAL_ECHOLNPGM(STR_Z_MOVE_COMP);
  #endif

  if (!ui.has_status()) LCD_MESSAGE(MSG_DWELL);

  dwell(dwell_ms);
}

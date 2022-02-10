/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if HAS_FILAMENT_SENSOR

#include "../../gcode.h"
#include "../../../feature/runout.h"

/**
 * M412: Enable / Disable filament runout detection
 *
 * Parameters
 *  R         : Reset the runout sensor
 *  S<bool>   : Reset and enable/disable the runout sensor
 *  H<bool>   : Enable/disable host handling of filament runout
 *  D<linear> : Extra distance to continue after runout is triggered
 */
void GcodeSuite::M412() {
  if (parser.seen("RS"
    TERN_(HAS_FILAMENT_RUNOUT_DISTANCE, "D")
    TERN_(HOST_ACTION_COMMANDS, "H")
  )) {
    #if ENABLED(HOST_ACTION_COMMANDS)
      if (parser.seen('H')) runout.host_handling = parser.value_bool();
    #endif
    const bool seenR = parser.seen_test('R'), seenS = parser.seen('S');
    if (seenR || seenS) runout.reset();
    if (seenS) runout.enabled = parser.value_bool();
    #if HAS_FILAMENT_RUNOUT_DISTANCE
      if (parser.seen('D')) runout.set_runout_distance(parser.value_linear_units());
    #endif
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Filament runout ");
    serialprint_onoff(runout.enabled);
    #if HAS_FILAMENT_RUNOUT_DISTANCE
      SERIAL_ECHOPGM(" ; Distance ", runout.runout_distance(), "mm");
    #endif
    #if ENABLED(HOST_ACTION_COMMANDS)
      SERIAL_ECHOPGM(" ; Host handling ");
      serialprint_onoff(runout.host_handling);
    #endif
    SERIAL_EOL();
  }
}

void GcodeSuite::M412_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_FILAMENT_RUNOUT_SENSOR));
  SERIAL_ECHOPGM(
    "  M412 S", runout.enabled
    #if HAS_FILAMENT_RUNOUT_DISTANCE
      , " D", LINEAR_UNIT(runout.runout_distance())
    #endif
    , " ; Sensor "
  );
  serialprintln_onoff(runout.enabled);
}

#endif // HAS_FILAMENT_SENSOR

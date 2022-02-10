/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(PIDTEMPCHAMBER)

#include "../gcode.h"
#include "../../module/temperature.h"

/**
 * M309 - Set and/or Report the current Chamber PID values
 *
 *  P<pval> - Set the P value
 *  I<ival> - Set the I value
 *  D<dval> - Set the D value
 */
void GcodeSuite::M309() {
  if (!parser.seen("PID")) return M309_report();
  if (parser.seen('P')) thermalManager.temp_chamber.pid.Kp = parser.value_float();
  if (parser.seen('I')) thermalManager.temp_chamber.pid.Ki = scalePID_i(parser.value_float());
  if (parser.seen('D')) thermalManager.temp_chamber.pid.Kd = scalePID_d(parser.value_float());
}

void GcodeSuite::M309_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_CHAMBER_PID));
  SERIAL_ECHOLNPGM(
      "  M309 P", thermalManager.temp_chamber.pid.Kp
    , " I", unscalePID_i(thermalManager.temp_chamber.pid.Ki)
    , " D", unscalePID_d(thermalManager.temp_chamber.pid.Kd)
  );
}

#endif // PIDTEMPCHAMBER

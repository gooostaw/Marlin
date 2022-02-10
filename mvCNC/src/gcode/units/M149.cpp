/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(TEMPERATURE_UNITS_SUPPORT)

#include "../gcode.h"

/**
 * M149: Set temperature units
 */
void GcodeSuite::M149() {
       if (parser.seenval('C')) parser.set_input_temp_units(TEMPUNIT_C);
  else if (parser.seenval('K')) parser.set_input_temp_units(TEMPUNIT_K);
  else if (parser.seenval('F')) parser.set_input_temp_units(TEMPUNIT_F);
  else M149_report();
}

void GcodeSuite::M149_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_TEMPERATURE_UNITS));
  SERIAL_ECHOPGM("  M149 ", AS_CHAR(parser.temp_units_code()), " ; Units in ");
  SERIAL_ECHOLNF(parser.temp_units_name());
}

#endif // TEMPERATURE_UNITS_SUPPORT

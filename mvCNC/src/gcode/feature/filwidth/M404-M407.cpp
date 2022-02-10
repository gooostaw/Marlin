/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(FILAMENT_WIDTH_SENSOR)

#include "../../../feature/filwidth.h"
#include "../../../module/planner.h"
#include "../../../mvCNCCore.h"
#include "../../gcode.h"

/**
 * M404: Display or set (in current units) the nominal filament width (3mm, 1.75mm ) W<3.0>
 */
void GcodeSuite::M404() {
  if (parser.seenval('W')) {
    filwidth.nominal_mm = parser.value_linear_units();
    planner.volumetric_area_nominal = CIRCLE_AREA(filwidth.nominal_mm * 0.5);
  }
  else
    SERIAL_ECHOLNPGM("Filament dia (nominal mm):", filwidth.nominal_mm);
}

/**
 * M405: Turn on filament sensor for control
 */
void GcodeSuite::M405() {
  // This is technically a linear measurement, but since it's quantized to centimeters and is a different
  // unit than everything else, it uses parser.value_byte() instead of parser.value_linear_units().
  if (parser.seenval('D'))
    filwidth.set_delay_cm(parser.value_byte());

  filwidth.enable(true);
}

/**
 * M406: Turn off filament sensor for control
 */
void GcodeSuite::M406() {
  filwidth.enable(false);
  planner.calculate_volumetric_multipliers();   // Restore correct 'volumetric_multiplier' value
}

/**
 * M407: Get measured filament diameter on serial output
 */
void GcodeSuite::M407() {
  SERIAL_ECHOLNPGM("Filament dia (measured mm):", filwidth.measured_mm);
}

#endif // FILAMENT_WIDTH_SENSOR

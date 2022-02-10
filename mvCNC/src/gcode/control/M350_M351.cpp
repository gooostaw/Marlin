/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if HAS_MICROSTEPS

#include "../gcode.h"
#include "../../module/stepper.h"

/**
 * M350: Set axis microstepping modes. S sets mode for all drivers.
 *
 * Warning: Steps-per-unit remains unchanged.
 */
void GcodeSuite::M350() {
  if (parser.seen('S')) LOOP_LE_N(i, 4) stepper.microstep_mode(i, parser.value_byte());
  LOOP_LOGICAL_AXES(i) if (parser.seen(axis_codes[i])) stepper.microstep_mode(i, parser.value_byte());
  if (parser.seen('B')) stepper.microstep_mode(4, parser.value_byte());
  stepper.microstep_readings();
}

/**
 * M351: Toggle MS1 MS2 pins directly with axis codes X Y Z E B
 *       S# determines MS1, MS2 or MS3, X# sets the pin high/low.
 */
void GcodeSuite::M351() {
  if (parser.seenval('S')) switch (parser.value_byte()) {
    case 1:
      LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) stepper.microstep_ms(i, parser.value_byte(), -1, -1);
      if (parser.seenval('B')) stepper.microstep_ms(4, parser.value_byte(), -1, -1);
      break;
    case 2:
      LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) stepper.microstep_ms(i, -1, parser.value_byte(), -1);
      if (parser.seenval('B')) stepper.microstep_ms(4, -1, parser.value_byte(), -1);
      break;
    case 3:
      LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) stepper.microstep_ms(i, -1, -1, parser.value_byte());
      if (parser.seenval('B')) stepper.microstep_ms(4, -1, -1, parser.value_byte());
      break;
  }
  stepper.microstep_readings();
}

#endif // HAS_MICROSTEPS

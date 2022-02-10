/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if HAS_TRINAMIC_CONFIG

#include "../../gcode.h"
#include "../../../feature/tmc_util.h"
#include "../../../module/stepper/indirection.h"

/**
 * M122: Debug TMC drivers
 */
void GcodeSuite::M122() {
  xyze_bool_t print_axis = ARRAY_N_1(LOGICAL_AXES, false);

  bool print_all = true;
  LOOP_LOGICAL_AXES(i) if (parser.seen_test(axis_codes[i])) { print_axis[i] = true; print_all = false; }

  if (print_all) LOOP_LOGICAL_AXES(i) print_axis[i] = true;

  if (parser.boolval('I')) restore_stepper_drivers();

  #if ENABLED(TMC_DEBUG)
    #if ENABLED(MONITOR_DRIVER_STATUS)
      const bool sflag = parser.seen_test('S'), sval = sflag && parser.value_bool();
      if (sflag && !sval)
        tmc_set_report_interval(0);
      else if (parser.seenval('P'))
        tmc_set_report_interval(_MAX(250, parser.value_ushort()));
      else if (sval)
        tmc_set_report_interval(MONITOR_DRIVER_STATUS_INTERVAL_MS);
    #endif

    if (parser.seen_test('V'))
      tmc_get_registers(LOGICAL_AXIS_ELEM(print_axis));
    else
      tmc_report_all(LOGICAL_AXIS_ELEM(print_axis));
  #endif

  test_tmc_connection(LOGICAL_AXIS_ELEM(print_axis));
}

#endif // HAS_TRINAMIC_CONFIG

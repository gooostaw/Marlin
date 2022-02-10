/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfigPre.h"

#if HAS_SOFTWARE_ENDSTOPS

#include "../gcode.h"
#include "../../module/motion.h"

/**
 * M211: Enable, Disable, and/or Report software endstops
 *
 * Usage: M211 S1 to enable, M211 S0 to disable, M211 alone for report
 */
void GcodeSuite::M211() {
  if (parser.seen('S'))
    soft_endstop._enabled = parser.value_bool();
  else
    M211_report();
}

void GcodeSuite::M211_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_SOFT_ENDSTOPS));
  SERIAL_ECHOPGM("  M211 S", AS_DIGIT(soft_endstop._enabled), " ; ");
  serialprintln_onoff(soft_endstop._enabled);

  report_echo_start(forReplay);
  const xyz_pos_t l_soft_min = soft_endstop.min.asLogical(),
                  l_soft_max = soft_endstop.max.asLogical();
  print_pos(l_soft_min, F(STR_SOFT_MIN), F(" "));
  print_pos(l_soft_max, F(STR_SOFT_MAX));
}

#endif // HAS_SOFTWARE_ENDSTOPS

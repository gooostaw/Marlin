/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfig.h"

#if ENABLED(POWER_LOSS_RECOVERY)

#include "../../gcode.h"
#include "../../../feature/powerloss.h"
#include "../../../module/motion.h"
#include "../../../lcd/marlinui.h"

/**
 * M413: Enable / Disable power-loss recovery
 *
 * Parameters
 *   S[bool] - Flag to enable / disable.
 *             If omitted, report current state.
 */
void GcodeSuite::M413() {

  if (parser.seen('S'))
    recovery.enable(parser.value_bool());
  else
    M413_report();

  #if ENABLED(DEBUG_POWER_LOSS_RECOVERY)
    if (parser.seen("RL")) recovery.load();
    if (parser.seen_test('W')) recovery.save(true);
    if (parser.seen_test('P')) recovery.purge();
    if (parser.seen_test('D')) recovery.debug(F("M413"));
    #if PIN_EXISTS(POWER_LOSS)
      if (parser.seen_test('O')) recovery._outage();
    #endif
    if (parser.seen_test('E')) SERIAL_ECHOF(recovery.exists() ? F("PLR Exists\n") : F("No PLR\n"));
    if (parser.seen_test('V')) SERIAL_ECHOF(recovery.valid() ? F("Valid\n") : F("Invalid\n"));
  #endif
}

void GcodeSuite::M413_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_POWER_LOSS_RECOVERY));
  SERIAL_ECHOPGM("  M413 S", AS_DIGIT(recovery.enabled), " ; ");
  serialprintln_onoff(recovery.enabled);
}

#endif // POWER_LOSS_RECOVERY

/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/WRCNCConfig.h"

#if HAS_POWER_MONITOR

#include "../../../feature/power_monitor.h"
#include "../../../WRCNCCore.h"
#include "../../gcode.h"

/**
 * M430: Enable/disable current LCD display
 *       With no parameters report the system current draw (in Amps)
 *
 *  I[bool] - Set Display of current on the LCD
 *  V[bool] - Set Display of voltage on the LCD
 *  W[bool] - Set Display of power on the LCD
 */
void GcodeSuite::M430() {
  bool do_report = true;
  #if HAS_WIRED_LCD
    #if ENABLED(POWER_MONITOR_CURRENT)
      if (parser.seen('I')) { power_monitor.set_current_display(parser.value_bool()); do_report = false; }
    #endif
    #if ENABLED(POWER_MONITOR_VOLTAGE)
      if (parser.seen('V')) { power_monitor.set_voltage_display(parser.value_bool()); do_report = false; }
    #endif
    #if HAS_POWER_MONITOR_WATTS
      if (parser.seen('W')) { power_monitor.set_power_display(parser.value_bool()); do_report = false; }
    #endif
  #endif
  if (do_report) {
    SERIAL_ECHOLNPGM(
      #if ENABLED(POWER_MONITOR_CURRENT)
        "Current: ", power_monitor.getAmps(), "A"
        TERN_(POWER_MONITOR_VOLTAGE, "  ")
      #endif
      #if ENABLED(POWER_MONITOR_VOLTAGE)
        "Voltage: ", power_monitor.getVolts(), "V"
      #endif
      #if HAS_POWER_MONITOR_WATTS
        "  Power: ", power_monitor.getPower(), "W"
      #endif
    );
  }
}

#endif // HAS_POWER_MONITOR

/**
 * Modern Vintage CNC Firmware
*/

//
// Power Monitor Menu
//

#include "../../inc/mvCNCConfigPre.h"

#if HAS_MVCNCUI_MENU && HAS_POWER_MONITOR

#include "menu_item.h"
#include "../../feature/power_monitor.h"

void menu_power_monitor() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  #if ENABLED(POWER_MONITOR_CURRENT)
  {
    bool ena = power_monitor.current_display_enabled();
    EDIT_ITEM(bool, MSG_CURRENT, &ena, power_monitor.toggle_current_display);
  }
  #endif

  #if ENABLED(POWER_MONITOR_VOLTAGE)
  {
    bool ena = power_monitor.voltage_display_enabled();
    EDIT_ITEM(bool, MSG_VOLTAGE, &ena, power_monitor.toggle_voltage_display);
  }
  #endif

  #if HAS_POWER_MONITOR_WATTS
  {
    bool ena = power_monitor.power_display_enabled();
    EDIT_ITEM(bool, MSG_POWER, &ena, power_monitor.toggle_power_display);
  }
  #endif

  END_MENU();
}

#endif // HAS_MVCNCUI_MENU && HAS_POWER_MONITOR

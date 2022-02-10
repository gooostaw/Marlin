/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfigPre.h"

#if HAS_POWER_MONITOR

#include "power_monitor.h"

#if HAS_mvCNCUI_MENU
  #include "../lcd/mvcncui.h"
  #include "../lcd/lcdprint.h"
#endif

#include "../libs/numtostr.h"

uint8_t PowerMonitor::flags; // = 0

#if ENABLED(POWER_MONITOR_CURRENT)
  pm_lpf_t<PowerMonitor::amps_adc_scale, PM_K_VALUE, PM_K_SCALE> PowerMonitor::amps;
#endif
#if ENABLED(POWER_MONITOR_VOLTAGE)
  pm_lpf_t<PowerMonitor::volts_adc_scale, PM_K_VALUE, PM_K_SCALE> PowerMonitor::volts;
#endif

millis_t PowerMonitor::display_item_ms;
uint8_t PowerMonitor::display_item;

PowerMonitor power_monitor; // Single instance - this calls the constructor

#if HAS_mvCNCUI_U8GLIB

  #if ENABLED(POWER_MONITOR_CURRENT)
    void PowerMonitor::draw_current() {
      const float amps = getAmps();
      lcd_put_u8str(amps < 100 ? ftostr31ns(amps) : ui16tostr4rj((uint16_t)amps));
      lcd_put_wchar('A');
    }
  #endif

  #if ENABLED(POWER_MONITOR_VOLTAGE)
    void PowerMonitor::draw_voltage() {
      const float volts = getVolts();
      lcd_put_u8str(volts < 100 ? ftostr31ns(volts) : ui16tostr4rj((uint16_t)volts));
      lcd_put_wchar('V');
    }
  #endif

  #if HAS_POWER_MONITOR_WATTS
    void PowerMonitor::draw_power() {
      const float power = getPower();
      lcd_put_u8str(power < 100 ? ftostr31ns(power) : ui16tostr4rj((uint16_t)power));
      lcd_put_wchar('W');
    }
  #endif

#endif // HAS_mvCNCUI_U8GLIB

#endif // HAS_POWER_MONITOR

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * power.h - power control
 */

#if EITHER(AUTO_POWER_CONTROL, POWER_OFF_TIMER)
  #include "../core/millis_t.h"
#endif

class Power {
  public:
    static bool psu_on;

    static void init();
    static void power_on();
    static void power_off();

    #if EITHER(POWER_OFF_TIMER, POWER_OFF_WAIT_FOR_COOLDOWN)
      #if ENABLED(POWER_OFF_TIMER)
        static millis_t power_off_time;
        static void setPowerOffTimer(const millis_t delay_ms);
      #endif
      #if ENABLED(POWER_OFF_WAIT_FOR_COOLDOWN)
        static bool power_off_on_cooldown;
        static void setPowerOffOnCooldown(const bool ena);
      #endif
      static void cancelAutoPowerOff();
      static void checkAutoPowerOff();
    #endif

    #if ENABLED(AUTO_POWER_CONTROL) && POWER_OFF_DELAY > 0
      static void power_off_soon();
    #else
      static void power_off_soon() { power_off(); }
    #endif

    #if ENABLED(AUTO_POWER_CONTROL)
      static void check(const bool pause);

      private:
        static millis_t lastPowerOn;
        static bool is_power_needed();
        static bool is_cooling_needed();
    #elif ENABLED(POWER_OFF_WAIT_FOR_COOLDOWN)
      private:
        static bool is_cooling_needed();
    #endif
};

extern Power powerManager;

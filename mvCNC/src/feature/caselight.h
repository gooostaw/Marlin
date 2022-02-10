/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../inc/mvCNCConfig.h"

#if CASE_LIGHT_IS_COLOR_LED
  #include "leds/leds.h" // for LEDColor
#endif

class CaseLight {
public:
  static bool on;
  #if ENABLED(CASELIGHT_USES_BRIGHTNESS)
    static uint8_t brightness;
  #endif

  static bool pin_is_pwm() { return TERN0(NEED_CASE_LIGHT_PIN, PWM_PIN(CASE_LIGHT_PIN)); }
  static bool has_brightness() { return TERN0(CASELIGHT_USES_BRIGHTNESS, TERN(CASE_LIGHT_USE_NEOPIXEL, true, pin_is_pwm())); }

  static void init() {
    #if NEED_CASE_LIGHT_PIN
      if (pin_is_pwm()) SET_PWM(CASE_LIGHT_PIN); else SET_OUTPUT(CASE_LIGHT_PIN);
    #endif
    update_brightness();
  }

  static void update(const bool sflag);
  static void update_brightness() { update(false); }
  static void update_enabled()    { update(true);  }

  #if ENABLED(CASE_LIGHT_IS_COLOR_LED)
    private:
      static LEDColor color;
  #endif
};

extern CaseLight caselight;

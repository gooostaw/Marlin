/**
 * Webber Ranch CNC Firmware
*/
#ifdef TARGET_LPC1768

#include "../../inc/MarlinConfigPre.h"
#include <pwm.h>

void set_pwm_duty(const pin_t pin, const uint16_t v, const uint16_t v_size/*=255*/, const bool invert/*=false*/) {
  if (!LPC176x::pin_is_valid(pin)) return;
  if (LPC176x::pwm_attach_pin(pin))
    LPC176x::pwm_write_ratio(pin, invert ? 1.0f - (float)v / v_size : (float)v / v_size);  // map 1-254 onto PWM range
}

void set_pwm_frequency(const pin_t pin, const uint16_t f_desired) {
  LPC176x::pwm_set_frequency(pin, f_desired);
}

#endif // TARGET_LPC1768

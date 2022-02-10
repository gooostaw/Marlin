/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Driver for the Philips PCA9632 LED driver.
 * Written by Robert Mendon Feb 2017.
 */

struct LEDColor;
typedef LEDColor LEDColor;

void PCA9632_set_led_color(const LEDColor &color);

#if ENABLED(PCA9632_BUZZER)
  #include <stdint.h>
  void PCA9632_buzz(const long, const uint16_t);
#endif

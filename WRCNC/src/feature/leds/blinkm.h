/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * blinkm.h - Control a BlinkM over i2c
 */

struct LEDColor;
typedef LEDColor LEDColor;

void blinkm_set_led_color(const LEDColor &color);

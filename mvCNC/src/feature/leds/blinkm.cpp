/**
 * Modern Vintage CNC Firmware
*/

/**
 * blinkm.cpp - Control a BlinkM over i2c
 */

#include "../../inc/mvCNCConfig.h"

#if ENABLED(BLINKM)

#include "blinkm.h"
#include "leds.h"
#include <Wire.h>

void blinkm_set_led_color(const LEDColor &color) {
  Wire.begin();
  Wire.beginTransmission(I2C_ADDRESS(0x09));
  Wire.write('o');                    //to disable ongoing script, only needs to be used once
  Wire.write('n');
  Wire.write(color.r);
  Wire.write(color.g);
  Wire.write(color.b);
  Wire.endTransmission();
}

#endif // BLINKM

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * joystick.h - joystick input / jogging
 */

#include "../inc/mvCNCConfigPre.h"
#include "../core/types.h"

#if PIN_EXISTS(JOY_EN)
pinMode(JOY_EN_PIN, OUTPUT);
#endif

class Joystick {
  private:
    #if HAS_JOY_ADC_X
  xyz_float_t x;
    #endif
    #if HAS_JOY_ADC_Y
  xyz_float_t y;
    #endif
    #if HAS_JOY_ADC_Z
    xyz_float_t z;
    #endif
  public:
  bool enabled = ENABLED(JOYSTICK_ENABLED);
    #if ENABLED(JOYSTICK_DEBUG)
  void report();
    #endif
    void calculate(xyz_float_t &norm_jog);
    void injectJogMoves();
};

extern Joystick joystick;

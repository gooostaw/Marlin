/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * feature/z_stepper_align.h
 */

#include "../inc/WRCNCConfig.h"

class ZStepperAlign {
  public:
    static xy_pos_t xy[NUM_Z_STEPPER_DRIVERS];

    #if ENABLED(Z_STEPPER_ALIGN_KNOWN_STEPPER_POSITIONS)
      static xy_pos_t stepper_xy[NUM_Z_STEPPER_DRIVERS];
    #endif

  static void reset_to_default();
};

extern ZStepperAlign z_stepper_align;

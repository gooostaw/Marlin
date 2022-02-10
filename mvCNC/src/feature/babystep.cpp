/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfig.h"

#if ENABLED(BABYSTEPPING)

#include "babystep.h"
#include "../mvCNCCore.h"
#include "../module/motion.h"   // for axes_should_home()
#include "../module/planner.h"  // for axis_steps_per_mm[]
#include "../module/stepper.h"

#if ENABLED(BABYSTEP_ALWAYS_AVAILABLE)
  #include "../gcode/gcode.h"
#endif

Babystep babystep;

volatile int16_t Babystep::steps[BS_AXIS_IND(Z_AXIS) + 1];
#if ENABLED(BABYSTEP_DISPLAY_TOTAL)
  int16_t Babystep::axis_total[BS_TOTAL_IND(Z_AXIS) + 1];
#endif
int16_t Babystep::accum;

void Babystep::step_axis(const AxisEnum axis) {
  const int16_t curTodo = steps[BS_AXIS_IND(axis)]; // get rid of volatile for performance
  if (curTodo) {
    stepper.do_babystep((AxisEnum)axis, curTodo > 0);
    if (curTodo > 0) steps[BS_AXIS_IND(axis)]--; else steps[BS_AXIS_IND(axis)]++;
  }
}

void Babystep::add_mm(const AxisEnum axis, const_float_t mm) {
  add_steps(axis, mm * planner.settings.axis_steps_per_mm[axis]);
}

void Babystep::add_steps(const AxisEnum axis, const int16_t distance) {
  if (DISABLED(BABYSTEP_WITHOUT_HOMING) && axes_should_home(_BV(axis))) return;

  accum += distance; // Count up babysteps for the UI
  steps[BS_AXIS_IND(axis)] += distance;
  TERN_(BABYSTEP_DISPLAY_TOTAL, axis_total[BS_TOTAL_IND(axis)] += distance);
  TERN_(BABYSTEP_ALWAYS_AVAILABLE, gcode.reset_stepper_timeout());
  TERN_(INTEGRATED_BABYSTEPPING, if (has_steps()) stepper.initiateBabystepping());
}

#endif // BABYSTEPPING

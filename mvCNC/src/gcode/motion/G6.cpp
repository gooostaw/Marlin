/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(DIRECT_STEPPING)

#include "../../feature/direct_stepping.h"

#include "../gcode.h"
#include "../../module/planner.h"

/**
 * G6: Direct Stepper Move
 */
void GcodeSuite::G6() {
  // TODO: feedrate support?
  if (parser.seen('R'))
    planner.last_page_step_rate = parser.value_ulong();

  if (!DirectStepping::Config::DIRECTIONAL) {
    if (parser.seen('X')) planner.last_page_dir.x = !!parser.value_byte();
    if (parser.seen('Y')) planner.last_page_dir.y = !!parser.value_byte();
    if (parser.seen('Z')) planner.last_page_dir.z = !!parser.value_byte();
    if (parser.seen('E')) planner.last_page_dir.e = !!parser.value_byte();
  }

  // No index means we just set the state
  if (!parser.seen('I')) return;

  // No speed is set, can't schedule the move
  if (!planner.last_page_step_rate) return;

  const page_idx_t page_idx = (page_idx_t) parser.value_ulong();

  uint16_t num_steps = DirectStepping::Config::TOTAL_STEPS;
  if (parser.seen('S')) num_steps = parser.value_ushort();

  planner.buffer_page(page_idx, 0, num_steps);
  reset_stepper_timeout();
}

#endif // DIRECT_STEPPING

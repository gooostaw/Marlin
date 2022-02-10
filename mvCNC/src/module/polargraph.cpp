/**
 * Modern Vintage CNC Firmware
*/

/**
 * polargraph.cpp
 */

#include "../inc/mvCNCConfig.h"

#if ENABLED(POLARGRAPH)

#include "polargraph.h"
#include "motion.h"

// For homing:
#include "planner.h"
#include "endstops.h"
#include "../lcd/mvcncui.h"
#include "../mvCNCCore.h"

float segments_per_second; // Initialized by settings.load()

void inverse_kinematics(const xyz_pos_t &raw) {
  const float x1 = raw.x - (X_MIN_POS), x2 = (X_MAX_POS) - raw.x, y = raw.y - (Y_MAX_POS);
  delta.set(HYPOT(x1, y), HYPOT(x2, y), raw.z);
}

#endif // POLARGRAPH

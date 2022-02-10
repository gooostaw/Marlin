/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * polargraph.h - Polargraph-specific functions
 */

#include "../core/types.h"
#include "../core/macros.h"

extern float segments_per_second;

void inverse_kinematics(const xyz_pos_t &raw);

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * scara.h - SCARA-specific functions
 */

#include "../core/macros.h"

extern float segments_per_second;

#if ENABLED(AXEL_TPARA)

  float constexpr L1 = TPARA_LINKAGE_1, L2 = TPARA_LINKAGE_2,   // Float constants for Robot arm calculations
                  L1_2 = sq(float(L1)), L1_2_2 = 2.0 * L1_2,
                  L2_2 = sq(float(L2));

  void forward_kinematics(const_float_t a, const_float_t b, const_float_t c);
  void home_TPARA();

#else

  float constexpr L1 = SCARA_LINKAGE_1, L2 = SCARA_LINKAGE_2,   // Float constants for SCARA calculations
                  L1_2 = sq(float(L1)), L1_2_2 = 2.0 * L1_2,
                  L2_2 = sq(float(L2));

  void forward_kinematics(const_float_t a, const_float_t b);

#endif

void inverse_kinematics(const xyz_pos_t &raw);
void scara_set_axis_is_at_home(const AxisEnum axis);
void scara_report_positions();

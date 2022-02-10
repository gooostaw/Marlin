/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfigPre.h"

extern xy_pos_t bilinear_grid_spacing, bilinear_start;
extern xy_float_t bilinear_grid_factor;
extern bed_mesh_t z_values;
float bilinear_z_offset(const xy_pos_t &raw);

void extrapolate_unprobed_bed_level();
void print_bilinear_leveling_grid();
void refresh_bed_level();
#if ENABLED(ABL_BILINEAR_SUBDIVISION)
  void print_bilinear_leveling_grid_virt();
  void bed_level_virt_interpolate();
#endif

#if IS_CARTESIAN && DISABLED(SEGMENT_LEVELED_MOVES)
  void bilinear_line_to_destination(const_feedRate_t scaled_fr_mm_s, uint16_t x_splits=0xFFFF, uint16_t y_splits=0xFFFF);
#endif

#define _GET_MESH_X(I) float(bilinear_start.x + (I) * bilinear_grid_spacing.x)
#define _GET_MESH_Y(J) float(bilinear_start.y + (J) * bilinear_grid_spacing.y)
#define Z_VALUES_ARR  z_values

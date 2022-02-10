/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(MESH_BED_LEVELING)

  #include "../bedlevel.h"

  #include "../../../module/motion.h"

  #if ENABLED(EXTENSIBLE_UI)
    #include "../../../lcd/extui/ui_api.h"
  #endif

  mesh_bed_leveling mbl;

  float mesh_bed_leveling::z_offset,
        mesh_bed_leveling::z_values[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y],
        mesh_bed_leveling::index_to_xpos[GRID_MAX_POINTS_X],
        mesh_bed_leveling::index_to_ypos[GRID_MAX_POINTS_Y];

  mesh_bed_leveling::mesh_bed_leveling() {
    LOOP_L_N(i, GRID_MAX_POINTS_X)
      index_to_xpos[i] = MESH_MIN_X + i * (MESH_X_DIST);
    LOOP_L_N(i, GRID_MAX_POINTS_Y)
      index_to_ypos[i] = MESH_MIN_Y + i * (MESH_Y_DIST);
    reset();
  }

  void mesh_bed_leveling::reset() {
    z_offset = 0;
    ZERO(z_values);
    #if ENABLED(EXTENSIBLE_UI)
      GRID_LOOP(x, y) ExtUI::onMeshUpdate(x, y, 0);
    #endif
  }

  #if IS_CARTESIAN && DISABLED(SEGMENT_LEVELED_MOVES)

    /**
     * Prepare a mesh-leveled linear move in a Cartesian setup,
     * splitting the move where it crosses mesh borders.
     */
    void mesh_bed_leveling::line_to_destination(const_feedRate_t scaled_fr_mm_s, uint8_t x_splits, uint8_t y_splits) {
      // Get current and destination cells for this line
      xy_int8_t scel = cell_indexes(current_position), ecel = cell_indexes(destination);
      NOMORE(scel.x, GRID_MAX_CELLS_X - 1);
      NOMORE(scel.y, GRID_MAX_CELLS_Y - 1);
      NOMORE(ecel.x, GRID_MAX_CELLS_X - 1);
      NOMORE(ecel.y, GRID_MAX_CELLS_Y - 1);

      // Start and end in the same cell? No split needed.
      if (scel == ecel) {
        current_position = destination;
        line_to_current_position(scaled_fr_mm_s);
        return;
      }

      #define MBL_SEGMENT_END(A) (current_position.A + (destination.A - current_position.A) * normalized_dist)

      float normalized_dist;
      xyze_pos_t dest;
      const int8_t gcx = _MAX(scel.x, ecel.x), gcy = _MAX(scel.y, ecel.y);

      // Crosses on the X and not already split on this X?
      // The x_splits flags are insurance against rounding errors.
      if (ecel.x != scel.x && TEST(x_splits, gcx)) {
        // Split on the X grid line
        CBI(x_splits, gcx);
        dest = destination;
        destination.x = index_to_xpos[gcx];
        normalized_dist = (destination.x - current_position.x) / (dest.x - current_position.x);
        destination.y = MBL_SEGMENT_END(y);
      }
      // Crosses on the Y and not already split on this Y?
      else if (ecel.y != scel.y && TEST(y_splits, gcy)) {
        // Split on the Y grid line
        CBI(y_splits, gcy);
        dest = destination;
        destination.y = index_to_ypos[gcy];
        normalized_dist = (destination.y - current_position.y) / (dest.y - current_position.y);
        destination.x = MBL_SEGMENT_END(x);
      }
      else {
        // Must already have been split on these border(s)
        // This should be a rare case.
        current_position = destination;
        line_to_current_position(scaled_fr_mm_s);
        return;
      }

      destination.z = MBL_SEGMENT_END(z);
      destination.e = MBL_SEGMENT_END(e);

      // Do the split and look for more borders
      line_to_destination(scaled_fr_mm_s, x_splits, y_splits);

      // Restore destination from stack
      destination = dest;
      line_to_destination(scaled_fr_mm_s, x_splits, y_splits);
    }

  #endif // IS_CARTESIAN && !SEGMENT_LEVELED_MOVES

  void mesh_bed_leveling::report_mesh() {
    SERIAL_ECHOPAIR_F(STRINGIFY(GRID_MAX_POINTS_X) "x" STRINGIFY(GRID_MAX_POINTS_Y) " mesh. Z offset: ", z_offset, 5);
    SERIAL_ECHOLNPGM("\nMeasured points:");
    print_2d_array(GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y, 5,
      [](const uint8_t ix, const uint8_t iy) { return z_values[ix][iy]; }
    );
  }

#endif // MESH_BED_LEVELING

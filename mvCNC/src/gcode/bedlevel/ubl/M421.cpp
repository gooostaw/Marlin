/**
 * Modern Vintage CNC Firmware
*/

/**
 * M421.cpp - Unified Bed Leveling
 */

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(AUTO_BED_LEVELING_UBL)

#include "../../gcode.h"
#include "../../../feature/bedlevel/bedlevel.h"

#if ENABLED(EXTENSIBLE_UI)
  #include "../../../lcd/extui/ui_api.h"
#elif ENABLED(DWIN_CREALITY_LCD_ENHANCED)
  #include "../../../lcd/e3v2/proui/dwin.h"
#endif

/**
 * M421: Set a single Mesh Bed Leveling Z coordinate
 *
 * Usage:
 *   M421 I<xindex> J<yindex> Z<linear>  : Set the Mesh Point IJ to the Z value
 *   M421 I<xindex> J<yindex> Q<offset>  : Add the Q value to the Mesh Point IJ
 *   M421 I<xindex> J<yindex> N          : Set the Mesh Point IJ to NAN (not set)
 *   M421 C Z<linear>                    : Set the closest Mesh Point to the Z value
 *   M421 C Q<offset>                    : Add the Q value to the closest Mesh Point
 */
void GcodeSuite::M421() {
  xy_int8_t ij = { int8_t(parser.intval('I', -1)), int8_t(parser.intval('J', -1)) };
  const bool hasI = ij.x >= 0,
             hasJ = ij.y >= 0,
             hasC = parser.seen_test('C'),
             hasN = parser.seen_test('N'),
             hasZ = parser.seen('Z'),
             hasQ = !hasZ && parser.seen('Q');

  if (hasC) ij = ubl.find_closest_mesh_point_of_type(CLOSEST, current_position);

  // Test for bad parameter combinations
  if (int(hasC) + int(hasI && hasJ) != 1 || !(hasZ || hasQ || hasN))
    SERIAL_ERROR_MSG(STR_ERR_M421_PARAMETERS);

  // Test for I J out of range
  else if (!WITHIN(ij.x, 0, GRID_MAX_POINTS_X - 1) || !WITHIN(ij.y, 0, GRID_MAX_POINTS_Y - 1))
    SERIAL_ERROR_MSG(STR_ERR_MESH_XY);
  else {
    float &zval = ubl.z_values[ij.x][ij.y];                               // Altering this Mesh Point
    zval = hasN ? NAN : parser.value_linear_units() + (hasQ ? zval : 0);  // N=NAN, Z=NEWVAL, or Q=ADDVAL
    TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(ij.x, ij.y, zval));          // Ping ExtUI in case it's showing the mesh
    TERN_(DWIN_CREALITY_LCD_ENHANCED, DWIN_MeshUpdate(ij.x, ij.y, zval));
  }
}

#endif // AUTO_BED_LEVELING_UBL

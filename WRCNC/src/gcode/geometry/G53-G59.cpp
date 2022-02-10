/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../module/motion.h"

#if ENABLED(CNC_COORDINATE_SYSTEMS)

#include "../../module/stepper.h"

// #define DEBUG_G53

/**
 * Select a coordinate system and update the workspace offset.
 * System index -1 is used to specify machine-native.
 */
bool GcodeSuite::select_coordinate_system(const int8_t _new) {
  if (active_coordinate_system == _new) return false;
  active_coordinate_system = _new;
  xyz_float_t new_offset{0};
  if (WITHIN(_new, 0, MAX_COORDINATE_SYSTEMS - 1))
    new_offset = coordinate_system[_new];
  LOOP_LINEAR_AXES(i) {
    if (position_shift[i] != new_offset[i]) {
      position_shift[i] = new_offset[i];
      update_workspace_offset((AxisEnum)i);
    }
  }
  return true;
}

/**
 * G53: Apply native workspace to the current move
 *
 * In CNC G-code G53 is a modifier.
 * It precedes a movement command (or other modifiers) on the same line.
 * This is the first command to use parser.chain() to make this possible.
 *
 * WRCNC also uses G53 on a line by itself to go back to native space.
 */
void GcodeSuite::G53() {
  const int8_t old_system = active_coordinate_system;
  select_coordinate_system(-1);   // Always remove workspace offsets
  #ifdef DEBUG_G53
    SERIAL_ECHOLNPGM("Go to native space");
    report_current_position();
  #endif

  if (parser.chain()) {       // Command to chain?
    process_parsed_command(); // ...process the chained command
    select_coordinate_system(old_system);
    #ifdef DEBUG_G53
      SERIAL_ECHOLNPGM("Go back to workspace ", old_system);
      report_current_position();
    #endif
  }
}

/**
 * G54-G59.3: Select a new workspace
 *
 * A workspace is an XYZ offset to the machine native space.
 * All workspaces default to 0,0,0 at start, or with EEPROM
 * support they may be restored from a previous session.
 *
 * G92 is used to set the current workspace's offset.
 */
void G54_59(uint8_t subcode=0) {
  const int8_t _space = parser.codenum - 54 + subcode;
  if (gcode.select_coordinate_system(_space)) {
    SERIAL_ECHOLNPGM("Select workspace ", _space);
    report_current_position();
  }
}
void GcodeSuite::G54() { G54_59(); }
void GcodeSuite::G55() { G54_59(); }
void GcodeSuite::G56() { G54_59(); }
void GcodeSuite::G57() { G54_59(); }
void GcodeSuite::G58() { G54_59(); }
void GcodeSuite::G59() { G54_59(parser.subcode); }

#endif // CNC_COORDINATE_SYSTEMS

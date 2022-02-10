/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(CNC_WORKSPACE_PLANES)

#include "../gcode.h"

inline void report_workspace_plane() {
  SERIAL_ECHO_START();
  SERIAL_ECHOPGM("Workspace Plane ");
  SERIAL_ECHOF(
      gcode.workspace_plane == GcodeSuite::PLANE_YZ ? F("YZ\n")
    : gcode.workspace_plane == GcodeSuite::PLANE_ZX ? F("ZX\n")
                                                    : F("XY\n")
  );
}

inline void set_workspace_plane(const GcodeSuite::WorkspacePlane plane) {
  gcode.workspace_plane = plane;
  if (DEBUGGING(INFO)) report_workspace_plane();
}

/**
 * G17: Select Plane XY
 * G18: Select Plane ZX
 * G19: Select Plane YZ
 */
void GcodeSuite::G17() { set_workspace_plane(PLANE_XY); }
void GcodeSuite::G18() { set_workspace_plane(PLANE_ZX); }
void GcodeSuite::G19() { set_workspace_plane(PLANE_YZ); }

#endif // CNC_WORKSPACE_PLANES

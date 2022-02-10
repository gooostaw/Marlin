/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfigPre.h"

#if HAS_EXTRUDERS

#include "../gcode.h"

/**
 * M82: Set E codes absolute (default)
 */
void GcodeSuite::M82() { set_e_absolute(); }

/**
 * M83: Set E codes relative while in Absolute Coordinates (G90) mode
 */
void GcodeSuite::M83() { set_e_relative(); }

#endif // HAS_EXTRUDERS

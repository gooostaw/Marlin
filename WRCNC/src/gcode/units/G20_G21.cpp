/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if ENABLED(INCH_MODE_SUPPORT)

#include "../gcode.h"

/**
 * G20: Set input mode to inches
 */
void GcodeSuite::G20() { parser.set_input_linear_units(LINEARUNIT_INCH); }

/**
 * G21: Set input mode to millimeters
 */
void GcodeSuite::G21() { parser.set_input_linear_units(LINEARUNIT_MM); }

#endif // INCH_MODE_SUPPORT

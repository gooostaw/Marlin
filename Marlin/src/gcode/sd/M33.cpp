/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(LONG_FILENAME_HOST_SUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M33: Get the long full path of a file or folder
 *
 * Parameters:
 *   <dospath> Case-insensitive DOS-style path to a file or folder
 *
 * Example:
 *   M33 miscel~1/armchair/armcha~1.gco
 *
 * Output:
 *   /Miscellaneous/Armchair/Armchair.gcode
 */
void GcodeSuite::M33() {

  card.printLongPath(parser.string_arg);

}

#endif // LONG_FILENAME_HOST_SUPPORT

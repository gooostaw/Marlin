/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M928: Start SD Logging
 */
void GcodeSuite::M928() {

  card.openLogFile(parser.string_arg);

}

#endif // SDSUPPORT

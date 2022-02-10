/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(EXPECTED_PRINTER_CHECK)

#include "../gcode.h"
#include "../../MarlinCore.h"

/**
 * M16: Expected Printer Check
 */
void GcodeSuite::M16() {

  if (strcmp_P(parser.string_arg, PSTR(MACHINE_NAME)))
    kill(GET_TEXT_F(MSG_KILL_EXPECTED_PRINTER));

}

#endif

/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if HAS_STATUS_MESSAGE

#include "../gcode.h"
#include "../../lcd/mvcncui.h"

/**
 * M117: Set LCD Status Message
 */
void GcodeSuite::M117() {

  if (parser.string_arg && parser.string_arg[0])
    ui.set_status(parser.string_arg);
  else
    ui.reset_status();

}

#endif // HAS_STATUS_MESSAGE

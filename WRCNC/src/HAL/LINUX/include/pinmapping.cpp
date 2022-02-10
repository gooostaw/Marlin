/**
 * Webber Ranch CNC Firmware
*/
#ifdef __PLAT_LINUX__

#include <pinmapping.h>

#include "../../../gcode/parser.h"

int16_t PARSED_PIN_INDEX(const char code, const int16_t dval) {
  return parser.intval(code, dval);
}

#endif // __PLAT_LINUX__

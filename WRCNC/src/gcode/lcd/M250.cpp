/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if HAS_LCD_CONTRAST

#include "../gcode.h"
#include "../../lcd/wrcncui.h"

/**
 * M250: Read and optionally set the LCD contrast
 */
void GcodeSuite::M250() {
  if (LCD_CONTRAST_MIN < LCD_CONTRAST_MAX && parser.seenval('C'))
    ui.set_contrast(parser.value_byte());
  else
    M250_report();
}

void GcodeSuite::M250_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_LCD_CONTRAST));
  SERIAL_ECHOLNPGM("  M250 C", ui.contrast);
}

#endif // HAS_LCD_CONTRAST

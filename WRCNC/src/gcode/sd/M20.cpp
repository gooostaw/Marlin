/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M20: List SD card to serial output
 */
void GcodeSuite::M20() {
  if (card.flag.mounted) {
    SERIAL_ECHOLNPGM(STR_BEGIN_FILE_LIST);
    card.ls(
      TERN_(CUSTOM_FIRMWARE_UPLOAD, parser.boolval('F'))
      #if BOTH(CUSTOM_FIRMWARE_UPLOAD, LONG_FILENAME_HOST_SUPPORT)
        ,
      #endif
      TERN_(LONG_FILENAME_HOST_SUPPORT, parser.boolval('L'))
    );
    SERIAL_ECHOLNPGM(STR_END_FILE_LIST);
  }
  else
    SERIAL_ECHO_MSG(STR_NO_MEDIA);
}

#endif // SDSUPPORT

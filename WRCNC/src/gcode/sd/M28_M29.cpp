/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

#if HAS_MULTI_SERIAL
  #include "../queue.h"
#endif

/**
 * M28: Start SD Write
 */
void GcodeSuite::M28() {

  #if ENABLED(BINARY_FILE_TRANSFER)

    bool binary_mode = false;
    char *p = parser.string_arg;
    if (p[0] == 'B' && NUMERIC(p[1])) {
      binary_mode = p[1] > '0';
      p += 2;
      while (*p == ' ') ++p;
    }

    // Binary transfer mode
    if ((card.flag.binary_mode = binary_mode)) {
      SERIAL_ECHO_MSG("Switching to Binary Protocol");
      TERN_(HAS_MULTI_SERIAL, card.transfer_port_index = queue.ring_buffer.command_port().index);
    }
    else
      card.openFileWrite(p);

  #else

    card.openFileWrite(parser.string_arg);

  #endif
}

/**
 * M29: Stop SD Write
 * (Processed in write-to-file routine)
 */
void GcodeSuite::M29() {
  card.flag.saving = false;
}

#endif // SDSUPPORT

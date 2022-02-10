/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfig.h"

#if ENABLED(GCODE_MACROS)

#include "../../gcode.h"
#include "../../queue.h"
#include "../../parser.h"

char gcode_macros[GCODE_MACROS_SLOTS][GCODE_MACROS_SLOT_SIZE + 1] = {{ 0 }};

/**
 * M810_819: Set/execute a G-code macro.
 *
 * Usage:
 *   M810 <command>|...   Set Macro 0 to the given commands, separated by the pipe character
 *   M810                 Execute Macro 0
 */
void GcodeSuite::M810_819() {
  const uint8_t index = parser.codenum - 810;
  if (index >= GCODE_MACROS_SLOTS) return;

  const size_t len = strlen(parser.string_arg);

  if (len) {
    // Set a macro
    if (len > GCODE_MACROS_SLOT_SIZE)
      SERIAL_ERROR_MSG("Macro too long.");
    else {
      char c, *s = parser.string_arg, *d = gcode_macros[index];
      do {
        c = *s++;
        *d++ = c == '|' ? '\n' : c;
      } while (c);
    }
  }
  else {
    // Execute a macro
    char * const cmd = gcode_macros[index];
    if (strlen(cmd)) process_subcommands_now(cmd);
  }
}

#endif // GCODE_MACROS

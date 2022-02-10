/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfig.h"

#if ENABLED(GCODE_REPEAT_MARKERS)

//#define DEBUG_GCODE_REPEAT_MARKERS

#include "repeat.h"

#include "../gcode/gcode.h"
#include "../sd/cardreader.h"

#define DEBUG_OUT ENABLED(DEBUG_GCODE_REPEAT_MARKERS)
#include "../core/debug_out.h"

repeat_marker_t Repeat::marker[MAX_REPEAT_NESTING];
uint8_t Repeat::index;

void Repeat::add_marker(const uint32_t sdpos, const uint16_t count) {
  if (index >= MAX_REPEAT_NESTING)
    SERIAL_ECHO_MSG("!Too many markers.");
  else {
    marker[index].sdpos = sdpos;
    marker[index].counter = count ?: -1;
    index++;
    DEBUG_ECHOLNPGM("Add Marker ", index, " at ", sdpos, " (", count, ")");
  }
}

void Repeat::loop() {
  if (!index)                           // No marker?
    SERIAL_ECHO_MSG("!No marker set."); //  Inform the user.
  else {
    const uint8_t ind = index - 1;      // Active marker's index
    if (!marker[ind].counter) {         // Did its counter run out?
      DEBUG_ECHOLNPGM("Pass Marker ", index);
      index--;                          //  Carry on. Previous marker on the next 'M808'.
    }
    else {
      card.setIndex(marker[ind].sdpos); // Loop back to the marker.
      if (marker[ind].counter > 0)      // Ignore a negative (or zero) counter.
        --marker[ind].counter;          // Decrement the counter. If zero this 'M808' will be skipped next time.
      DEBUG_ECHOLNPGM("Goto Marker ", index, " at ", marker[ind].sdpos, " (", marker[ind].counter, ")");
    }
  }
}

void Repeat::cancel() { LOOP_L_N(i, index) marker[i].counter = 0; }

void Repeat::early_parse_M808(char * const cmd) {
  if (is_command_M808(cmd)) {
    DEBUG_ECHOLNPGM("Parsing \"", cmd, "\"");
    parser.parse(cmd);
    if (parser.seen('L'))
      add_marker(card.getIndex(), parser.value_ushort());
    else
      Repeat::loop();
  }
}

#endif // GCODE_REPEAT_MARKERS

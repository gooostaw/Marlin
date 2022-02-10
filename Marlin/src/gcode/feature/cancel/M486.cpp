/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfig.h"

#if ENABLED(CANCEL_OBJECTS)

#include "../../gcode.h"
#include "../../../feature/cancel_object.h"

/**
 * M486: A simple interface to cancel objects
 *
 *   T[count] : Reset objects and/or set the count
 *   S<index> : Start an object with the given index
 *   P<index> : Cancel the object with the given index
 *   U<index> : Un-cancel object with the given index
 *   C        : Cancel the current object (the last index given by S<index>)
 *   S-1      : Start a non-object like a brim or purge tower that should always print
 */
void GcodeSuite::M486() {

  if (parser.seen('T')) {
    cancelable.reset();
    cancelable.object_count = parser.intval('T', 1);
  }

  if (parser.seen('S'))
    cancelable.set_active_object(parser.value_int());

  if (parser.seen('C')) cancelable.cancel_active_object();

  if (parser.seen('P')) cancelable.cancel_object(parser.value_int());

  if (parser.seen('U')) cancelable.uncancel_object(parser.value_int());
}

#endif // CANCEL_OBJECTS

/**
 * Webber Ranch CNC Firmware
*/

#include "../inc/WRCNCConfig.h"

#if ENABLED(CANCEL_OBJECTS)

#include "cancel_object.h"
#include "../gcode/gcode.h"
#include "../lcd/wrcncui.h"

CancelObject cancelable;

int8_t CancelObject::object_count, // = 0
       CancelObject::active_object = -1;
uint32_t CancelObject::canceled; // = 0x0000
bool CancelObject::skipping; // = false

void CancelObject::set_active_object(const int8_t obj) {
  active_object = obj;
  if (WITHIN(obj, 0, 31)) {
    if (obj >= object_count) object_count = obj + 1;
    skipping = TEST(canceled, obj);
  }
  else
    skipping = false;

  #if BOTH(HAS_STATUS_MESSAGE, CANCEL_OBJECTS_REPORTING)
    if (active_object >= 0)
      ui.status_printf(0, F(S_FMT " %i"), GET_TEXT(MSG_PRINTING_OBJECT), int(active_object));
    else
      ui.reset_status();
  #endif
}

void CancelObject::cancel_object(const int8_t obj) {
  if (WITHIN(obj, 0, 31)) {
    SBI(canceled, obj);
    if (obj == active_object) skipping = true;
  }
}

void CancelObject::uncancel_object(const int8_t obj) {
  if (WITHIN(obj, 0, 31)) {
    CBI(canceled, obj);
    if (obj == active_object) skipping = false;
  }
}

void CancelObject::report() {
  if (active_object >= 0)
    SERIAL_ECHO_MSG("Active Object: ", active_object);

  if (canceled) {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Canceled:");
    for (int i = 0; i < object_count; i++)
      if (TEST(canceled, i)) { SERIAL_CHAR(' '); SERIAL_ECHO(i); }
    SERIAL_EOL();
  }
}

#endif // CANCEL_OBJECTS

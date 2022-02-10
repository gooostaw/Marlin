/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(PASSWORD_FEATURE)

#include "../../../feature/password/password.h"
#include "../../../core/serial.h"
#include "../../gcode.h"

//
// M510: Lock Printer
//
void GcodeSuite::M510() {
  password.lock_machine();
}

//
// M511: Unlock Printer
//
#if ENABLED(PASSWORD_UNLOCK_GCODE)

  void GcodeSuite::M511() {
    if (password.is_locked) {
      password.value_entry = parser.ulongval('P');
      password.authentication_check();
    }
  }

#endif // PASSWORD_UNLOCK_GCODE

//
// M512: Set/Change/Remove Password
//
#if ENABLED(PASSWORD_CHANGE_GCODE)

  void GcodeSuite::M512() {
    if (password.is_set && parser.ulongval('P') != password.value) {
      SERIAL_ECHOLNPGM(STR_WRONG_PASSWORD);
      return;
    }

    if (parser.seenval('S')) {
      password.value_entry = parser.ulongval('S');

      if (password.value_entry < CAT(1e, PASSWORD_LENGTH)) {
        password.is_set = true;
        password.value = password.value_entry;
        SERIAL_ECHOLNPGM(STR_PASSWORD_SET, password.value); // TODO: Update password.string
      }
      else
        SERIAL_ECHOLNPGM(STR_PASSWORD_TOO_LONG);
    }
    else {
      password.is_set = false;
      SERIAL_ECHOLNPGM(STR_PASSWORD_REMOVED);
    }
    SERIAL_ECHOLNPGM(STR_REMINDER_SAVE_SETTINGS);
  }

#endif // PASSWORD_CHANGE_GCODE

#endif // PASSWORD_FEATURE

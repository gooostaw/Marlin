/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(PASSWORD_FEATURE)

#include "password.h"
#include "../../gcode/gcode.h"
#include "../../core/serial.h"

Password password;

// public:
bool     Password::is_set, Password::is_locked, Password::did_first_run; // = false
uint32_t Password::value, Password::value_entry;

//
// Authenticate user with password.
// Called from Setup, after SD Prinitng Stops/Aborts, and M510
//
void Password::lock_machine() {
  is_locked = true;
  TERN_(HAS_MARLINUI_MENU, authenticate_user(ui.status_screen, screen_password_entry));
}

//
// Authentication check
//
void Password::authentication_check() {
  if (value_entry == value) {
    is_locked = false;
    did_first_run = true;
  }
  else {
    is_locked = true;
    SERIAL_ECHOLNPGM(STR_WRONG_PASSWORD);
  }
  TERN_(HAS_MARLINUI_MENU, authentication_done());
}

#endif // PASSWORD_FEATURE

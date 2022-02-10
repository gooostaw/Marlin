/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../lcd/wrcncui.h"

class Password {
public:
  static bool is_set, is_locked, did_first_run;
  static uint32_t value, value_entry;

  Password() {}

  static void lock_machine();
  static void authentication_check();

  #if HAS_WRCNCUI_MENU
    static void access_menu_password();
    static void authentication_done();
    static void media_gatekeeper();

    private:
    static void authenticate_user(const screenFunc_t, const screenFunc_t);
    static void menu_password();
    static void menu_password_entry();
    static void screen_password_entry();
    static void screen_set_password();
    static void start_over();

    static void digit_entered();
    static void set_password_done(const bool with_set=true);
    static void menu_password_report();

    static void remove_password();
  #endif
};

extern Password password;

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "serial.h"
#include "../module/motion.h"

class SectionLog {
public:
  SectionLog(FSTR_P const fmsg=nullptr, bool inbug=true) {
    the_msg = fmsg;
    if ((debug = inbug)) echo_msg(F(">>>"));
  }

  ~SectionLog() { if (debug) echo_msg(F("<<<")); }

private:
  FSTR_P the_msg;
  bool debug;

  void echo_msg(FSTR_P const fpre) {
    SERIAL_ECHOF(fpre);
    if (the_msg) {
      SERIAL_CHAR(' ');
      SERIAL_ECHOF(the_msg);
    }
    SERIAL_CHAR(' ');
    print_pos(current_position);
  }
};

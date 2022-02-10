/**
 * Webber Ranch CNC Firmware
*/
#pragma once

class ClosedLoop {
public:
  static void init();
  static void set(const byte val);
};

extern ClosedLoop closedloop;

#define CLOSED_LOOP_WAITING() (READ(CLOSED_LOOP_ENABLE_PIN) && !READ(CLOSED_LOOP_MOVE_COMPLETE_PIN))

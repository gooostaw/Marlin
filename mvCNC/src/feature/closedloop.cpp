/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfig.h"

#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)

#if !PIN_EXISTS(CLOSED_LOOP_ENABLE) || !PIN_EXISTS(CLOSED_LOOP_MOVE_COMPLETE)
  #error "CLOSED_LOOP_ENABLE_PIN and CLOSED_LOOP_MOVE_COMPLETE_PIN are required for EXTERNAL_CLOSED_LOOP_CONTROLLER."
#endif

#include "closedloop.h"

ClosedLoop closedloop;

void ClosedLoop::init() {
  OUT_WRITE(CLOSED_LOOP_ENABLE_PIN, LOW);
  SET_INPUT_PULLUP(CLOSED_LOOP_MOVE_COMPLETE_PIN);
}

void ClosedLoop::set(const byte val) {
  OUT_WRITE(CLOSED_LOOP_ENABLE_PIN, val);
}

#endif // EXTERNAL_CLOSED_LOOP_CONTROLLER

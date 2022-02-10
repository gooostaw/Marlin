/**
 * Webber Ranch CNC Firmware
*/

/**
 * feature/pause.cpp - Pause feature support functions
 * This may be combined with related G-codes if features are consolidated.
 */

#include "../inc/WRCNCConfig.h"

#if HAS_FANMUX

#include "fanmux.h"

void fanmux_switch(const uint8_t e) {
  WRITE(FANMUX0_PIN, TEST(e, 0) ? HIGH : LOW);
  #if PIN_EXISTS(FANMUX1)
    WRITE(FANMUX1_PIN, TEST(e, 1) ? HIGH : LOW);
    #if PIN_EXISTS(FANMUX2)
      WRITE(FANMUX2_PIN, TEST(e, 2) ? HIGH : LOW);
    #endif
  #endif
}

void fanmux_init() {
  SET_OUTPUT(FANMUX0_PIN);
  #if PIN_EXISTS(FANMUX1)
    SET_OUTPUT(FANMUX1_PIN);
    #if PIN_EXISTS(FANMUX2)
      SET_OUTPUT(FANMUX2_PIN);
    #endif
  #endif
  fanmux_switch(0);
}

#endif // HAS_FANMUX

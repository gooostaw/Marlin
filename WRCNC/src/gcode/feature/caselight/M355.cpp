/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/WRCNCConfig.h"

#if ENABLED(CASE_LIGHT_ENABLE)

#include "../../../feature/caselight.h"
#include "../../gcode.h"

/**
 * M355: Turn case light on/off and set brightness
 *
 *   P<byte>  Set case light brightness (PWM pin required - ignored otherwise)
 *
 *   S<bool>  Set case light on/off
 *
 *   When S turns on the light on a PWM pin then the current brightness level is used/restored
 *
 *   M355 P200 S0 turns off the light & sets the brightness level
 *   M355 S1 turns on the light with a brightness of 200 (assuming a PWM pin)
 */
void GcodeSuite::M355() {
  bool didset = false;
  #if CASELIGHT_USES_BRIGHTNESS
    if (parser.seenval('P')) {
      didset = true;
      caselight.brightness = parser.value_byte();
    }
  #endif
  const bool sflag = parser.seenval('S');
  if (sflag) {
    didset = true;
    caselight.on = parser.value_bool();
  }
  if (didset) caselight.update(sflag);

  // Always report case light status
  SERIAL_ECHO_START();
  SERIAL_ECHOPGM("Case light: ");
  if (!caselight.on)
    SERIAL_ECHOLNPGM(STR_OFF);
  else {
    #if CASELIGHT_USES_BRIGHTNESS
      if (TERN(CASE_LIGHT_USE_NEOPIXEL, true, TERN0(NEED_CASE_LIGHT_PIN, PWM_PIN(CASE_LIGHT_PIN)))) {
        SERIAL_ECHOLN(int(caselight.brightness));
        return;
      }
    #endif
    SERIAL_ECHOLNPGM(STR_ON);
  }
}

#endif // CASE_LIGHT_ENABLE

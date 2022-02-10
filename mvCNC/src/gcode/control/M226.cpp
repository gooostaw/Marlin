/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(DIRECT_PIN_CONTROL)

#include "../gcode.h"
#include "../../mvCNCCore.h" // for pin_is_protected and idle()
#include "../../module/stepper.h"

void protected_pin_err();

/**
 * M226: Wait until the specified pin reaches the state required (M226 P<pin> S<state>)
 */
void GcodeSuite::M226() {
  if (parser.seen('P')) {
    const int pin_number = PARSED_PIN_INDEX('P', 0),
              pin_state = parser.intval('S', -1); // required pin state - default is inverted
    const pin_t pin = GET_PIN_MAP_PIN(pin_number);

    if (WITHIN(pin_state, -1, 1) && pin > -1) {
      if (pin_is_protected(pin))
        protected_pin_err();
      else {
        int target = LOW;
        planner.synchronize();
        pinMode(pin, INPUT);
        switch (pin_state) {
          case 1: target = HIGH; break;
          case 0: target = LOW; break;
          case -1: target = !extDigitalRead(pin); break;
        }
        while (int(extDigitalRead(pin)) != target) idle();
      }
    } // pin_state -1 0 1 && pin > -1
  } // parser.seen('P')
}

#endif // DIRECT_PIN_CONTROL

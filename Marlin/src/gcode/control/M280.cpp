/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "../gcode.h"
#include "../../module/servo.h"
#include "../../module/planner.h"

/**
 * M280: Get or set servo position.
 *  P<index> - Servo index
 *  S<angle> - Angle to set, omit to read current angle, or use -1 to detach
 *
 * With POLARGRAPH:
 *  T<ms>    - Duration of servo move
 */
void GcodeSuite::M280() {

  if (!parser.seenval('P')) return;

  TERN_(POLARGRAPH, planner.synchronize());

  const int servo_index = parser.value_int();
  if (WITHIN(servo_index, 0, NUM_SERVOS - 1)) {
    if (parser.seenval('S')) {
      const int anew = parser.value_int();
      if (anew >= 0) {
        #if ENABLED(POLARGRAPH)
          if (parser.seen('T')) { // (ms) Total duration of servo move
            const int16_t t = constrain(parser.value_int(), 0, 10000);
            const int aold = servo[servo_index].read();
            millis_t now = millis();
            const millis_t start = now, end = start + t;
            while (PENDING(now, end)) {
              safe_delay(50);
              now = _MIN(millis(), end);
              MOVE_SERVO(servo_index, LROUND(aold + (anew - aold) * (float(now - start) / t)));
            }
          }
        #endif // POLARGRAPH
        MOVE_SERVO(servo_index, anew);
      }
      else
        DETACH_SERVO(servo_index);
    }
    else
      SERIAL_ECHO_MSG(" Servo ", servo_index, ": ", servo[servo_index].read());
  }
  else
    SERIAL_ERROR_MSG("Servo ", servo_index, " out of range");

}

#endif // HAS_SERVOS

/**
 * Webber Ranch CNC Firmware
*/

/**
 * HAL Servo for Teensy 4.0 (IMXRT1062DVL6A) / 4.1 (IMXRT1062DVJ6A)
 */

#ifdef __IMXRT1062__

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "Servo.h"

int8_t libServo::attach(const int inPin) {
  if (inPin > 0) servoPin = inPin;
  return super::attach(servoPin);
}

int8_t libServo::attach(const int inPin, const int inMin, const int inMax) {
  if (inPin > 0) servoPin = inPin;
  return super::attach(servoPin, inMin, inMax);
}

void libServo::move(const int value) {
  constexpr uint16_t servo_delay[] = SERVO_DELAY;
  static_assert(COUNT(servo_delay) == NUM_SERVOS, "SERVO_DELAY must be an array NUM_SERVOS long.");
  if (attach(0) >= 0) {
    write(value);
    safe_delay(servo_delay[servoIndex]);
    TERN_(DEACTIVATE_SERVOS_AFTER_MOVE, detach());
  }
}

void libServo::detach() {
  // PWMServo library does not have detach() function
  //super::detach();
}

#endif // HAS_SERVOS
#endif // __IMXRT1062__

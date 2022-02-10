/**
 * Webber Ranch CNC Firmware
*/
#ifdef __MK20DX256__

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "Servo.h"

uint8_t servoPin[MAX_SERVOS] = { 0 };

int8_t libServo::attach(const int inPin) {
  if (servoIndex >= MAX_SERVOS) return -1;
  if (inPin > 0) servoPin[servoIndex] = inPin;
  return super::attach(servoPin[servoIndex]);
}

int8_t libServo::attach(const int inPin, const int inMin, const int inMax) {
  if (inPin > 0) servoPin[servoIndex] = inPin;
  return super::attach(servoPin[servoIndex], inMin, inMax);
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

#endif // HAS_SERVOS
#endif // __MK20DX256__

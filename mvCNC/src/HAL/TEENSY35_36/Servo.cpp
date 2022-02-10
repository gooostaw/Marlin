/**
 * Modern Vintage CNC Firmware
*/

/**
 * HAL Servo for Teensy 3.5 (MK64FX512) and Teensy 3.6 (MK66FX1M0)
 */

#if defined(__MK64FX512__) || defined(__MK66FX1M0__)

#include "../../inc/mvCNCConfig.h"

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
#endif // __MK64FX512__ || __MK66FX1M0__

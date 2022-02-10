/**
 * Webber Ranch CNC Firmware
*/
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "Servo.h"

// Adjacent channels (0/1, 2/3 etc.) share the same timer and therefore the same frequency and resolution settings on ESP32,
// so we only allocate servo channels up high to avoid side effects with regards to analogWrite (fans, leds, laser pwm etc.)
int Servo::channel_next_free = 12;

Servo::Servo() {
  channel = channel_next_free++;
}

int8_t Servo::attach(const int inPin) {
  if (channel >= CHANNEL_MAX_NUM) return -1;
  if (inPin > 0) pin = inPin;

  ledcSetup(channel, 50, 16); // channel X, 50 Hz, 16-bit depth
  ledcAttachPin(pin, channel);
  return true;
}

void Servo::detach() { ledcDetachPin(pin); }

int Servo::read() { return degrees; }

void Servo::write(int inDegrees) {
  degrees = constrain(inDegrees, MIN_ANGLE, MAX_ANGLE);
  int us = map(degrees, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int duty = map(us, 0, TAU_USEC, 0, MAX_COMPARE);
  ledcWrite(channel, duty);
}

void Servo::move(const int value) {
  constexpr uint16_t servo_delay[] = SERVO_DELAY;
  static_assert(COUNT(servo_delay) == NUM_SERVOS, "SERVO_DELAY must be an array NUM_SERVOS long.");
  if (attach(0) >= 0) {
    write(value);
    safe_delay(servo_delay[channel]);
    TERN_(DEACTIVATE_SERVOS_AFTER_MOVE, detach());
  }
}
#endif // HAS_SERVOS

#endif // ARDUINO_ARCH_ESP32

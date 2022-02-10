/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * HAL Servo for Teensy 3.5 (MK64FX512) and Teensy 3.6 (MK66FX1M0)
 */

#include <Servo.h>

// Inherit and expand on core Servo library
class libServo : public Servo {
  public:
    int8_t attach(const int pin);
    int8_t attach(const int pin, const int min, const int max);
    void move(const int value);
  private:
    typedef Servo super;
    uint16_t min_ticks;
    uint16_t max_ticks;
    uint8_t servoIndex; // Index into the channel data for this servo
};

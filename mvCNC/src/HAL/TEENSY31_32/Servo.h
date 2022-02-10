/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <Servo.h>

// Inherit and expand on the official library
class libServo : public Servo {
  public:
    int8_t attach(const int pin);
    int8_t attach(const int pin, const int min, const int max);
    void move(const int value);
  private:
    typedef Servo super;
    uint16_t min_ticks;
    uint16_t max_ticks;
    uint8_t servoIndex;               // index into the channel data for this servo
};

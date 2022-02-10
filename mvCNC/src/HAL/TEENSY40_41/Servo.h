/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * HAL Servo for Teensy 4.0 (IMXRT1062DVL6A) / 4.1 (IMXRT1062DVJ6A)
 */

#include <PWMServo.h>

// Inherit and expand on core Servo library
class libServo : public PWMServo {
  public:
    int8_t attach(const int pin);
    int8_t attach(const int pin, const int min, const int max);
    void move(const int value);
    void detach(void);
  private:
    typedef PWMServo super;
    uint8_t servoPin;
    uint16_t min_ticks;
    uint16_t max_ticks;
    uint8_t servoIndex; // Index into the channel data for this servo
};

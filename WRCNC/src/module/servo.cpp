/**
 * Webber Ranch CNC Firmware
*/

/**
 * module/servo.cpp
 */

#include "../inc/WRCNCConfig.h"

#if HAS_SERVOS

#include "servo.h"

HAL_SERVO_LIB servo[NUM_SERVOS];

#if ENABLED(EDITABLE_SERVO_ANGLES)
  uint16_t servo_angles[NUM_SERVOS][2];
#endif

void servo_init() {
  #if NUM_SERVOS >= 1 && HAS_SERVO_0
    servo[0].attach(SERVO0_PIN);
    DETACH_SERVO(0); // Just set up the pin. We don't have a position yet. Don't move to a random position.
  #endif
  #if NUM_SERVOS >= 2 && HAS_SERVO_1
    servo[1].attach(SERVO1_PIN);
    DETACH_SERVO(1);
  #endif
  #if NUM_SERVOS >= 3 && HAS_SERVO_2
    servo[2].attach(SERVO2_PIN);
    DETACH_SERVO(2);
  #endif
  #if NUM_SERVOS >= 4 && HAS_SERVO_3
    servo[3].attach(SERVO3_PIN);
    DETACH_SERVO(3);
  #endif
}

#endif // HAS_SERVOS

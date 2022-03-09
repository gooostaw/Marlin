/**
 * Modern Vintage CNC Firmware
 */
#pragma once

/**
 * Wii Nunchuck input / jogging
 */

#include "../inc/mvCNCConfigPre.h"
#include "../core/types.h"
#include "src/HAL/shared/Marduino.h"

#define NUNCHUK_BUFFER_SIZE 6
#ifndef WII_SLOW_DIVISER
  #define WII_SLOW_DIVISER 3  // Divide all speeds by value for standard (C unpressed) movements
#endif
#ifndef WII_X_LIMITS
  #define WII_X_LIMITS \
    { 0, 128 - 10, 128 + 10, 255 }  // min, deadzone start, deadzone end, max
#endif
#ifndef WII_Y_LIMITS
  #define WII_Y_LIMITS \
    { 0, 128 - 10, 128 + 10, 255 }
#endif

#ifndef WII_SLOW_DIVISER
  #define WII_SLOW_DIVISER 3
#endif

class WiiNunchuck {
 private:
#if ENABLED(WII_NUNCHUCK_DEBUG)
  void report();
  /**
   * @brief Prints debugging messages when `M111 S2` (DEBUG INFO) is set
   */
  static void prefix(FSTR_P const func);
  static void debug(FSTR_P const func, uint32_t number);
  static void debug(FSTR_P const func, float number);
  static void debug(FSTR_P const func, const char string[]);
#else
  static void debug(FSTR_P const, uint32_t) {}
  static void debug(FSTR_P const, float) {}
  static void debug(FSTR_P const, char[]) {}
#endif
  static void debug(FSTR_P const func, uint8_t value) { debug(func, (uint32_t)value); }
  static void debug(FSTR_P const func, uint16_t value) { debug(func, (uint32_t)value); }
  static void debug(FSTR_P const func, char string[]) { debug(func, (const char *)string); }

  void normalize(float &axis_jog, const int16_t joy_value, const int16_t (&wii_limits)[4]);
  void calculate(xyz_float_t &joy_value_normalized);
  void requestData();
  char decodeByte(const char);

 public:
  char _buffer[NUNCHUK_BUFFER_SIZE];
  uint8_t address = 0x52;
  bool connected  = false;
  bool simulation = false;
  bool enabled = ENABLED(WII_NUNCHUCK_ENABLED);

  void connect(uint8_t i2c_address = 0x52);
  bool update();
  void injectJogMoves();

  uint8_t joyX() { return _buffer[0]; }
  uint8_t joyY() { return _buffer[1]; }

  bool left() { return _buffer[0] < 50; }
  bool right() { return _buffer[0] > 200; }
  bool up() { return _buffer[1] > 200; }
  bool down() { return _buffer[1] < 60; }

  uint16_t xAcceleration() {
    return ((uint16_t)(_buffer[2] << 2) | ((_buffer[5] >> 2) & 0x03));
  }
  uint16_t yAcceleration() {
    return ((uint16_t)(_buffer[3] << 2) | ((_buffer[5] >> 4) & 0x03));
  }
  uint16_t zAcceleration() {
    return ((uint16_t)(_buffer[4] << 2) | ((_buffer[5] >> 6) & 0x03));
  }
  bool zPressed() { return (~_buffer[5] >> 0) & 1; }
  bool cPressed() { return (~_buffer[5] >> 1) & 1; }
};

extern WiiNunchuck wii;

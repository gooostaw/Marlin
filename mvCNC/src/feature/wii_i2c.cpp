/**
 * Modern Vintage CNC Firmware
 */

/**
 * Wii Nunchuck input / jogging
 */

// #include "src/inc/mvCNCConfigPre.h"
#include "src/inc/mvCNCConfig.h"  // for pins

#if ENABLED(WII_NUNCHUCK)

  #include "wii_i2c.h"
  #include "src/module/planner.h"
  #if HAS_CUTTER
    #include "spindle_laser.h"
  #endif
  #include "src/feature/twibus.h"

// #include <Wire.h>

WiiNunchuck wii;
// TWIBus i2c = TWIBus();

  #if ENABLED(EXTENSIBLE_UI)
    #include "src/lcd/extui/ui_api.h"
  #endif

  #if ENABLED(INVERT_WII_X)
    #define WII_X(N) (255 - (N))
  #else
    #define WII_X(N) (N)
  #endif

  #if ENABLED(INVERT_WII_Y)
    #define WII_Y(N) (255 - (N))
  #else
    #define WII_Y(N) (N)
  #endif

  #if ENABLED(INVERT_WII_Z)
    #define WII_Z(N) (255 - (N))
  #else
    #define WII_Z(N) (N)
  #endif

// NUNCHUK DEVICE ID is normally 0x52 (82 dec)

void WiiNunchuck::connect(uint8_t i2c_address /*= 82*/) {
  address    = i2c_address;
  _buffer[0] = 0;
  // Do nothing if disabled (via M458 W0 or WII_NUNCHUCK_ENABLED is not set)
  if (!enabled) return;

  #if (PIN_EXISTS(WII_EN))  // Don't include the _PIN part
  debug(F("connect"), "Pin enable"));
  OUT_WRITE(WII_EN_PIN, HIGH);
  #endif

  #if PINS_EXIST(I2C_SCL, I2C_SDA) && DISABLED(SOFT_I2C_EEPROM)
  Wire.setSDA(pin_t(I2C_SDA_PIN));
  Wire.setSCL(pin_t(I2C_SCL_PIN));
  #endif

  i2c.address(address);

  debug(F("connect: Connecting to"), address);
  // debug(F("connect"), F("Writing start bits"));
  // Tell nunchuck to report status *without* encryption
  i2c.addbyte(0xF0);
  i2c.addbyte(0x55);
  i2c.send();
  // safe_delay(1);
  i2c.addbyte(0xFB);
  i2c.addbyte(0x00);
  i2c.send();
  // safe_delay(1);
  i2c.addbyte(0xFA);
  i2c.send();
  // safe_delay(1);
  i2c.request(6);
  // safe_delay(1);
  if (i2c.capture(_buffer, 6) == 6) {
    connected = true;
    debug(F("connect"), "Connection success");
    // safe_delay(1);
    requestData();
  } else {
    connected = false;
    debug(F("connect"), "Connection failed");
  }
}

bool WiiNunchuck::update() {
  updateReady = false;
  if (!enabled) return updateReady;
  if (!connected) {
    connect();
  } else {
    i2c.request(6);
    // safe_delay(1);
    if (i2c.capture(_buffer, 6) == 6) {
      updateReady = true;
      debug(F("update: response"), _buffer);
      // safe_delay(1);
      requestData();
    } else {
      // Delay error messages to prevent console spam
      static millis_t _next_update_error = millis();
      if (!PENDING(millis(), _next_update_error)) {
        debug(F("update"), "Wii update failed");
      }
      _next_update_error += 500;  // delay in ms
      connected = false;
    }
  }
  return updateReady;
}

void WiiNunchuck::requestData() {
  debug(F("requestData"), "Sending reset");
  i2c.flush();
  i2c.addbyte(0x00);
  i2c.send();
}

char WiiNunchuck::decodeByte(const char b) {
  // return (b ^ 0x17) + 0x17;
  return b;
}

void WiiNunchuck::normalize(float &axis_jog, const uint16_t joy_value, const int16_t (&wii_limits)[4]) {
  debug(F("normalize: Joy value"), joy_value);
  if (WITHIN(joy_value, wii_limits[0], wii_limits[3])) {  // Ignore unexpected results
    // Ignore if within deadzone
    if (joy_value > wii_limits[2]) {
      // returns positive value (0..1)
      axis_jog = ((joy_value - wii_limits[2]) / float(wii_limits[3] - wii_limits[2]));
      // If C button is pressed, double speed
      axis_jog /= (cPressed()) ? (WII_SLOW_DIVISER / 2) : WII_SLOW_DIVISER;
    } else if (joy_value < wii_limits[1]) {
      // returns negative value (-1..0)
      axis_jog = ((joy_value - wii_limits[1]) / float(wii_limits[1] - wii_limits[0]));
      // If C button is pressed, double speed
      axis_jog /= (cPressed()) ? (WII_SLOW_DIVISER / 2) : WII_SLOW_DIVISER;
    }

    // Map normal to jog value via quadratic relationship
    // axis_jog = SIGN(axis_jog) * sq(axis_jog);
    debug(F("normalize: Jog value"), axis_jog);
    if (simulation && axis_jog != 0) {
      SERIAL_ECHOLNPGM("Jog value: ", axis_jog);
    }
  }
};

// Built-in normalizing function (converts arbitrary input range to -1 -> 1 range, adjusting for dead zones)
void WiiNunchuck::calculate(xyz_float_t &joy_value_normalized) {
  static constexpr int16_t wii_x_limits[4] = WII_X_LIMITS;
  static constexpr int16_t wii_y_limits[4] = WII_Y_LIMITS;

  debug(F("calculate: zPressed"), (zPressed()) ? "Yes" : "No");
  if (zPressed()) {  // Move Z axis if Z button pressed
    if (joyX() < wii_x_limits[1] || joyX() > wii_x_limits[2]) {
      normalize(joy_value_normalized.z, WII_Z(joyX()), wii_x_limits);
      // joyX moves the Z axis at 1/4 speed.
      joy_value_normalized.z /= 4;
      if (simulation && joy_value_normalized.z != 0) {
        SERIAL_ECHOLNPGM("xBased Z ", WII_Z(joyX()), " normalized to ", joy_value_normalized.z);
      }
    } else if (joyY() < wii_y_limits[1] || joyY() > wii_y_limits[2]) {
      normalize(joy_value_normalized.z, WII_Z(joyY()), wii_y_limits);
      // joyY moves the Z axis at 1/2 speed.
      joy_value_normalized.z /= 2;
      if (simulation && joy_value_normalized.z != 0) {
        SERIAL_ECHOLNPGM("yBased Z ", WII_Z(joyY()), " normalized to ", joy_value_normalized.z);
      }
    }

  } else {  // Move X/Y axis if not in dead zone
    if (joyX() < wii_x_limits[1] || joyX() > wii_x_limits[2]) {
      normalize(joy_value_normalized.x, WII_X(joyX()), wii_x_limits);
      if (simulation && joy_value_normalized.x != 0) {
        SERIAL_ECHOLNPGM("xValue ", joyX(), " normalized to ", joy_value_normalized.x);
      }
    } else if (joyY() < wii_y_limits[1] || joyY() > wii_y_limits[2]) {
      normalize(joy_value_normalized.y, WII_Y(joyY()), wii_y_limits);
      if (simulation && joy_value_normalized.y != 0) {
        SERIAL_ECHOLNPGM("yValue ", joyY(), " normalized to ", joy_value_normalized.y);
      }
    }
  }
}

void WiiNunchuck::injectJogMoves() {
  // Do nothing if disabled (via M258 W0 or WII_NUNCHUCK_ENABLED is not set)
  if (!enabled)
    return;

  // Recursion barrier
  static bool injecting_now;  // = false;
  if (injecting_now) return;

  if (simulation) {
    // Delay updates reduce console spam
    static millis_t _next_jog_update = millis();
    if (PENDING(millis(), _next_jog_update)) {
      return;
    }
    _next_jog_update += 1000;  // delay in ms
  }

  #if ENABLED(NO_MOTION_BEFORE_HOMING)
  if (axis_should_home())
    return;
  #endif

  const uint8_t _max_queue      = 5;                           // Insert up to this many movements
  const float _target_lag       = 0.25f;                       // Aim for 1/4 second lag
  const float _seg_time         = (_target_lag / _max_queue);  // 0.05 seconds, short segments inserted every 1/20th of a second
  const millis_t timer_limit_ms = millis_t(_seg_time * 500);   // 25 ms minimum delay between insertions

  // The planner can merge/collapse small moves, so the movement queue is unreliable to control the lag
  static millis_t _next_move = millis();
  if (PENDING(millis(), _next_move)) {
    return;
  }
  _next_move += timer_limit_ms;  // delay in ms

  // Only inject a command if the planner has fewer than 5 moves and there are no unparsed commands
  if (planner.movesplanned() > _max_queue || queue.has_commands_queued())
    return;

  if (!update()) {
    return;
  }

  if (simulation) {
    report();
  }

  // Normalized jog values are 0 for no movement and -1 or +1 for as max feedrate (linear relationship)
  // Jog are initialized to zero and handling input can update values but doesn't have to
  // You could use a two-axis wiinunchuck and a one-axis keypad and they might work together
  xyz_float_t joy_value_normalized{0};
  // Use ADC values and defined limits. The active zone is normalized: -1..0 (dead) 0..1
  calculate(joy_value_normalized);

  // Other non-wiinunchuck poll-based jogging could be implemented here
  // with "jogging" encapsulated as a more general class.

  TERN_(EXTENSIBLE_UI, ExtUI::_jogging_update(joy_value_normalized));

  // joy_value_normalized values of [-1 .. 1] maps linearly to [-feedrate .. feedrate]
  xyz_float_t jog_feed_rate{0};
  float quadratic_speed = 0;
  LOOP_LINEAR_AXES(i)
  if (joy_value_normalized[i]) {
    jog_feed_rate[i] = _seg_time * joy_value_normalized[i] * TERN(EXTENSIBLE_UI, manual_feedrate_mm_s, planner.settings.max_feedrate_mm_s)[i];
    quadratic_speed += sq(jog_feed_rate[i]);
  }

  if (!UNEAR_ZERO(quadratic_speed)) {
    if (jobIsOngoing() || TERN0(HAS_CUTTER, cutter.enabled())) {
      // Limit error messages to prevent console spam
      static millis_t _next_in_progress = millis();
      if (PENDING(millis(), _next_in_progress))
        return;
      _next_in_progress += 10000;  // delay in ms
      SERIAL_ERROR_MSG("Cannot jog while job in progress");
      return;
    }
    const float jog_distance = sqrt(quadratic_speed);
    if (simulation) {
      LOOP_LINEAR_AXES(i)
      SERIAL_ECHOLNPGM("Jogging ", i, ": ", jog_feed_rate[i]);
    } else {
      injecting_now = true;
      LOOP_LINEAR_AXES(i)
      debug(F("injectJogMoves: Jogging " + i), jog_feed_rate[i]);
      current_position += jog_feed_rate;
      apply_motion_limits(current_position);
      planner.buffer_line(current_position, jog_distance / _seg_time, active_tool, jog_distance);
      injecting_now = false;
    }
  } else {
    // Correct for memory leaks in cheap 3rd party nunchucks
    static uint8_t _idle_count = 0;
    if (_idle_count > 50) {
      connected = false;
    } else {
      ++_idle_count;
    }
  }
}

  #if ENABLED(WII_NUNCHUCK_DEBUG)

// static
void WiiNunchuck::prefix(FSTR_P const func) {
  SERIAL_ECHOPGM("WiiNunchuck::", func, ": ");
}
void WiiNunchuck::debug(FSTR_P const func, uint32_t number) {
  if (DEBUGGING(INFO)) {
    prefix(func);
    SERIAL_ECHOLN(number);
  }
}
void WiiNunchuck::debug(FSTR_P const func, float number) {
  if (DEBUGGING(INFO)) {
    prefix(func);
    SERIAL_ECHOLN(number);
  }
}
void WiiNunchuck::debug(FSTR_P const func, const char string[]) {
  if (DEBUGGING(INFO)) {
    prefix(func);
    SERIAL_ECHOLN(string);
  }
}

void WiiNunchuck::report() {
  SERIAL_ECHO("Wii Nunchuck");
  SERIAL_ECHO(" X: ");
  SERIAL_ECHO(WII_X(joyX()));
  SERIAL_ECHO(" Y: ");
  SERIAL_ECHO(WII_Y(joyY()));
  // SERIAL_ECHOPGM_P(SP_X_STR, WII_X(joyX()));
  // SERIAL_ECHOPGM_P(SP_Y_STR, WII_Y(joyY()));
  SERIAL_ECHO_TERNARY(cPressed(), " Button C: ", "Yes", "No", "");
  SERIAL_ECHO_TERNARY(zPressed(), " Button Z: ", "Yes", "No", "");
  SERIAL_EOL();
}
  #endif  // WII_NUNCHUCK_DEBUG

#endif  // WII_NUNCHUCK

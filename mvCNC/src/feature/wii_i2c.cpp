/**
 * Modern Vintage CNC Firmware
*/

/**
 * Wii Nunchuck input / jogging
 */

#include "src/inc/mvCNCConfigPre.h"

#if ENABLED(WII_NUNCHUCK)

#include "wii_i2c.h"
#include "src/inc/mvCNCConfig.h"  // for pins
#include "src/module/planner.h"
#if HAS_CUTTER
#include "spindle_laser.h"
#endif
#include <Wire.h>

WiiNunchuck wii;

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

#define NUNCHUK_DEVICE_ID 0x52

void WiiNunchuck::connect() {
#if PIN_EXISTS(WII_EN)
  pinMode(WII_EN_PIN, OUTPUT);
#else
  enabled = false;
#endif
  // Do nothing if disabled (via M458 W0 or WII_NUNCHUCK_ENABLED is not set)
  if (enabled) extDigitalWrite(WII_EN_PIN, HIGH); else return;

  // Delay reconnection attempts to save CPU time and prevent job stuttering
  const millis_t _reconnection_delay = 15000;  // delay in ms

  static millis_t next_run = 0;
  if (PENDING(millis(), next_run)) return;
  next_run = millis() + _reconnection_delay;

#if PINS_EXIST(I2C_SCL, I2C_SDA) && DISABLED(SOFT_I2C_EEPROM)
  Wire.setSDA(pin_t(I2C_SDA_PIN));
  Wire.setSCL(pin_t(I2C_SCL_PIN));
#endif

  Wire.begin();

  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.endTransmission();
}

bool WiiNunchuck::update() {
  Wire.requestFrom(NUNCHUK_DEVICE_ID, NUNCHUK_BUFFER_SIZE);
  int byte_counter = 0;

  while (Wire.available() && byte_counter < NUNCHUK_BUFFER_SIZE)
    _buffer[byte_counter++] = decodeByte(Wire.read());

  requestData();
  return byte_counter == NUNCHUK_BUFFER_SIZE;
}

void WiiNunchuck::requestData() {
  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.write(0x00);
  Wire.endTransmission();
}

char WiiNunchuck::decodeByte(const char b) {
  return (b ^ 0x17) + 0x17;
}

void WiiNunchuck::normalize(float &axis_jog, const int16_t joy_value, const int16_t(&wii_limits)[4], const bool is_z_axis/* = false */) {
  if (WITHIN(joy_value, wii_limits[0], wii_limits[3])) {
    // Within limits? Ignore if within deadzone
    if (joy_value > wii_limits[2])
      axis_jog = (joy_value - wii_limits[2]) / float(wii_limits[3] - wii_limits[2]);  // positive value
    else if (joy_value < wii_limits[1])
      axis_jog = (joy_value - wii_limits[1]) / float(wii_limits[1] - wii_limits[0]);  // negative value

      // If C button is not pressed, reduce the speed of the movement
    if (axis_jog != 0.0f && !cPressed()) { axis_jog = axis_jog / WII_SLOW_DIVISER; }

    // Map normal to jog value via quadratic relationship
    axis_jog = SIGN(axis_jog) * sq(axis_jog);
  }
};


// Built-in normalizing function (converts arbitrary input range to -1 -> 1 range, adjusting for dead zones)
void WiiNunchuck::calculate(xyz_float_t &joy_value_normalized) {

  static constexpr int16_t wii_x_limits[4] = WII_X_LIMITS;
  static constexpr int16_t wii_y_limits[4] = WII_Y_LIMITS;

  if (zPressed()) {  // Move Z axis if Z button pressed

    if (joyX() < wii_x_limits[1] || joyX() > wii_x_limits[2]) {
      // joyX moves the Z axis at half adjusted speed.
      float _half_joy_speed = joyX() + (128 - joyX()) / 2;
      normalize(joy_value_normalized.z, WII_Z(_half_joy_speed), wii_x_limits, true);
    } else {
      // joyY moves the Z axis at normal adjusted speed.
      normalize(joy_value_normalized.z, WII_Z(joyY()), wii_y_limits, true);
    }

  } else {  // Move X/Y axis
    normalize(joy_value_normalized.x, WII_X(joyX()), wii_x_limits);
    normalize(joy_value_normalized.y, WII_Y(joyY()), wii_y_limits);
  }
}

void WiiNunchuck::injectJogMoves() {
  // Do nothing if disabled (via M458 W0 or WII_NUNCHUCK_ENABLED is not set)
  if (!enabled) return;

  // Recursion barrier
  static bool injecting_now;  // = false;
  if (injecting_now || jobIsOngoing() || TERN0(HAS_CUTTER, cutter.enabled())) {
    SERIAL_ERROR_MSG("Cannot jog while job in progress");
    return;
  }

#if ENABLED(NO_MOTION_BEFORE_HOMING)
  if (axis_should_home()) return;
#endif

  // Attempt a connection if not currently connected
  if (!update()) {
    connect();
    return;
  }

  static constexpr int QUEUE_DEPTH = 5;      // Insert up to this many movements
  static constexpr float target_lag = 0.25f,  // Aim for 1/4 second lag
    seg_time = target_lag / QUEUE_DEPTH;      // 0.05 seconds, short segments inserted every 1/20th of a second
  static constexpr millis_t timer_limit_ms = millis_t(seg_time * 500);  // 25 ms minimum delay between insertions

  // The planner can merge/collapse small moves, so the movement queue is unreliable to control the lag
  static millis_t next_run = 0;
  if (PENDING(millis(), next_run)) return;
  next_run = millis() + timer_limit_ms;

  // Only inject a command if the planner has fewer than 5 moves and there are no unparsed commands
  if (planner.movesplanned() >= QUEUE_DEPTH || queue.has_commands_queued()) return;

  // Normalized jog values are 0 for no movement and -1 or +1 for as max feedrate (nonlinear relationship)
  // Jog are initialized to zero and handling input can update values but doesn't have to
  // You could use a two-axis wiinunchuck and a one-axis keypad and they might work together
  xyz_float_t joy_value_normalized{0};

  // Use ADC values and defined limits. The active zone is normalized: -1..0 (dead) 0..1
  calculate(joy_value_normalized);
#if ENABLED(WII_NUNCHUCK_DEBUG)
  report();
#endif

  // Other non-wiinunchuck poll-based jogging could be implemented here
  // with "jogging" encapsulated as a more general class.

  TERN_(EXTENSIBLE_UI, ExtUI::_jogging_update(joy_value_normalized));

  // joy_value_normalized values of [-1 .. 1] maps linearly to [-feedrate .. feedrate]
  xyz_float_t jog_feed_rate{0};
  float quadratic_speed = 0;
  LOOP_LINEAR_AXES(i) if (joy_value_normalized[i]) {
    jog_feed_rate[i] =
      seg_time * joy_value_normalized[i] * TERN(EXTENSIBLE_UI, manual_feedrate_mm_s, planner.settings.max_feedrate_mm_s)[i];
    quadratic_speed += sq(jog_feed_rate[i]);
  }

  if (!UNEAR_ZERO(quadratic_speed)) {
    current_position += jog_feed_rate;
    apply_motion_limits(current_position);
    const float jog_distance = sqrt(quadratic_speed);
    injecting_now = true;
    planner.buffer_line(current_position, jog_distance / seg_time, active_tool, jog_distance);
    injecting_now = false;
  }
}

#if ENABLED(WII_NUNCHUCK_DEBUG)
void WiiNunchuck::report() {
  if (mvcnc_debug_flags == MVCNC_DEBUG_COMMUNICATION) {  // Show debug reports when "M111 S5" is set
    const millis_t _report_delay = 1000;                 // delay in ms

    static millis_t next_run = 0;
    if (PENDING(millis(), next_run)) return;
    next_run = millis() + _report_delay;

    const char cPrint = cPressed() ? 'C' : 'c';
    const char zPrint = zPressed() ? 'Z' : 'z';

    SERIAL_ECHOPGM("Wii Nunchuck");
  #if HAS_WII_EN
    SERIAL_ECHO_TERNARY(READ(WII_EN_PIN), " EN=", "HIGH (dis", "LOW (en", "abled)");
  #endif
    SERIAL_ECHOPGM_P(SP_X_STR, WII_X(joyX()));
    SERIAL_ECHOPGM_P(SP_Y_STR, WII_Y(joyY()));
    SERIAL_ECHOLNPGM_P("Buttons: ", cPrint + zPrint);
  }
}
#endif // WII_NUNCHUCK_DEBUG

#endif  // WII_NUNCHUCK

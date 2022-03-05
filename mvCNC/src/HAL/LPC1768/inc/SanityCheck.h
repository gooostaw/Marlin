/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#if PIO_PLATFORM_VERSION < 1001
  #error "nxplpc-arduino-lpc176x package is out of date, Please update the PlatformIO platforms, frameworks and libraries. You may need to remove the platform and let it reinstall automatically."
#endif
#if PIO_FRAMEWORK_VERSION < 2006
  #error "framework-arduino-lpc176x package is out of date, Please update the PlatformIO platforms, frameworks and libraries."
#endif

/**
 * Detect an old pins file by checking for old ADC pins values.
 */
#define _OLD_TEMP_PIN(P) PIN_EXISTS(P) && _CAT(P,_PIN) <= 7 && !WITHIN(_CAT(P,_PIN), TERN(LPC1768_IS_SKRV1_3, 0, 2), 3)  // Include P0_00 and P0_01 for SKR V1.3 board
#if _OLD_TEMP_PIN(TEMP_BED)
  #error "TEMP_BED_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_0)
  #error "TEMP_0_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_1)
  #error "TEMP_1_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_2)
  #error "TEMP_2_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_3)
  #error "TEMP_3_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_4)
  #error "TEMP_4_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_5)
  #error "TEMP_5_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_6)
  #error "TEMP_6_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#elif _OLD_TEMP_PIN(TEMP_7)
  #error "TEMP_7_PIN must be defined using the Pn_nn or Pn_nn_An format. (See the included pins files)."
#endif
#undef _OLD_TEMP_PIN

/**
 * Because PWM hardware channels all share the same frequency, along with the
 * fallback software channels, FAST_PWM_FAN is incompatible with Servos.
 */
static_assert(!(NUM_SERVOS && ENABLED(FAST_PWM_FAN)), "BLTOUCH and Servos are incompatible with FAST_PWM_FAN on LPC176x boards.");

#if SPINDLE_LASER_FREQUENCY
  static_assert(!NUM_SERVOS, "BLTOUCH and Servos are incompatible with SPINDLE_LASER_FREQUENCY on LPC176x boards.");
#endif

/**
 * Test LPC176x-specific configuration values for errors at compile-time.
 */

//#if ENABLED(SPINDLE_LASER_USE_PWM) && !(SPINDLE_LASER_PWM_PIN == 4 || SPINDLE_LASER_PWM_PIN == 6 || SPINDLE_LASER_PWM_PIN == 11)
//  #error "SPINDLE_LASER_PWM_PIN must use SERVO0, SERVO1 or SERVO3 connector"
//#endif

#if MB(RAMPS_14_RE_ARM_EFB, RAMPS_14_RE_ARM_EEB, RAMPS_14_RE_ARM_EFF, RAMPS_14_RE_ARM_EEF, RAMPS_14_RE_ARM_SF)
  #if IS_RRD_FG_SC && HAS_DRIVER(TMC2130) && DISABLED(TMC_USE_SW_SPI)
    #error "Re-ARM with REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER and TMC2130 requires TMC_USE_SW_SPI."
  #endif
#endif

static_assert(DISABLED(BAUD_RATE_GCODE), "BAUD_RATE_GCODE is not yet supported on LPC176x.");

/**
 * Flag any serial port conflicts
 *
 *   Port  |  TX   |  RX   |
 *    ---  |  ---  |  ---  |
 * Serial  | P0_02 | P0_03 |
 * Serial1 | P0_15 | P0_16 |
 * Serial2 | P0_10 | P0_11 |
 * Serial3 | P0_00 | P0_01 |
 */
#define ANY_TX(N,V...) DO(IS_TX##N,||,V)
#define ANY_RX(N,V...) DO(IS_RX##N,||,V)

#if USING_HW_SERIAL0
  #define IS_TX0(P) (P == P0_02)
  #define IS_RX0(P) (P == P0_03)
  #if IS_TX0(TMC_SW_MISO) || IS_RX0(TMC_SW_MOSI)
    #error "Serial port pins (0) conflict with Trinamic SPI pins!"
  #elif HAS_PRUSA_MMU1 && (IS_TX0(E_MUX1_PIN) || IS_RX0(E_MUX0_PIN))
    #error "Serial port pins (0) conflict with Multi-Material-Unit multiplexer pins!"
  #elif (AXIS_HAS_SPI(X) && IS_TX0(X_CS_PIN)) || (AXIS_HAS_SPI(Y) && IS_RX0(Y_CS_PIN))
    #error "Serial port pins (0) conflict with X/Y axis SPI pins!"
  #endif
  #undef IS_TX0
  #undef IS_RX0
#endif

#if USING_HW_SERIAL1
  #define IS_TX1(P) (P == P0_15)
  #define IS_RX1(P) (P == P0_16)
  #define _IS_TX1_1 IS_TX1
  #define _IS_RX1_1 IS_RX1
  #if IS_TX1(TMC_SW_SCK)
    #error "Serial port pins (1) conflict with other pins!"
  #elif HAS_ROTARY_ENCODER
    #if IS_TX1(BTN_EN2) || IS_RX1(BTN_EN1)
      #error "Serial port pins (1) conflict with Encoder Buttons!"
    #elif ANY_TX(1, SD_SCK_PIN, LCD_PINS_D4, DOGLCD_SCK, LCD_RESET_PIN, LCD_PINS_RS, SHIFT_CLK_PIN) \
       || ANY_RX(1, LCD_SDSS, LCD_PINS_RS, SD_MISO_PIN, DOGLCD_A0, SD_SS_PIN, LCD_SDSS, DOGLCD_CS, LCD_RESET_PIN, LCD_BACKLIGHT_PIN)
      #error "Serial port pins (1) conflict with LCD pins!"
    #endif
  #endif
  #undef IS_TX1
  #undef IS_RX1
  #undef _IS_TX1_1
  #undef _IS_RX1_1
#endif

#if USING_HW_SERIAL2
  #define IS_TX2(P) (P == P0_10)
  #define IS_RX2(P) (P == P0_11)
  #define _IS_TX2_1 IS_TX2
  #define _IS_RX2_1 IS_RX2
  #if IS_TX2(X2_ENABLE_PIN) || ANY_RX(2, X2_DIR_PIN, X2_STEP_PIN) || (AXIS_HAS_SPI(X2) && IS_TX2(X2_CS_PIN))
    #error "Serial port pins (2) conflict with X2 pins!"
  #elif IS_TX2(Y2_ENABLE_PIN) || ANY_RX(2, Y2_DIR_PIN, Y2_STEP_PIN) || (AXIS_HAS_SPI(Y2) && IS_TX2(Y2_CS_PIN))
    #error "Serial port pins (2) conflict with Y2 pins!"
  #elif IS_TX2(Z2_ENABLE_PIN) || ANY_RX(2, Z2_DIR_PIN, Z2_STEP_PIN) || (AXIS_HAS_SPI(Z2) && IS_TX2(Z2_CS_PIN))
    #error "Serial port pins (2) conflict with Z2 pins!"
  #elif IS_TX2(Z3_ENABLE_PIN) || ANY_RX(2, Z3_DIR_PIN, Z3_STEP_PIN) || (AXIS_HAS_SPI(Z3) && IS_TX2(Z3_CS_PIN))
    #error "Serial port pins (2) conflict with Z3 pins!"
  #elif IS_TX2(Z4_ENABLE_PIN) || ANY_RX(2, Z4_DIR_PIN, Z4_STEP_PIN) || (AXIS_HAS_SPI(Z4) && IS_TX2(Z4_CS_PIN))
    #error "Serial port pins (2) conflict with Z4 pins!"
  #elif ANY_RX(2, X_DIR_PIN, Y_DIR_PIN)
    #error "Serial port pins (2) conflict with other pins!"
  #elif Y_HOME_TO_MIN && IS_TX2(Y_STOP_PIN)
    #error "Serial port pins (2) conflict with Y endstop pin!"
  #elif USES_Z_MIN_PROBE_PIN && IS_TX2(Z_MIN_PROBE_PIN)
    #error "Serial port pins (2) conflict with probe pin!"
  #elif ANY_TX(2, X_ENABLE_PIN, Y_ENABLE_PIN) || ANY_RX(2, X_DIR_PIN, Y_DIR_PIN)
    #error "Serial port pins (2) conflict with X/Y stepper pins!"
  #elif HAS_MULTI_EXTRUDER && (IS_TX2(E1_ENABLE_PIN) || (AXIS_HAS_SPI(E1) && IS_TX2(E1_CS_PIN)))
    #error "Serial port pins (2) conflict with E1 stepper pins!"
  #elif EXTRUDERS && ANY_RX(2, E0_DIR_PIN, E0_STEP_PIN)
    #error "Serial port pins (2) conflict with E stepper pins!"
  #endif
  #undef IS_TX2
  #undef IS_RX2
  #undef _IS_TX2_1
  #undef _IS_RX2_1
#endif

#if USING_HW_SERIAL3
  #define PIN_IS_TX3(P) (PIN_EXISTS(P) && P##_PIN == P0_00)
  #define PIN_IS_RX3(P) (P##_PIN == P0_01)
  #if PIN_IS_TX3(X_MIN) || PIN_IS_RX3(X_MAX)
    #error "Serial port pins (3) conflict with X endstop pins!"
  #elif PIN_IS_TX3(Y_SERIAL_TX) || PIN_IS_TX3(Y_SERIAL_RX) || PIN_IS_RX3(X_SERIAL_TX) || PIN_IS_RX3(X_SERIAL_RX)
    #error "Serial port pins (3) conflict with X/Y axis UART pins!"
  #elif PIN_IS_TX3(X2_DIR) || PIN_IS_RX3(X2_STEP)
    #error "Serial port pins (3) conflict with X2 pins!"
  #elif PIN_IS_TX3(Y2_DIR) || PIN_IS_RX3(Y2_STEP)
    #error "Serial port pins (3) conflict with Y2 pins!"
  #elif PIN_IS_TX3(Z2_DIR) || PIN_IS_RX3(Z2_STEP)
    #error "Serial port pins (3) conflict with Z2 pins!"
  #elif PIN_IS_TX3(Z3_DIR) || PIN_IS_RX3(Z3_STEP)
    #error "Serial port pins (3) conflict with Z3 pins!"
  #elif PIN_IS_TX3(Z4_DIR) || PIN_IS_RX3(Z4_STEP)
    #error "Serial port pins (3) conflict with Z4 pins!"
  #elif HAS_MULTI_EXTRUDER && (PIN_IS_TX3(E1_DIR) || PIN_IS_RX3(E1_STEP))
    #error "Serial port pins (3) conflict with E1 pins!"
  #endif
  #undef PIN_IS_TX3
  #undef PIN_IS_RX3
#endif

#undef ANY_TX
#undef ANY_RX

//
// Flag any i2c pin conflicts
//
#if ANY(WII_NUNCHUCK, HAS_MOTOR_CURRENT_I2C, HAS_MOTOR_CURRENT_DAC, EXPERIMENTAL_I2CBUS, I2C_POSITION_ENCODERS, PCA9632, I2C_EEPROM) && !defined(USEDI2CDEV_M)
  // Automatically finds and sets available i2c pins for <Arduino>/Wire.cpp
  #ifndef USEDI2CDEV_M
    // Try Pins P0_27 [SD Detect] (SDA) and P0_28 [??] (SCL)
    #if ENABLED(SDSUPPORT)
      #define I2CCONFLICT = "i2c SDA0 pin conflicts with SD_DETECT_PIN!"
    #else
      static_assert("Autoassigned i2c to Pins P0_27 [SD Detect] (SDA) and P0_28 [??] (SCL)");
      #define USEDI2CDEV_M 0  // Sets i2c pins for <Arduino>/Wire.cpp
    #endif
    // Try Pins P0_00 [E1_DIR] (SDA) and P0_01 [E1_STEP] (SCL)
    #if defined(I2CCONFLICT)
      #undef I2CCONFLICT
      #define PIN_IS_SDA1(P) (PIN_EXISTS(P) && P##_PIN == P0_00)
      #define PIN_IS_SCL1(P) (P##_PIN == P0_01)
      #if HAS_MULTI_EXTRUDER && (PIN_IS_SDA1(E1_DIR) || PIN_IS_SCL1(E1_STEP))
        #define I2CCONFLICT = "I2C pins overlap with E1 pins!"
      #else
        static_assert("Autoassigned i2c to Pins P0_00 [E1_DIR] (SDA) and P0_01 [E1_STEP] (SCL)");
        #define USEDI2CDEV_M 1  // Sets i2c pins for <Arduino>/Wire.cpp
      #endif
      #undef PIN_IS_SDA1
      #undef PIN_IS_SCL1
    #endif
    #if defined(I2CCONFLICT)  // Try Pins P0_10 and P0_11
      #undef I2CCONFLICT
      #define PIN_IS_SDA2(P) (P##_PIN == P0_10)
      #define PIN_IS_SCL2(P) (P##_PIN == P0_11)
      #if PIN_IS_SDA2(Y_STOP)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Y endstop pin!"
      #elif USES_Z_MIN_PROBE_PIN && PIN_IS_SDA2(Z_MIN_PROBE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Z probe pin!"
      #elif PIN_IS_SDA2(X_ENABLE) || PIN_IS_SDA2(Y_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with X/Y ENABLE pin!"
      #elif AXIS_HAS_SPI(X) && PIN_IS_SDA2(X_CS)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with X CS pin!"
      #elif PIN_IS_SDA2(X2_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with X2 enable pin! Disable i2c peripherals."
      #elif PIN_IS_SDA2(Y2_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Y2 enable pin! Disable i2c peripherals."
      #elif PIN_IS_SDA2(Z2_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Z2 enable pin! Disable i2c peripherals."
      #elif PIN_IS_SDA2(Z3_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Z3 enable pin! Disable i2c peripherals."
      #elif PIN_IS_SDA2(Z4_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with Z4 enable pin! Disable i2c peripherals."
      #elif HAS_MULTI_EXTRUDER && PIN_IS_SDA2(E1_ENABLE)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with E1 enable pin! Disable i2c peripherals."
      #elif HAS_MULTI_EXTRUDER && PIN_IS_SDA2(E1_DIR)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with E1 direction pin! Disable i2c peripherals."
      #elif HAS_MULTI_EXTRUDER && AXIS_HAS_SPI(E1) && PIN_IS_SDA2(E1_CS)
        #define I2CCONFLICT = "i2c SDA2 pin conflicts with E1 CS pin! Disable i2c peripherals."
      #elif EXTRUDERS && (PIN_IS_SDA2(E0_STEP) || PIN_IS_SDA2(E0_DIR))
        #define I2CCONFLICT = "i2c SCL2 pin conflicts with E0 STEP/DIR pin! Disable i2c peripherals."
      #elif PIN_IS_SDA2(X_DIR) || PIN_IS_SDA2(Y_DIR)
        #define I2CCONFLICT = "One or more i2c pins pin conflicts with X/Y DIR pin! Disable i2c peripherals."
      #else
        #undef I2CCONFLICT
        static_assert("Autoassigned i2c to Pins P0_10 [E1_EN] (SDA) and P0_11 [E0_DIR] (SCL)");
        #define USEDI2CDEV_M 2  // Sets i2c pins for <Arduino>/Wire.cpp
      #endif
      #undef PIN_IS_SDA2
      #undef PIN_IS_SCL2
    #endif
    #if defined(I2CCONFLICT)  // All i2c pins are taken, abort.
      #error I2CCONFLICT
    #endif
  #endif
#endif

#if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
  #error "SERIAL_STATS_MAX_RX_QUEUED is not supported on LPC176x."
#elif ENABLED(SERIAL_STATS_DROPPED_RX)
  #error "SERIAL_STATS_DROPPED_RX is not supported on LPX176x."
#endif

/**
 * Modern Vintage CNC Firmware
*/

#include "src/inc/mvCNCConfig.h"

#if ANY(WII_NUNCHUCK, JOYSTICK)

#include "src/gcode/gcode.h"

#if ENABLED(WII_NUNCHUCK)
#include "src/feature/wii_i2c.h"
#endif

#if ENABLED(JOYSTICK)
#include "src/feature/joystick.h"
#endif

/**
 * M258: Enable/Disable an I2C accessory device (game joystick, wii controller, etc)
 *
 *  M258
 *        W[0/1/2] Disable/Enable/Simulate attached Wii Nunchuck
 *          - Simulation (2) mode will only report values to serial, no actual jogging will occur
 *        J[0/1] Disable/Enable attached joystick
 */
void GcodeSuite::M258() {
#if ENABLED(WII_NUNCHUCK)
  // Wii controller enable/disable
  if (parser.seen('W')) {
    if (parser.value_byte() == 2) {  // Simulation mode
      wii.enabled    = true;
      wii.simulation = true;
    #if (PIN_EXISTS(WII_EN))  // Don't include the _PIN part
      OUT_WRITE(WII_EN_PIN, HIGH);
    #endif
    } else if (parser.value_byte() == 1) {  // Enable
      wii.enabled = true;
      wii.simulation = false;
    #if (PIN_EXISTS(WII_EN))  // Don't include the _PIN part
      OUT_WRITE(WII_EN_PIN, HIGH);
    #endif
    } else {  // Disable
      wii.enabled = false;
    #if (PIN_EXISTS(WII_EN))
      OUT_WRITE(WII_EN_PIN, LOW);
    #endif
    }
    SERIAL_ECHO_TERNARY(wii.enabled, "Wii Nunchuck ", "enabled", "disabled", "");
    if (wii.enabled)
      SERIAL_ECHO_TERNARY(wii.simulation, ", Simulation mode: ", "enabled", "disabled", "");
    SERIAL_EOL();
  }
#endif

#if ENABLED(JOYSTICK)
  // Wii controller enable/disable
  else if (parser.seen('J')) {
    if (parser.value_bool()) {
      joystick.enabled = true;
    #if (PIN_EXISTS(JOY_EN))  // Don't include the _PIN part
      OUT_WRITE(JOY_EN_PIN, HIGH);
    #endif
    } else {
      joystick.enabled = false;
    #if (PIN_EXISTS(JOY_EN))  // Don't include the _PIN part
      OUT_WRITE(JOY_EN_PIN, LOW);
    #endif
    }
    SERIAL_ECHO_TERNARY(joystick.enabled, "Joystick ", "enabled", "disabled", "");
    SERIAL_EOL();
  }
#endif

  // TODO: Duplicate the below lines to add a device
  //#if ENABLED(xDevice)
  //// xDevice enable/disable
  // else if (parser.seen('X')) {
  //   if (parser.value_bool()) {
  //     xDevice.enabled = true;
  // #if (PIN_EXISTS(xDevice_EN)) // Don't include the _PIN part
  //   OUT_WRITE(xDevice_EN_PIN, HIGH);
  // #endif
  //   } else {
  //     xDevice.enabled = false;
  // #if (PIN_EXISTS(xDevice_EN)) // Don't include the _PIN part
  //   OUT_WRITE(xDevice_EN_PIN, LOW);
  // #endif
  //   }
  //   SERIAL_ECHO_TERNARY(xDevice.enabled, "xDevice ", "enabled", "disabled", "");
  //   SERIAL_EOL();
  // }
  //#endif

  else {
    SERIAL_ERROR_MSG("Device prefix not found");
  }
}

#endif

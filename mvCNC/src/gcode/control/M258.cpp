/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

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
 *        W[0/1] Disable/Enable attached Wii Nunchuck
 *        J[0/1] Disable/Enable attached joystick
 */
void GcodeSuite::M258() {
#if ENABLED(WII_NUNCHUCK)
  // Wii controller enable/disable
  if (parser.seen('W')) {
    if (parser.value_bool()) {
      wii.enabled = true;
      extDigitalWrite(WII_EN_PIN, HIGH);
    } else {
      wii.enabled = false;
      extDigitalWrite(WII_EN_PIN, LOW);
    }
    SERIAL_ECHO_TERNARY(wii.enabled, "Wii Nunchuck ", "enabled", "disabled", "");
  }
#endif

#if ENABLED(JOYSTICK)
  // Wii controller enable/disable
  else if (parser.seen('J')) {
    if (parser.value_bool()) {
      joystick.enabled = true;
      extDigitalWrite(JOY_EN_PIN, HIGH);
    } else {
      joystick.enabled = false;
      extDigitalWrite(JOY_EN_PIN, LOW);
    }
    SERIAL_ECHO_TERNARY(joystick.enabled, "Joystick ", "enabled", "disabled", "");
  }
#endif

  //TODO: Duplicate the below lines to add a device
  //#if ENABLED(xDevice)
  //// xDevice enable/disable
  // else if (parser.seen('W')) {
  //   if (parser.value_bool()) {
  //     wii.enabled = true;
  //     extDigitalWrite(xDevice_EN_PIN, HIGH);
  //   } else {
  //     wii.enabled = false;
  //     extDigitalWrite(xDevice_EN_PIN, LOW);
  //   }
  //   SERIAL_ECHO_TERNARY(xDevice.enabled, "xDevice ", "enabled", "disabled", "");
  // }
  //#endif

  else {
    SERIAL_ERROR_MSG("Device code not recognized. Is it configured?");
  }

}

#endif

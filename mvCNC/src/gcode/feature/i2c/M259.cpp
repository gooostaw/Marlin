/**
 * Modern Vintage CNC Firmware
 */

#include "src/inc/mvCNCConfig.h"
#include "src/gcode/gcode.h"
#include "Wire.h"

/**
 * M259: Scan for available I2C slave devices
 *
 * Usage: M259 (no arguments)
 */
void GcodeSuite::M259() {
  Wire.begin();
  int nDevices = 0;
  delay(200);

  SERIAL_ECHOLN("Scanning for i2c devices..");
  for (uint8_t address = 9; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Wire.endTransmission to see if
    // a device returns an ACK to the address.
    Wire.beginTransmission(I2C_ADDRESS(address));
    delay(100);
    if (Wire.endTransmission() == 0) {
      SERIAL_EOL();
      SERIAL_ECHOLNPGM("I2C device found at address ", HEXCHR(address), " (", address, ")", "");
      ++nDevices;
    } else {
      SERIAL_ECHOPGM(".", address);
    }
  }
  if (!nDevices) {
    SERIAL_ECHOLN("No I2C devices found");
  }
}

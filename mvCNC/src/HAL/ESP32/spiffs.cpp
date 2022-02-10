/**
 * Modern Vintage CNC Firmware
*/
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/mvCNCConfigPre.h"

#if BOTH(WIFISUPPORT, WEBSUPPORT)

#include "../../core/serial.h"

#include <FS.h>
#include <SPIFFS.h>

bool spiffs_initialized;

void spiffs_init() {
  if (SPIFFS.begin(true))  // formatOnFail = true
    spiffs_initialized = true;
  else
    SERIAL_ERROR_MSG("SPIFFS mount failed");
}

#endif // WIFISUPPORT && WEBSUPPORT
#endif // ARDUINO_ARCH_ESP32

/**
 * Modern Vintage CNC Firmware
*/

#ifdef ARDUINO_ARCH_ESP32

#include "FlushableHardwareSerial.h"

Serial1Class<FlushableHardwareSerial> flushableSerial(false, 0);

#endif

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <HardwareSerial.h>

#include "../shared/Marduino.h"
#include "../../core/serial_hook.h"

class FlushableHardwareSerial : public HardwareSerial {
public:
  FlushableHardwareSerial(int uart_nr) : HardwareSerial(uart_nr) {}
};

extern Serial1Class<FlushableHardwareSerial> flushableSerial;

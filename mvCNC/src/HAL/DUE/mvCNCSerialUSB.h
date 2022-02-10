/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * mvCNCSerialUSB_Due.h - Hardware Serial over USB (CDC) library for Arduino DUE
 * Copyright (c) 2017 Eduardo José Tagle. All right reserved
 */

#include "../../inc/mvCNCConfig.h"
#include "../../core/serial_hook.h"

#include <WString.h>

struct mvCNCSerialUSB {
  void begin(const long);
  void end();
  int peek();
  int read();
  void flush();
  int available();
  size_t write(const uint8_t c);

  #if ENABLED(SERIAL_STATS_DROPPED_RX)
    FORCE_INLINE uint32_t dropped() { return 0; }
  #endif

  #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
    FORCE_INLINE int rxMaxEnqueued() { return 0; }
  #endif
};

#if SERIAL_PORT == -1
  typedef Serial1Class<mvCNCSerialUSB> MSerialT1;
  extern MSerialT1 customizedSerial1;
#endif

#if SERIAL_PORT_2 == -1
  typedef Serial1Class<mvCNCSerialUSB> MSerialT2;
  extern MSerialT2 customizedSerial2;
#endif

#if SERIAL_PORT_3 == -1
  typedef Serial1Class<mvCNCSerialUSB> MSerialT3;
  extern MSerialT3 customizedSerial3;
#endif

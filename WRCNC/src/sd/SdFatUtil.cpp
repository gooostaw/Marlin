/**
 * Webber Ranch CNC Firmware
*/

/**
 * sd/SdFatUtil.cpp
 *
 * Arduino SdFat Library
 * Copyright (c) 2008 by William Greiman
 *
 * This file is part of the Arduino Sd2Card Library
 */

#include "../inc/WRCNCConfig.h"

#if ENABLED(SDSUPPORT)

#include "SdFatUtil.h"
#include <string.h>

/**
 * Amount of free RAM
 * \return The number of free bytes.
 */
#ifdef __arm__

  extern "C" char* sbrk(int incr);
  int SdFatUtil::FreeRam() {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
  }

#elif defined(__AVR__)

  extern char* __brkval;
  extern char __bss_end;
  int SdFatUtil::FreeRam() {
    char top;
    return __brkval ? &top - __brkval : &top - &__bss_end;
  }

#endif

#endif // SDSUPPORT

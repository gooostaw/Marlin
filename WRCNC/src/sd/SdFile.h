/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * sd/SdFile.h
 *
 * Arduino SdFat Library
 * Copyright (c) 2009 by William Greiman
 *
 * This file is part of the Arduino Sd2Card Library
 */

#include "SdBaseFile.h"

#include <stdint.h>

/**
 * \class SdFile
 * \brief SdBaseFile with Print.
 */
class SdFile : public SdBaseFile {
 public:
  SdFile() {}
  SdFile(const char *name, uint8_t oflag);
  #if ARDUINO >= 100
    size_t write(uint8_t b);
  #else
    void write(uint8_t b);
  #endif

  int16_t write(const void *buf, uint16_t nbyte);
  void write(const char *str);
  void write_P(PGM_P str);
  void writeln_P(PGM_P str);
};

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * sd/SdFatUtil.h
 *
 * Arduino SdFat Library
 * Copyright (c) 2008 by William Greiman
 *
 * This file is part of the Arduino Sd2Card Library
 */

/**
 * \file
 * \brief Useful utility functions.
 */

namespace SdFatUtil {
  int FreeRam();
}

using namespace SdFatUtil;  // NOLINT

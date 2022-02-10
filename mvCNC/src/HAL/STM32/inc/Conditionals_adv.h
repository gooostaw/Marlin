/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#if BOTH(SDSUPPORT, USBD_USE_CDC_MSC) && DISABLED(NO_SD_HOST_DRIVE)
  #define HAS_SD_HOST_DRIVE 1
#endif

// Fix F_CPU not being a compile-time constant in STSTM32 framework
#ifdef BOARD_F_CPU
  #undef F_CPU
  #define F_CPU BOARD_F_CPU
#endif

// The Sensitive Pins array is not optimizable
#define RUNTIME_ONLY_ANALOG_TO_DIGITAL

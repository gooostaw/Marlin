/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#if NOT_TARGET(STM32F0xx)
  #error "Oops! Select an STM32F0 board in your IDE."
#endif

#define BOARD_INFO_NAME "Malyan M200 V2"

#include "../stm32f1/pins_MALYAN_M200.h"

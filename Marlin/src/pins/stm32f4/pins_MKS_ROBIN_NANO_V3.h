/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define ALLOW_STM32DUINO
#include "env_validate.h"

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS Robin Nano V3 supports up to 2 hotends / E-steppers."
#elif HAS_FSMC_TFT
  #error "MKS Robin Nano V3 doesn't support FSMC-based TFT displays."
#endif

#define BOARD_INFO_NAME "MKS Robin Nano V3"

#define USES_DIAG_JUMPERS

#ifndef X_CS_PIN
  #define X_CS_PIN                          PD5
#endif
#ifndef Y_CS_PIN
  #define Y_CS_PIN                          PD7
#endif
#ifndef Z_CS_PIN
  #define Z_CS_PIN                          PD4
#endif
#ifndef E0_CS_PIN
  #define E0_CS_PIN                         PD9
#endif
#ifndef E1_CS_PIN
  #define E1_CS_PIN                         PD8
#endif

//
// Software SPI pins for TMC2130 stepper drivers
// This board only supports SW SPI for stepper drivers
//
#if HAS_TMC_SPI
  #define TMC_USE_SW_SPI
#endif
#if ENABLED(TMC_USE_SW_SPI)
  #if !defined(TMC_SW_MOSI) || TMC_SW_MOSI == -1
    #define TMC_SW_MOSI                     PD14
  #endif
  #if !defined(TMC_SW_MISO) || TMC_SW_MISO == -1
    #define TMC_SW_MISO                     PD1
  #endif
  #if !defined(TMC_SW_SCK) || TMC_SW_SCK == -1
    #define TMC_SW_SCK                      PD0
  #endif
#endif

#include "pins_MKS_ROBIN_NANO_V3_common.h"

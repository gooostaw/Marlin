/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#define BOARD_INFO_NAME "FYSETC S6 2.0"

//
// EEPROM Emulation
//
#if NO_EEPROM_SELECTED
  #undef NO_EEPROM_SELECTED
  //#define FLASH_EEPROM_EMULATION
  #define I2C_EEPROM
#endif

//
// Steppers
//
#define X_ENABLE_PIN                        PE9

#if HAS_TMC_UART
  #define X_SERIAL_TX_PIN                   PE8
  #define X_SERIAL_RX_PIN                   PE8
  #define Y_SERIAL_TX_PIN                   PC4
  #define Y_SERIAL_RX_PIN                   PC4
  #define Z_SERIAL_TX_PIN                   PD12
  #define Z_SERIAL_RX_PIN                   PD12
  #define E0_SERIAL_TX_PIN                  PA15
  #define E0_SERIAL_RX_PIN                  PA15
  #define E1_SERIAL_TX_PIN                  PC5
  #define E1_SERIAL_RX_PIN                  PC5
  #define E2_SERIAL_TX_PIN                  PE0
  #define E2_SERIAL_RX_PIN                  PE0
#endif

//
// Software SPI pins for TMC2130 stepper drivers
//
#define TMC_USE_SW_SPI
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
    #define TMC_SW_MOSI                     PE14
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO                     PE13
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK                      PE12
  #endif
#endif

#include "pins_FYSETC_S6.h"

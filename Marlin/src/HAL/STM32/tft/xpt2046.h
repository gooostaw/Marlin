/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef STM32F1xx
  #include <stm32f1xx_hal.h>
#elif defined(STM32F4xx)
  #include <stm32f4xx_hal.h>
#endif

#include "../../../inc/MarlinConfig.h"

// Not using regular SPI interface by default to avoid SPI mode conflicts with other SPI devices

#if !PIN_EXISTS(TOUCH_MISO)
  #error "TOUCH_MISO_PIN is not defined."
#elif !PIN_EXISTS(TOUCH_MOSI)
  #error "TOUCH_MOSI_PIN is not defined."
#elif !PIN_EXISTS(TOUCH_SCK)
  #error "TOUCH_SCK_PIN is not defined."
#elif !PIN_EXISTS(TOUCH_CS)
  #error "TOUCH_CS_PIN is not defined."
#endif

#ifndef TOUCH_INT_PIN
  #define TOUCH_INT_PIN  -1
#endif

#define XPT2046_DFR_MODE        0x00
#define XPT2046_SER_MODE        0x04
#define XPT2046_CONTROL         0x80

enum XPTCoordinate : uint8_t {
  XPT2046_X  = 0x10 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Y  = 0x50 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Z1 = 0x30 | XPT2046_CONTROL | XPT2046_DFR_MODE,
  XPT2046_Z2 = 0x40 | XPT2046_CONTROL | XPT2046_DFR_MODE,
};

#ifndef XPT2046_Z1_THRESHOLD
  #define XPT2046_Z1_THRESHOLD 10
#endif

class XPT2046 {
private:
  static SPI_HandleTypeDef SPIx;

  static bool isBusy() { return false; }

  static uint16_t getRawData(const XPTCoordinate coordinate);
  static bool isTouched();

  static void DataTransferBegin() { if (SPIx.Instance) { HAL_SPI_Init(&SPIx); } WRITE(TOUCH_CS_PIN, LOW); };
  static void DataTransferEnd() { WRITE(TOUCH_CS_PIN, HIGH); };
  static uint16_t HardwareIO(uint16_t data);
  static uint16_t SoftwareIO(uint16_t data);
  static uint16_t IO(uint16_t data = 0) { return SPIx.Instance ? HardwareIO(data) : SoftwareIO(data); }

public:
  static void Init();
  static bool getRawPoint(int16_t *x, int16_t *y);
};

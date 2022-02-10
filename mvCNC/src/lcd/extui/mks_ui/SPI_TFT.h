/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../tft_io/tft_io.h"
#include <stdint.h>

class TFT {
public:
  TFT_IO tftio;
  void spi_init(uint8_t spiRate);
  void SetPoint(uint16_t x, uint16_t y, uint16_t point);
  void setWindow(uint16_t x, uint16_t y, uint16_t with, uint16_t height);
  void LCD_init();
  void LCD_clear(uint16_t color);
  void LCD_Draw_Logo();
};

extern TFT SPI_TFT;

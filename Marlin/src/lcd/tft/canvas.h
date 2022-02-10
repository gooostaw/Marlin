/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "tft_color.h"
#include "tft_string.h"
#include "tft_image.h"
#include "tft.h"

#include "../../inc/MarlinConfig.h"

class CANVAS {
  private:
    static uint16_t width, height;
    static uint16_t startLine, endLine;
    static uint16_t *buffer;

    inline static font_t *Font() { return TFT_String::font(); }
    inline static glyph_t *Glyph(uint8_t *character) { return TFT_String::glyph(character); }
    inline static uint16_t GetFontHeight() { return TFT_String::font_height(); }

    static void AddImage(int16_t x, int16_t y, uint8_t image_width, uint8_t image_height, colorMode_t color_mode, uint8_t *data, uint16_t *colors);
    static void AddImage(uint16_t x, uint16_t y, uint16_t imageWidth, uint16_t imageHeight, uint16_t color, uint16_t bgColor, uint8_t *image);

  public:
    static void New(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    static void Continue();
    static bool ToScreen();

    static void SetBackground(uint16_t color);
    static void AddText(uint16_t x, uint16_t y, uint16_t color, uint8_t *string, uint16_t maxWidth);
    static void AddImage(int16_t x, int16_t y, MarlinImage image, uint16_t *colors);

    static void AddRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
    static void AddBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
};

extern CANVAS Canvas;

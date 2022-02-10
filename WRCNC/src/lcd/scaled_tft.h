/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../inc/WRCNCConfig.h"

#ifndef GRAPHICAL_TFT_UPSCALE
  #define GRAPHICAL_TFT_UPSCALE 2
#endif

#ifndef TFT_WIDTH
  #if GRAPHICAL_TFT_UPSCALE == 3
    #define TFT_WIDTH 480
  #else
    #define TFT_WIDTH 320
  #endif
#endif
#ifndef TFT_HEIGHT
  #if GRAPHICAL_TFT_UPSCALE == 3
    #define TFT_HEIGHT 320
  #else
    #define TFT_HEIGHT 240
  #endif
#endif

#ifndef TFT_PIXEL_OFFSET_X
  #if GRAPHICAL_TFT_UPSCALE == 2
    #define TFT_PIXEL_OFFSET_X 32
  #else
    #define TFT_PIXEL_OFFSET_X 48
  #endif
#endif

#ifndef TFT_PIXEL_OFFSET_Y
  #define TFT_PIXEL_OFFSET_Y 32 // 32 is best for both 320x240 and 480x320
#endif

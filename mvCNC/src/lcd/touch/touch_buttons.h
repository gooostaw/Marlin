/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <stdint.h>

#include "../../inc/mvCNCConfig.h"
#include "../scaled_tft.h"

#define UPSCALE0(M) ((M) * (GRAPHICAL_TFT_UPSCALE))
#define UPSCALE(A,M) (UPSCALE0(M) + (A))

#define BUTTON_DRAW_WIDTH  32
#define BUTTON_DRAW_HEIGHT 20

#define BUTTON_WIDTH  UPSCALE0(BUTTON_DRAW_WIDTH)
#define BUTTON_HEIGHT UPSCALE0(BUTTON_DRAW_HEIGHT)

// calc the space between buttons
#define BUTTON_SPACING (((TFT_WIDTH) - (BUTTON_WIDTH * 4)) / 5)

#define BUTTOND_X_LO BUTTON_SPACING
#define BUTTOND_X_HI BUTTOND_X_LO + BUTTON_WIDTH - 1

#define BUTTONA_X_LO BUTTOND_X_HI + BUTTON_SPACING
#define BUTTONA_X_HI BUTTONA_X_LO + BUTTON_WIDTH - 1

#define BUTTONB_X_LO BUTTONA_X_HI + BUTTON_SPACING
#define BUTTONB_X_HI BUTTONB_X_LO + BUTTON_WIDTH - 1

#define BUTTONC_X_LO BUTTONB_X_HI + BUTTON_SPACING
#define BUTTONC_X_HI BUTTONC_X_LO + BUTTON_WIDTH - 1

#define BUTTON_Y_HI (TFT_HEIGHT) - BUTTON_SPACING
#define BUTTON_Y_LO BUTTON_Y_HI - BUTTON_HEIGHT

#define TSLP_PREINIT  0
#define TSLP_SLEEPING 1

class TouchButtons {
public:
  static void init();
  static uint8_t read_buttons();
  #if HAS_TOUCH_SLEEP
    static millis_t next_sleep_ms;
    static bool isSleeping() { return next_sleep_ms == TSLP_SLEEPING; }
    static void sleepTimeout();
    static void wakeUp();
  #endif
};

extern TouchButtons touchBt;

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Implementation of the LCD display routines for a TFT GLCD displays with external controller.
 */

#include "../../inc/MarlinConfig.h"

#if IS_TFTGLCD_PANEL

#include "../../libs/duration_t.h"

////////////////////////////////////
// Set up button and encode mappings for each panel (into 'buttons' variable)
//
// This is just to map common functions (across different panels) onto the same
// macro name. The mapping is independent of whether the button is directly connected or
// via a shift/i2c register.

////////////////////////////////////
// Create LCD class instance and chipset-specific information
class TFTGLCD {
  private:
  public:
    TFTGLCD();
    void clear_buffer();
    void clr_screen();
    void setCursor(uint8_t col, uint8_t row);
    void write(char c);
    void print(const char *line);
    void print_line();
    void print_screen();
    void redraw_screen();
    void setContrast(uint16_t contrast);
};

extern TFTGLCD lcd;

#include "../fontutils.h"
#include "../lcdprint.h"

// Use panel encoder - free old encoder pins
#undef BTN_EN1
#undef BTN_EN2
#undef BTN_ENC

#ifndef EN_C
  #define EN_C       4 // for click
#endif

#endif // IS_TFTGLCD_PANEL

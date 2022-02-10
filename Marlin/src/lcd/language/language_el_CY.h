/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * Greek (Cyprus)
 *
 * LCD Menu Messages
 * See also https://marlinfw.org/docs/development/lcd_language.html
 */

#include "language_el.h"

namespace Language_el_CY {
  using namespace Language_el; // Inherit undefined strings from Greek (or English)

  constexpr uint8_t CHARSIZE              = 2;
  LSTR LANGUAGE                           = _UxGT("Greek (Cyprus)");
}

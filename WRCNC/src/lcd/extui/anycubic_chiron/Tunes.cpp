/**
 * Webber Ranch CNC Firmware
*/

/**
 * lcd/extui/anycubic_chiron/Tunes.cpp
 *
 * Extensible_UI implementation for Anycubic Chiron
 * Written By Nick Wells, 2020 [https://github.com/SwiftNick]
 *  (not affiliated with Anycubic, Ltd.)
 */

/***********************************************************************
 * A Utility to play tunes using the buzzer in the printer controller. *
 * See Tunes.h for note and tune definitions.                          *
 ***********************************************************************/

#include "../../../inc/WRCNCConfigPre.h"

#if ENABLED(ANYCUBIC_LCD_CHIRON)

#include "Tunes.h"
#include "../ui_api.h"

namespace Anycubic {

  void PlayTune(uint8_t beeperPin, const uint16_t *tune, uint8_t speed=1) {
    uint8_t pos = 1;
    uint16_t wholenotelen = tune[0] / speed;
    do {
      uint16_t freq = tune[pos];
      uint16_t notelen = wholenotelen / tune[pos + 1];

      ::tone(beeperPin, freq, notelen);
      ExtUI::delay_ms(notelen);
      pos += 2;

      if (pos >= MAX_TUNE_LENGTH) break;
    } while (tune[pos] != n_END);
  }

}

#endif // ANYCUBIC_LCD_CHIRON

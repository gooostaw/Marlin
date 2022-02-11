/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../core/macros.h"

#if BOTH(SDSUPPORT, HAS_MVCNCUI_U8GLIB) && (LCD_PINS_D4 == SD_SCK_PIN || LCD_PINS_ENABLE == SD_MOSI_PIN || DOGLCD_SCK == SD_SCK_PIN || DOGLCD_MOSI == SD_MOSI_PIN)
  #define LPC_SOFTWARE_SPI  // If the SD card and LCD adapter share the same SPI pins, then software SPI is currently
                            // needed due to the speed and mode required for communicating with each device being different.
                            // This requirement can be removed if the SPI access to these devices is updated to use
                            // spiBeginTransaction.
#endif

/** onboard SD card */
//#define SD_SCK_PIN        P0_07
//#define SD_MISO_PIN       P0_08
//#define SD_MOSI_PIN       P0_09
//#define SD_SS_PIN         P0_06
/** external */
#ifndef SD_SCK_PIN
  #define SD_SCK_PIN        P0_15
#endif
#ifndef SD_MISO_PIN
  #define SD_MISO_PIN       P0_17
#endif
#ifndef SD_MOSI_PIN
  #define SD_MOSI_PIN       P0_18
#endif
#ifndef SD_SS_PIN
  #define SD_SS_PIN         P1_23
#endif
#if !defined(SDSS) || SDSS == P_NC // gets defaulted in pins.h
  #undef SDSS
  #define SDSS          SD_SS_PIN
#endif

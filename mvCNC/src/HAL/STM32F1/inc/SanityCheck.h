/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Test STM32F1-specific configuration values for errors at compile-time.
 */

#if ENABLED(SDCARD_EEPROM_EMULATION) && DISABLED(SDSUPPORT)
  #undef SDCARD_EEPROM_EMULATION // Avoid additional error noise
  #if USE_FALLBACK_EEPROM
    #warning "EEPROM type not specified. Fallback is SDCARD_EEPROM_EMULATION."
  #endif
  #error "SDCARD_EEPROM_EMULATION requires SDSUPPORT. Enable SDSUPPORT or choose another EEPROM emulation."
#endif

#if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
  #error "SERIAL_STATS_MAX_RX_QUEUED is not supported on the STM32F1 platform."
#elif ENABLED(SERIAL_STATS_DROPPED_RX)
  #error "SERIAL_STATS_DROPPED_RX is not supported on the STM32F1 platform."
#endif

#if ENABLED(NEOPIXEL_LED) && DISABLED(FYSETC_MINI_12864_2_1)
  #error "NEOPIXEL_LED (Adafruit NeoPixel) is not supported for HAL/STM32F1. Comment out this line to proceed at your own risk!"
#endif

// Emergency Parser needs at least one serial with HardwareSerial or USBComposite.
// The USBSerial maple don't allow any hook to implement EMERGENCY_PARSER.
// And copy all USBSerial code to mvcnc space to support EMERGENCY_PARSER, when we have another options, don't worth it.
#if ENABLED(EMERGENCY_PARSER) && !defined(USE_USB_COMPOSITE) && ((SERIAL_PORT == -1 && !defined(SERIAL_PORT_2)) || (SERIAL_PORT_2 == -1 && !defined(SERIAL_PORT)))
  #error "EMERGENCY_PARSER is only supported by HardwareSerial or USBComposite in HAL/STM32F1."
#endif

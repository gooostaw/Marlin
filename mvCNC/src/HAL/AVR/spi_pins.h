/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Define SPI Pins: SCK, MISO, MOSI, SS
 */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  #define AVR_SCK_PIN  13
  #define AVR_MISO_PIN 12
  #define AVR_MOSI_PIN 11
  #define AVR_SS_PIN   10
#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) || defined(__AVR_ATmega1284P__)
  #define AVR_SCK_PIN  7
  #define AVR_MISO_PIN 6
  #define AVR_MOSI_PIN 5
  #define AVR_SS_PIN   4
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define AVR_SCK_PIN  52
  #define AVR_MISO_PIN 50
  #define AVR_MOSI_PIN 51
  #define AVR_SS_PIN   53
#elif defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__)
  #define AVR_SCK_PIN  21
  #define AVR_MISO_PIN 23
  #define AVR_MOSI_PIN 22
  #define AVR_SS_PIN   20
#elif defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2561__)
  #define AVR_SCK_PIN  10
  #define AVR_MISO_PIN 12
  #define AVR_MOSI_PIN 11
  #define AVR_SS_PIN   16
#endif

#ifndef SD_SCK_PIN
  #define SD_SCK_PIN  AVR_SCK_PIN
#endif
#ifndef SD_MISO_PIN
  #define SD_MISO_PIN AVR_MISO_PIN
#endif
#ifndef SD_MOSI_PIN
  #define SD_MOSI_PIN AVR_MOSI_PIN
#endif
#ifndef SD_SS_PIN
  #define SD_SS_PIN   AVR_SS_PIN
#endif

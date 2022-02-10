/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define XSTR(V...) #V

#ifdef __AVR__
  #define HAL_PATH(PATH, NAME) XSTR(PATH/AVR/NAME)
#elif defined(ARDUINO_ARCH_SAM)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/DUE/NAME)
#elif defined(__MK20DX256__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/TEENSY31_32/NAME)
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/TEENSY35_36/NAME)
#elif defined(__IMXRT1062__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/TEENSY40_41/NAME)
#elif defined(TARGET_LPC1768)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/LPC1768/NAME)
#elif defined(__STM32F1__) || defined(TARGET_STM32F1)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/STM32F1/NAME)
#elif defined(ARDUINO_ARCH_STM32)
  #ifndef HAL_STM32
    #define HAL_STM32
  #endif
  #define HAL_PATH(PATH, NAME) XSTR(PATH/STM32/NAME)
#elif defined(ARDUINO_ARCH_ESP32)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/ESP32/NAME)
#elif defined(__PLAT_LINUX__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/LINUX/NAME)
#elif defined(__PLAT_NATIVE_SIM__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/NATIVE_SIM/NAME)
#elif defined(__SAMD51__)
  #define HAL_PATH(PATH, NAME) XSTR(PATH/SAMD51/NAME)
#else
  #error "Unsupported Platform!"
#endif

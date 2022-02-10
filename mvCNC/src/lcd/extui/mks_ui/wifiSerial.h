/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef SERIAL_PORT_2
  #error "SERIAL_PORT_2 must be disabled with TFT_LVGL_UI* and MKS_WIFI_MODULE."
#endif

#define WIFI_BAUDRATE          115200
#define WIFI_UPLOAD_BAUDRATE  1958400
#define USART_SAFE_INSERT

#define WIFI_RX_BUF_SIZE  (1024)
#define WIFI_TX_BUF_SIZE  (64)

#include "tft_lvgl_configuration.h"

#ifdef __STM32F1__
  #include "wifiSerial_STM32F1.h"
#else
  #include "wifiSerial_STM32.h"
#endif

extern WifiSerial WifiSerial1;
#define WIFISERIAL WifiSerial1

/**
 * Modern Vintage CNC Firmware
*/
#ifdef __STM32F1__

#include "../../../inc/mvCNCConfigPre.h"

#if BOTH(HAS_TFT_LVGL_UI, MKS_WIFI_MODULE)

#include "tft_lvgl_configuration.h"

#include "draw_ui.h"
#include "wifiSerial.h"

#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <libmaple/usart.h>
#include <libmaple/ring_buffer.h>

#include "../../../inc/mvCNCConfig.h"

#ifdef __cplusplus
  extern "C" {
#endif

#define WIFI_IO1_SET()    WRITE(WIFI_IO1_PIN, HIGH);
#define WIFI_IO1_RESET()  WRITE(WIFI_IO1_PIN, LOW);

void __irq_usart1() {
  if ((USART1_BASE->CR1 & USART_CR1_RXNEIE) && (USART1_BASE->SR & USART_SR_RXNE))
    WRITE(WIFI_IO1_PIN, HIGH);

  WIFISERIAL.wifi_usart_irq(USART1_BASE);
}

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

#endif // HAS_TFT_LVGL_UI && MKS_WIFI_MODULE
#endif // __STM32F1__

/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"
#include "Delay.h"

void esp_wifi_init(void) {                          // init ESP01 WIFI module pins
  #if PIN_EXISTS(ESP_WIFI_MODULE_GPIO0)
    OUT_WRITE(ESP_WIFI_MODULE_GPIO0_PIN, HIGH);
  #endif
  #if PIN_EXISTS(ESP_WIFI_MODULE_GPIO2)
    OUT_WRITE(ESP_WIFI_MODULE_GPIO2_PIN, HIGH);
  #endif
  #if PIN_EXISTS(ESP_WIFI_MODULE_RESET)
    delay(1);  // power up delay (0.1mS minimum)
    OUT_WRITE(ESP_WIFI_MODULE_RESET_PIN, LOW);
    delay(1);
    OUT_WRITE(ESP_WIFI_MODULE_RESET_PIN, HIGH);
  #endif
  #if PIN_EXISTS(ESP_WIFI_MODULE_ENABLE)
    delay(1);  // delay after reset released (0.1mS minimum)
    OUT_WRITE(ESP_WIFI_MODULE_ENABLE_PIN, HIGH);
  #endif
}

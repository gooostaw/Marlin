/**
 * Modern Vintage CNC Firmware
*/
#ifdef __PLAT_LINUX__

#include "../../inc/mvCNCConfig.h"
#include "../shared/Delay.h"

MSerialT usb_serial(TERN0(EMERGENCY_PARSER, true));

// U8glib required functions
extern "C" {
  void u8g_xMicroDelay(uint16_t val) { DELAY_US(val); }
  void u8g_MicroDelay()              { u8g_xMicroDelay(1); }
  void u8g_10MicroDelay()            { u8g_xMicroDelay(10); }
  void u8g_Delay(uint16_t val)       { delay(val); }
}

//************************//

// return free heap space
int freeMemory() {
  return 0;
}

// ------------------------
// ADC
// ------------------------

void HAL_adc_init() {

}

void HAL_adc_enable_channel(const uint8_t ch) {

}

uint8_t active_ch = 0;
void HAL_adc_start_conversion(const uint8_t ch) {
  active_ch = ch;
}

bool HAL_adc_finished() {
  return true;
}

uint16_t HAL_adc_get_result() {
  pin_t pin = analogInputToDigitalPin(active_ch);
  if (!VALID_PIN(pin)) return 0;
  uint16_t data = ((Gpio::get(pin) >> 2) & 0x3FF);
  return data;    // return 10bit value as mvCNC expects
}

void HAL_pwm_init() {

}

void HAL_reboot() { /* Reset the application state and GPIO */ }

#endif // __PLAT_LINUX__

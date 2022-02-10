/**
 * Webber Ranch CNC Firmware
*/
#ifdef __PLAT_LINUX__

#include "Clock.h"
#include <stdio.h>
#include "../../../inc/WRCNCConfig.h"

#include "Heater.h"

Heater::Heater(pin_t heater, pin_t adc) {
  heater_state = 0;
  room_temp_raw = 150;
  last = Clock::micros();
  heater_pin = heater;
  adc_pin = adc;
  heat = 0.0;
}

Heater::~Heater() {
}

void Heater::update() {
  // crude pwm read and cruder heat simulation
  auto now = Clock::micros();
  double delta = (now - last);
  if (delta > 1000 ) {
    heater_state = pwmcap.update(0xFFFF * Gpio::pin_map[heater_pin].value);
    last = now;
    heat += (heater_state - heat) * (delta / 1000000000.0);

    NOLESS(heat, room_temp_raw);
    Gpio::pin_map[analogInputToDigitalPin(adc_pin)].value = 0xFFFF - (uint16_t)heat;
  }
}

void Heater::interrupt(GpioEvent ev) {
  // unused
}

#endif // __PLAT_LINUX__

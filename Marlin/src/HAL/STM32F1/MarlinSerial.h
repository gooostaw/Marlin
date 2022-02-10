/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <HardwareSerial.h>
#include <libmaple/usart.h>
#include <WString.h>

#include "../../inc/MarlinConfigPre.h"
#include "../../core/serial_hook.h"

// Increase priority of serial interrupts, to reduce overflow errors
#define UART_IRQ_PRIO 1

struct MarlinSerial : public HardwareSerial {
  MarlinSerial(struct usart_dev *usart_device, uint8 tx_pin, uint8 rx_pin) : HardwareSerial(usart_device, tx_pin, rx_pin) { }

  #ifdef UART_IRQ_PRIO
    // Shadow the parent methods to set IRQ priority after begin()
    void begin(uint32 baud) {
      MarlinSerial::begin(baud, SERIAL_8N1);
    }

    void begin(uint32 baud, uint8_t config) {
      HardwareSerial::begin(baud, config);
      nvic_irq_set_priority(c_dev()->irq_num, UART_IRQ_PRIO);
    }
  #endif
};

typedef Serial1Class<MarlinSerial> MSerialT;

extern MSerialT MSerial1;
extern MSerialT MSerial2;
extern MSerialT MSerial3;
#if EITHER(STM32_HIGH_DENSITY, STM32_XL_DENSITY)
  extern MSerialT MSerial4;
  extern MSerialT MSerial5;
#endif

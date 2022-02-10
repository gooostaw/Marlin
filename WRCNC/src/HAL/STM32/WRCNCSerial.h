/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../inc/WRCNCConfigPre.h"

#if ENABLED(EMERGENCY_PARSER)
  #include "../../feature/e_parser.h"
#endif

#include "../../core/serial_hook.h"

typedef void (*usart_rx_callback_t)(serial_t * obj);

struct WRCNCSerial : public HardwareSerial {
  WRCNCSerial(void *peripheral, usart_rx_callback_t rx_callback) :
      HardwareSerial(peripheral), _rx_callback(rx_callback)
  { }

  void begin(unsigned long baud, uint8_t config);
  inline void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }

  void _rx_complete_irq(serial_t *obj);

protected:
  usart_rx_callback_t _rx_callback;
};

typedef Serial1Class<WRCNCSerial> MSerialT;
extern MSerialT MSerial1;
extern MSerialT MSerial2;
extern MSerialT MSerial3;
extern MSerialT MSerial4;
extern MSerialT MSerial5;
extern MSerialT MSerial6;
extern MSerialT MSerial7;
extern MSerialT MSerial8;
extern MSerialT MSerial9;
extern MSerialT MSerial10;
extern MSerialT MSerialLP1;

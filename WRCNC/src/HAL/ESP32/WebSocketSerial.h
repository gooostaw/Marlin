/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../inc/WRCNCConfig.h"
#include "../../core/serial_hook.h"

#include <Stream.h>

#ifndef TX_BUFFER_SIZE
  #define TX_BUFFER_SIZE 32
#endif
#if ENABLED(WIFISUPPORT)
  #ifndef RX_BUFFER_SIZE
    #define RX_BUFFER_SIZE 128
  #endif
  #if TX_BUFFER_SIZE <= 0
    #error "TX_BUFFER_SIZE is required for the WebSocket."
  #endif
#endif

typedef uint16_t ring_buffer_pos_t;

class RingBuffer {
  uint8_t *data;
  ring_buffer_pos_t size, read_index, write_index;

public:
  RingBuffer(ring_buffer_pos_t size);
  ~RingBuffer();

  int available();
  int peek();
  int read();
  ring_buffer_pos_t read(uint8_t *buffer);
  void flush();
  ring_buffer_pos_t write(const uint8_t c);
  ring_buffer_pos_t write(const uint8_t *buffer, ring_buffer_pos_t size);
};

class WebSocketSerial: public Stream {
  RingBuffer rx_buffer;
  RingBuffer tx_buffer;

public:
  WebSocketSerial();
  void begin(const long);
  void end();
  int available();
  int peek();
  int read();
  void flush();
  size_t write(const uint8_t c);
  size_t write(const uint8_t *buffer, size_t size);

  #if ENABLED(SERIAL_STATS_DROPPED_RX)
    FORCE_INLINE uint32_t dropped() { return 0; }
  #endif

  #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
    FORCE_INLINE int rxMaxEnqueued() { return 0; }
  #endif
};

typedef Serial1Class<WebSocketSerial> MSerialWebSocketT;
extern MSerialWebSocketT webSocketSerial;

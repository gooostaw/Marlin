/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "softspi.h"
#include <stdint.h>

template<uint8_t MisoPin, uint8_t MosiPin, uint8_t SckPin>
class SPIclass {
  static SoftSPI<MisoPin, MosiPin, SckPin> softSPI;
  public:
    FORCE_INLINE static void init() { softSPI.begin(); }
    FORCE_INLINE static void send(uint8_t data) { softSPI.send(data); }
    FORCE_INLINE static uint8_t receive() { return softSPI.receive(); }
};

// Hardware SPI
template<>
class SPIclass<SD_MISO_PIN, SD_MOSI_PIN, SD_SCK_PIN> {
  public:
    FORCE_INLINE static void init() {
      OUT_WRITE(SD_SCK_PIN, LOW);
      OUT_WRITE(SD_MOSI_PIN, HIGH);
      SET_INPUT_PULLUP(SD_MISO_PIN);
    }
    FORCE_INLINE static uint8_t receive() {
      #if defined(__AVR__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
        SPDR = 0;
        for (;!TEST(SPSR, SPIF););
        return SPDR;
      #else
        return spiRec();
      #endif
    }
};

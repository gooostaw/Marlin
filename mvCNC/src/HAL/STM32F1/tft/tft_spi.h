/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfig.h"

#include <SPI.h>

#ifndef LCD_READ_ID
  #define LCD_READ_ID 0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#define DATASIZE_8BIT    DATA_SIZE_8BIT
#define DATASIZE_16BIT   DATA_SIZE_16BIT
#define TFT_IO_DRIVER TFT_SPI

#define DMA_MINC_ENABLE 1
#define DMA_MINC_DISABLE 0

class TFT_SPI {
private:
  static uint32_t ReadID(uint16_t Reg);
  static void Transmit(uint16_t Data);
  static void TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);

public:
  static SPIClass SPIx;

  static void Init();
  static uint32_t GetID();
  static bool isBusy();
  static void Abort();

  static void DataTransferBegin(uint16_t DataWidth = DATA_SIZE_16BIT);
  static void DataTransferEnd() { WRITE(TFT_CS_PIN, HIGH); SPIx.end(); };
  static void DataTransferAbort();

  static void WriteData(uint16_t Data) { Transmit(Data); }
  static void WriteReg(uint16_t Reg) { WRITE(TFT_A0_PIN, LOW); Transmit(Reg); WRITE(TFT_A0_PIN, HIGH); }

  static void WriteSequence(uint16_t *Data, uint16_t Count) { TransmitDMA(DMA_MINC_ENABLE, Data, Count); }
  static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_MINC_DISABLE, &Data, Count); }
  static void WriteMultiple(uint16_t Color, uint32_t Count) {
    static uint16_t Data; Data = Color;
    while (Count > 0) {
      TransmitDMA(DMA_MINC_DISABLE, &Data, Count > 0xFFFF ? 0xFFFF : Count);
      Count = Count > 0xFFFF ? Count - 0xFFFF : 0;
    }
  }
};

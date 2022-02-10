/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfig.h"

#include <SPI.h>
#include <lpc17xx_ssp.h>
// #include <lpc17xx_gpdma.h>

#ifndef LCD_READ_ID
  #define LCD_READ_ID  0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#define DATASIZE_8BIT    SSP_DATABIT_8
#define DATASIZE_16BIT   SSP_DATABIT_16
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

  static void DataTransferBegin(uint16_t DataWidth = DATASIZE_16BIT);
  static void DataTransferEnd() { OUT_WRITE(TFT_CS_PIN, HIGH); SPIx.end(); };
  static void DataTransferAbort();

  static void WriteData(uint16_t Data) { Transmit(Data); }
  static void WriteReg(uint16_t Reg) { OUT_WRITE(TFT_A0_PIN, LOW); Transmit(Reg); OUT_WRITE(TFT_A0_PIN, HIGH); }

  static void WriteSequence(uint16_t *Data, uint16_t Count) { TransmitDMA(DMA_MINC_ENABLE, Data, Count); }
  // static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_MINC_DISABLE, &Data, Count); }
  static void WriteMultiple(uint16_t Color, uint32_t Count) {
    static uint16_t Data; Data = Color;
    //LPC dma can only write 0xFFF bytes at once.
    #define MAX_DMA_SIZE (0xFFF - 1)
    while (Count > 0) {
      TransmitDMA(DMA_MINC_DISABLE, &Data, Count > MAX_DMA_SIZE ? MAX_DMA_SIZE : Count);
      Count = Count > MAX_DMA_SIZE ? Count - MAX_DMA_SIZE : 0;
    }
    #undef MAX_DMA_SIZE
  }
};

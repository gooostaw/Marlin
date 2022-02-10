/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifndef LCD_READ_ID
  #define LCD_READ_ID  0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#include <libmaple/dma.h>

#define DATASIZE_8BIT  DMA_SIZE_8BITS
#define DATASIZE_16BIT DMA_SIZE_16BITS
#define TFT_IO_DRIVER  TFT_FSMC

typedef struct {
  __IO uint16_t REG;
  __IO uint16_t RAM;
} LCD_CONTROLLER_TypeDef;

class TFT_FSMC {
  private:
    static LCD_CONTROLLER_TypeDef *LCD;

    static uint32_t ReadID(uint16_t Reg);
    static void Transmit(uint16_t Data);
    static void TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);

  public:
    static void Init();
    static uint32_t GetID();
    static bool isBusy();
    static void Abort();

    static void DataTransferBegin(uint16_t DataWidth = DATASIZE_16BIT) {};
    static void DataTransferEnd() {};

    static void WriteData(uint16_t Data) { Transmit(Data); }
    static void WriteReg(uint16_t Reg);

    static void WriteSequence(uint16_t *Data, uint16_t Count) { TransmitDMA(DMA_PINC_MODE, Data, Count); }
    static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_CIRC_MODE, &Data, Count); }
    static void WriteMultiple(uint16_t Color, uint32_t Count) {
      static uint16_t Data; Data = Color;
      while (Count > 0) {
        TransmitDMA(DMA_CIRC_MODE, &Data, Count > 0xFFFF ? 0xFFFF : Count);
        Count = Count > 0xFFFF ? Count - 0xFFFF : 0;
      }
    }
};

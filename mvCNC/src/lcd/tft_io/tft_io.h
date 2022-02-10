/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../inc/mvCNCConfig.h"

#if HAS_SPI_TFT
  #include HAL_PATH(../../HAL, tft/tft_spi.h)
#elif HAS_FSMC_TFT
  #include HAL_PATH(../../HAL, tft/tft_fsmc.h)
#elif HAS_LTDC_TFT
  #include HAL_PATH(../../HAL, tft/tft_ltdc.h)
#else
  #error "TFT IO only supports SPI, FSMC or LTDC interface"
#endif

#define TFT_EXCHANGE_XY _BV32(1)
#define TFT_INVERT_X    _BV32(2)
#define TFT_INVERT_Y    _BV32(3)

#define TFT_NO_ROTATION           (0x00)
#define TFT_ROTATE_90             (TFT_EXCHANGE_XY | TFT_INVERT_X)
#define TFT_ROTATE_180            (TFT_INVERT_X    | TFT_INVERT_Y)
#define TFT_ROTATE_270            (TFT_EXCHANGE_XY | TFT_INVERT_Y)

#define TFT_MIRROR_X              (TFT_INVERT_Y)
#define TFT_MIRROR_Y              (TFT_INVERT_X)

#define TFT_ROTATE_90_MIRROR_X    (TFT_ROTATE_90 ^ TFT_INVERT_Y)
#define TFT_ROTATE_90_MIRROR_Y    (TFT_ROTATE_90 ^ TFT_INVERT_X)

#define TFT_ROTATE_180_MIRROR_X   (TFT_ROTATE_180 ^ TFT_INVERT_Y)
#define TFT_ROTATE_180_MIRROR_Y   (TFT_ROTATE_180 ^ TFT_INVERT_X)

#define TFT_ROTATE_270_MIRROR_X   (TFT_ROTATE_270 ^ TFT_INVERT_Y)
#define TFT_ROTATE_270_MIRROR_Y   (TFT_ROTATE_270 ^ TFT_INVERT_X)

// TFT_ROTATION is user configurable
#ifndef TFT_ROTATION
  #define TFT_ROTATION TFT_NO_ROTATION
#endif

// TFT_ORIENTATION is the "sum" of TFT_DEFAULT_ORIENTATION plus user TFT_ROTATION
#define TFT_ORIENTATION ((TFT_DEFAULT_ORIENTATION) ^ (TFT_ROTATION))

#define TFT_COLOR_RGB   _BV32(3)
#define TFT_COLOR_BGR   _BV32(4)

// Each TFT Driver is responsible for its default color mode.
// #ifndef TFT_COLOR
//   #define TFT_COLOR   TFT_COLOR_RGB
// #endif

#define TOUCH_ORIENTATION_NONE  0
#define TOUCH_LANDSCAPE         1
#define TOUCH_PORTRAIT          2

#ifndef TOUCH_CALIBRATION_X
  #define TOUCH_CALIBRATION_X   0
#endif
#ifndef TOUCH_CALIBRATION_Y
  #define TOUCH_CALIBRATION_Y   0
#endif
#ifndef TOUCH_OFFSET_X
  #define TOUCH_OFFSET_X        0
#endif
#ifndef TOUCH_OFFSET_Y
  #define TOUCH_OFFSET_Y        0
#endif
#ifndef TOUCH_ORIENTATION
  #define TOUCH_ORIENTATION     TOUCH_LANDSCAPE
#endif

#ifndef TFT_DRIVER
  #define TFT_DRIVER    AUTO
#endif

#define ESC_REG(x)   0xFFFF, 0x00FF & (uint16_t)x
#define ESC_DELAY(x) 0xFFFF, 0x8000 | (x & 0x7FFF)
#define ESC_END      0xFFFF, 0x7FFF
#define ESC_FFFF     0xFFFF, 0xFFFF

class TFT_IO {
public:
  static TFT_IO_DRIVER io;

  static void InitTFT();
  static void set_window(uint16_t Xmin, uint16_t Ymin, uint16_t Xmax, uint16_t Ymax);
  static void write_esc_sequence(const uint16_t *Sequence);

  // Deletaged methods
  inline static void Init() { io.Init(); io.Abort(); };
  inline static bool isBusy() { return io.isBusy(); };
  inline static void Abort() { io.Abort(); };
  inline static uint32_t GetID() { return io.GetID(); };

  inline static void DataTransferBegin(uint16_t DataWidth = DATASIZE_16BIT) { io.DataTransferBegin(DataWidth); }
  inline static void DataTransferEnd() { io.DataTransferEnd(); };
  // inline static void DataTransferAbort() { io.DataTransferAbort(); };

  inline static void WriteData(uint16_t Data) { io.WriteData(Data); };
  inline static void WriteReg(uint16_t Reg) { io.WriteReg(Reg); };

  inline static void WriteSequence(uint16_t *Data, uint16_t Count) { io.WriteSequence(Data, Count); };

  #if ENABLED(USE_SPI_DMA_TC)
    inline static void WriteSequenceIT(uint16_t *Data, uint16_t Count) { io.WriteSequenceIT(Data, Count); };
  #endif

  // static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_MINC_DISABLE, &Data, Count); }
  inline static void WriteMultiple(uint16_t Color, uint32_t Count) { io.WriteMultiple(Color, Count); };

protected:
  static uint32_t lcd_id;
};

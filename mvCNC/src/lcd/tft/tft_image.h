/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../inc/mvCNCConfigPre.h"

#include <stdint.h>

extern const uint8_t mvcnc_logo_112x38x1[];
extern const uint8_t mvcnc_logo_228x255x2[];
extern const uint8_t mvcnc_logo_228x255x4[];
extern const uint16_t mvcnc_logo_195x59x16[];
extern const uint16_t mvcnc_logo_320x240x16[];
extern const uint16_t mvcnc_logo_480x320x16[];
extern const uint16_t background_320x30x16[];

extern const uint8_t hotend_64x64x4[];
extern const uint8_t bed_64x64x4[], bed_heated_64x64x4[];
extern const uint8_t chamber_64x64x4[], chamber_heated_64x64x4[];
extern const uint8_t fan0_64x64x4[], fan1_64x64x4[];
extern const uint8_t fan_slow0_64x64x4[], fan_slow1_64x64x4[];
extern const uint8_t fan_fast0_64x64x4[], fan_fast1_64x64x4[];
extern const uint8_t sd_64x64x4[];
extern const uint8_t home_64x64x4[];
extern const uint8_t btn_rounded_64x52x4[];
extern const uint8_t btn_rounded_42x39x4[];
extern const uint8_t menu_64x64x4[];
extern const uint8_t settings_64x64x4[];
extern const uint8_t confirm_64x64x4[];
extern const uint8_t cancel_64x64x4[];
extern const uint8_t increase_64x64x4[];
extern const uint8_t decrease_64x64x4[];
extern const uint8_t pause_64x64x4[];

extern const uint8_t feedrate_32x32x4[];
extern const uint8_t flowrate_32x32x4[];
extern const uint8_t directory_32x32x4[];
extern const uint8_t back_32x32x4[];
extern const uint8_t up_32x32x4[];
extern const uint8_t down_32x32x4[];
extern const uint8_t left_32x32x4[];
extern const uint8_t right_32x32x4[];
extern const uint8_t refresh_32x32x4[];
extern const uint8_t leveling_32x32x4[];

extern const uint8_t slider_8x16x4[];

enum mvCNCImage : uint8_t {
  imgBootScreen = 0x00,
  imgHotEnd,
  imgBed,
  imgBedHeated,
  imgChamber,
  imgChamberHeated,
  imgFanIdle,
  imgFanSlow0,
  imgFanSlow1,
  imgFanFast0,
  imgFanFast1,
  imgFeedRate,
  imgFlowRate,
  imgSD,
  imgMenu,
  imgSettings,
  imgDirectory,
  imgConfirm,
  imgCancel,
  imgIncrease,
  imgDecrease,
  imgBack,
  imgUp,
  imgDown,
  imgLeft,
  imgRight,
  imgRefresh,
  imgLeveling,
  imgSlider,
  imgHome,
  imgBtn52Rounded,
  imgBtn39Rounded,
  imgCount,
  noImage = imgCount,
  imgPageUp = imgLeft,
  imgPageDown = imgRight
};

enum colorMode_t : uint8_t {
  NOCOLORS = 0x00,
  MONOCHROME = 0x01,  // 1 bit per pixel
  GREYSCALE1 = 0x01,  // 1 bit per pixel
  GREYSCALE2,         // 2 bits per pixel
  GREYSCALE4,         // 4 bits per pixel
  HIGHCOLOR           // 16 bits per pixel
};

typedef colorMode_t ColorMode;

typedef struct __attribute__((__packed__)) {
  void *data;
  uint16_t width;
  uint16_t height;
  colorMode_t colorMode;
} tImage;

extern const tImage NoLogo;

#if ENABLED(SHOW_BOOTSCREEN)
  extern const tImage mvCNCLogo112x38x1;
  extern const tImage mvCNCLogo228x255x2;
  extern const tImage mvCNCLogo228x255x4;
  extern const tImage mvCNCLogo195x59x16;
  extern const tImage mvCNCLogo320x240x16;
  extern const tImage mvCNCLogo480x320x16;
#endif
extern const tImage Background320x30x16;

extern const tImage HotEnd_64x64x4;
extern const tImage Bed_64x64x4;
extern const tImage Bed_Heated_64x64x4;
extern const tImage Chamber_64x64x4;
extern const tImage Chamber_Heated_64x64x4;
extern const tImage Fan0_64x64x4;
extern const tImage Fan1_64x64x4;
extern const tImage Fan_Slow0_64x64x4;
extern const tImage Fan_Slow1_64x64x4;
extern const tImage Fan_Fast0_64x64x4;
extern const tImage Fan_Fast1_64x64x4;
extern const tImage SD_64x64x4;
extern const tImage Home_64x64x4;
extern const tImage BtnRounded_64x52x4;
extern const tImage BtnRounded_42x39x4;
extern const tImage Menu_64x64x4;
extern const tImage Settings_64x64x4;
extern const tImage Confirm_64x64x4;
extern const tImage Cancel_64x64x4;
extern const tImage Increase_64x64x4;
extern const tImage Decrease_64x64x4;
extern const tImage Pause_64x64x4;

extern const tImage Feedrate_32x32x4;
extern const tImage Flowrate_32x32x4;
extern const tImage Directory_32x32x4;
extern const tImage Back_32x32x4;
extern const tImage Up_32x32x4;
extern const tImage Down_32x32x4;
extern const tImage Left_32x32x4;
extern const tImage Right_32x32x4;
extern const tImage Refresh_32x32x4;
extern const tImage Leveling_32x32x4;

extern const tImage Slider8x16x4;

extern const tImage Images[imgCount];

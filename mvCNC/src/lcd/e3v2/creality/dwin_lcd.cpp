/**
 * Modern Vintage CNC Firmware
*/

/********************************************************************************
 * @file     lcd/e3v2/creality/dwin_lcd.cpp
 * @author   LEO / Creality3D
 * @date     2019/07/18
 * @version  2.0.1
 * @brief    DWIN screen control functions
 ********************************************************************************/

#include "../../../inc/mvCNCConfigPre.h"

#if ENABLED(DWIN_CREALITY_LCD)

#include "../../../inc/mvCNCConfig.h"

#include "dwin_lcd.h"

//#define DEBUG_OUT 1
#include "../../../core/debug_out.h"

/*-------------------------------------- System variable function --------------------------------------*/

void DWIN_Startup() {
  DEBUG_ECHOPGM("\r\nDWIN handshake ");
  delay(750);   // Delay here or init later in the boot process
  if (DWIN_Handshake()) DEBUG_ECHOLNPGM("ok."); else DEBUG_ECHOLNPGM("error.");
  DWIN_Frame_SetDir(1);
  #if DISABLED(SHOW_BOOTSCREEN)
    DWIN_Frame_Clear(Color_Bg_Black); // mvCNCUI handles the bootscreen so just clear here
  #endif
  DWIN_UpdateLCD();
}

/*---------------------------------------- Picture related functions ----------------------------------------*/

// Draw an Icon
//  libID: Icon library ID
//  picID: Icon ID
//  x/y: Upper-left point
void DWIN_ICON_Show(uint8_t libID, uint8_t picID, uint16_t x, uint16_t y) {
  DWIN_ICON_Show(true, false, false, libID, picID, x, y);
}

// Copy area from virtual display area to current screen
//  cacheID: virtual area number
//  xStart/yStart: Upper-left of virtual area
//  xEnd/yEnd: Lower-right of virtual area
//  x/y: Screen paste point
void DWIN_Frame_AreaCopy(uint8_t cacheID, uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t x, uint16_t y) {
  size_t i = 0;
  DWIN_Byte(i, 0x27);
  DWIN_Byte(i, 0x80 | cacheID);
  DWIN_Word(i, xStart);
  DWIN_Word(i, yStart);
  DWIN_Word(i, xEnd);
  DWIN_Word(i, yEnd);
  DWIN_Word(i, x);
  DWIN_Word(i, y);
  DWIN_Send(i);
}

#endif // DWIN_CREALITY_LCD

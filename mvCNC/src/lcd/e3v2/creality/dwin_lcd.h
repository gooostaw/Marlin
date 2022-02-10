/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/********************************************************************************
 * @file     dwin_lcd.h
 * @author   LEO / Creality3D
 * @date     2019/07/18
 * @version  2.0.1
 * @brief    迪文屏控制操作函数
 ********************************************************************************/

#include "../common/dwin_api.h"
#include "../common/dwin_set.h"
#include "../common/dwin_font.h"
#include "../common/dwin_color.h"

#define DWIN_FONT_MENU  font10x20
#define DWIN_FONT_STAT  font10x20
#define DWIN_FONT_HEAD  font10x20
#define DWIN_FONT_ALERT font14x28

// Copy area from virtual display area to current screen
//  cacheID: virtual area number
//  xStart/yStart: Upper-left of virtual area
//  xEnd/yEnd: Lower-right of virtual area
//  x/y: Screen paste point
void DWIN_Frame_AreaCopy(uint8_t cacheID, uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t x, uint16_t y);

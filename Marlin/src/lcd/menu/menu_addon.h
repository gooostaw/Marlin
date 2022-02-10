/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../lcdprint.h"

#define _MENU_ITEM_ADDON_START(N,X) do{ \
  if (ui.should_draw() && _menuLineNr == _thisItemNr - 1) { \
    N(X)

#define MENU_ITEM_ADDON_START(X)    _MENU_ITEM_ADDON_START(SETCURSOR_X,    X)
#define MENU_ITEM_ADDON_START_RJ(X) _MENU_ITEM_ADDON_START(SETCURSOR_X_RJ, X)

#define MENU_ITEM_ADDON_END() } }while(0)

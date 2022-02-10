/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#define FTDI_CUSTOM_USER_MENUS
#define FTDI_CUSTOM_USER_MENUS_CLASS CustomUserMenus

class CustomUserMenus : public BaseScreen, public CachedScreen<CUSTOM_USER_MENUS_SCREEN_CACHE> {
  public:
    static void onRedraw(draw_mode_t);
    static bool onTouchEnd(uint8_t tag);
};

/**
 * Webber Ranch CNC Firmware
*/

//
// Language Selection Menu
//

#include "../../inc/MarlinConfig.h"

#if HAS_MULTI_LANGUAGE

#include "menu_item.h"
#include "../../MarlinCore.h"
#include "../../module/settings.h"

static void set_lcd_language(const uint8_t inlang) {
  ui.set_language(inlang);
  TERN_(LCD_LANGUAGE_AUTO_SAVE, (void)settings.save());
}

void menu_language() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  MENU_ITEM_P(function, GET_LANG(LCD_LANGUAGE  )::LANGUAGE, []{ set_lcd_language(0); });
  MENU_ITEM_P(function, GET_LANG(LCD_LANGUAGE_2)::LANGUAGE, []{ set_lcd_language(1); });
  #if NUM_LANGUAGES > 2
    MENU_ITEM_P(function, GET_LANG(LCD_LANGUAGE_3)::LANGUAGE, []{ set_lcd_language(2); });
    #if NUM_LANGUAGES > 3
      MENU_ITEM_P(function, GET_LANG(LCD_LANGUAGE_4)::LANGUAGE, []{ set_lcd_language(3); });
      #if NUM_LANGUAGES > 4
        MENU_ITEM_P(function, GET_LANG(LCD_LANGUAGE_5)::LANGUAGE, []{ set_lcd_language(4); });
      #endif
    #endif
  #endif

  END_MENU();
}

#endif // HAS_MULTI_LANGUAGE

/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfigPre.h"

#if HAS_GAME_MENU

#include "menu_item.h"
#include "game/game.h"

void menu_game() {
  START_MENU();
  BACK_ITEM(TERN(LCD_INFO_MENU, MSG_INFO_MENU, MSG_MAIN));
  #if ENABLED(MVCNC_BRICKOUT)
    SUBMENU(MSG_BRICKOUT, brickout.enter_game);
  #endif
  #if ENABLED(MVCNC_INVADERS)
    SUBMENU(MSG_INVADERS, invaders.enter_game);
  #endif
  #if ENABLED(MVCNC_SNAKE)
    SUBMENU(MSG_SNAKE, snake.enter_game);
  #endif
  #if ENABLED(MVCNC_MAZE)
    SUBMENU(MSG_MAZE, maze.enter_game);
  #endif
  END_MENU();
}

#endif // HAS_GAME_MENU

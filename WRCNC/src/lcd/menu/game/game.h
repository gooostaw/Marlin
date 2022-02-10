/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../../inc/WRCNCConfigPre.h"
#include "../../dogm/wrcncui_DOGM.h"
#include "../../lcdprint.h"
#include "../../wrcncui.h"

//#define MUTE_GAMES

#if ENABLED(MUTE_GAMES) || !HAS_BUZZER
  #define _BUZZ(D,F) NOOP
#else
  #define _BUZZ(D,F) BUZZ(D,F)
#endif

#if HAS_GAME_MENU
  void menu_game();
#endif

#if ENABLED(WRCNC_BRICKOUT)
  #include "brickout.h"
#endif
#if ENABLED(WRCNC_INVADERS)
  #include "invaders.h"
#endif
#if ENABLED(WRCNC_MAZE)
  #include "maze.h"
#endif
#if ENABLED(WRCNC_SNAKE)
  #include "snake.h"
#endif

// Pool game data to save SRAM
union WRCNCGameData {
  #if ENABLED(WRCNC_BRICKOUT)
    brickout_data_t brickout;
  #endif
  #if ENABLED(WRCNC_INVADERS)
    invaders_data_t invaders;
  #endif
  #if ENABLED(WRCNC_SNAKE)
    snake_data_t snake;
  #endif
  #if ENABLED(WRCNC_MAZE)
    maze_data_t maze;
  #endif
};

extern WRCNCGameData wrcnc_game_data;

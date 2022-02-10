/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfigPre.h"
#include "../../dogm/mvcncui_DOGM.h"
#include "../../lcdprint.h"
#include "../../mvcncui.h"

//#define MUTE_GAMES

#if ENABLED(MUTE_GAMES) || !HAS_BUZZER
  #define _BUZZ(D,F) NOOP
#else
  #define _BUZZ(D,F) BUZZ(D,F)
#endif

#if HAS_GAME_MENU
  void menu_game();
#endif

#if ENABLED(mvCNC_BRICKOUT)
  #include "brickout.h"
#endif
#if ENABLED(mvCNC_INVADERS)
  #include "invaders.h"
#endif
#if ENABLED(mvCNC_MAZE)
  #include "maze.h"
#endif
#if ENABLED(mvCNC_SNAKE)
  #include "snake.h"
#endif

// Pool game data to save SRAM
union mvCNCGameData {
  #if ENABLED(mvCNC_BRICKOUT)
    brickout_data_t brickout;
  #endif
  #if ENABLED(mvCNC_INVADERS)
    invaders_data_t invaders;
  #endif
  #if ENABLED(mvCNC_SNAKE)
    snake_data_t snake;
  #endif
  #if ENABLED(mvCNC_MAZE)
    maze_data_t maze;
  #endif
};

extern mvCNCGameData mvcnc_game_data;

/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../../../inc/MarlinConfigPre.h"
#include "../../dogm/marlinui_DOGM.h"
#include "../../lcdprint.h"
#include "../../marlinui.h"

//#define MUTE_GAMES

#if ENABLED(MUTE_GAMES) || !HAS_BUZZER
  #define _BUZZ(D,F) NOOP
#else
  #define _BUZZ(D,F) BUZZ(D,F)
#endif

#if HAS_GAME_MENU
  void menu_game();
#endif

#if ENABLED(MARLIN_BRICKOUT)
  #include "brickout.h"
#endif
#if ENABLED(MARLIN_INVADERS)
  #include "invaders.h"
#endif
#if ENABLED(MARLIN_MAZE)
  #include "maze.h"
#endif
#if ENABLED(MARLIN_SNAKE)
  #include "snake.h"
#endif

// Pool game data to save SRAM
union MarlinGameData {
  #if ENABLED(MARLIN_BRICKOUT)
    brickout_data_t brickout;
  #endif
  #if ENABLED(MARLIN_INVADERS)
    invaders_data_t invaders;
  #endif
  #if ENABLED(MARLIN_SNAKE)
    snake_data_t snake;
  #endif
  #if ENABLED(MARLIN_MAZE)
    maze_data_t maze;
  #endif
};

extern MarlinGameData marlin_game_data;

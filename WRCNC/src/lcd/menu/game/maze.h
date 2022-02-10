/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "types.h"

typedef struct { pos_t pos; } maze_data_t;

class MazeGame : WRCNCGame { public: static void enter_game(), game_screen(); };

extern MazeGame maze;

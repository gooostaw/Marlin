/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "types.h"

#define BRICK_ROWS   4
#define BRICK_COLS  16

typedef struct {
  uint8_t balls_left, brick_count;
  uint16_t bricks[BRICK_ROWS];
  int8_t paddle_x, hit_dir;
  fixed_t ballx, bally, ballh, ballv;
} brickout_data_t;

class BrickoutGame : MarlinGame { public: static void enter_game(), game_screen(); };

extern BrickoutGame brickout;

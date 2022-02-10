/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "types.h"

typedef struct {
  int8_t snake_dir,     // NESW
         foodx, foody,
         food_cnt,
         old_encoder;
  pos_t snake_tail[50];
  fixed_t snakex, snakey;
  uint8_t head_ind;
} snake_data_t;

class SnakeGame : mvCNCGame { public: static void enter_game(), game_screen(); };

extern SnakeGame snake;

/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfigPre.h"

#if HAS_GAMES

#include "game.h"

int MarlinGame::score;
uint8_t MarlinGame::game_state;
millis_t MarlinGame::next_frame;

MarlinGameData marlin_game_data;

bool MarlinGame::game_frame() {
  static int8_t slew;
  if (ui.first_page) slew = 2;
  ui.refresh(LCDVIEW_CALL_NO_REDRAW); // Refresh as often as possible
  return (game_state && slew-- > 0);
}

void MarlinGame::draw_game_over() {
  constexpr int8_t gowide = (MENU_FONT_WIDTH) * 9,
                   gohigh = MENU_FONT_ASCENT - 3,
                       lx = (LCD_PIXEL_WIDTH - gowide) / 2,
                       ly = (LCD_PIXEL_HEIGHT + gohigh) / 2;
  if (PAGE_CONTAINS(ly - gohigh - 1, ly + 1)) {
    u8g.setColorIndex(0);
    u8g.drawBox(lx - 1, ly - gohigh - 1, gowide + 2, gohigh + 2);
    u8g.setColorIndex(1);
    if (ui.get_blink()) lcd_put_u8str(lx, ly, F("GAME OVER"));
  }
}

void MarlinGame::init_game(const uint8_t init_state, const screenFunc_t screen) {
  score = 0;
  game_state = init_state;
  ui.goto_screen(screen);
  ui.defer_status_screen();
}

void MarlinGame::exit_game() {
  ui.goto_previous_screen_no_defer();
}

#endif // HAS_GAMES

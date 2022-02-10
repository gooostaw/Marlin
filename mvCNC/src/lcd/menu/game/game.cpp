/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_GAMES

#include "game.h"

int mvCNCGame::score;
uint8_t mvCNCGame::game_state;
millis_t mvCNCGame::next_frame;

mvCNCGameData mvcnc_game_data;

bool mvCNCGame::game_frame() {
  static int8_t slew;
  if (ui.first_page) slew = 2;
  ui.refresh(LCDVIEW_CALL_NO_REDRAW); // Refresh as often as possible
  return (game_state && slew-- > 0);
}

void mvCNCGame::draw_game_over() {
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

void mvCNCGame::init_game(const uint8_t init_state, const screenFunc_t screen) {
  score = 0;
  game_state = init_state;
  ui.goto_screen(screen);
  ui.defer_status_screen();
}

void mvCNCGame::exit_game() {
  ui.goto_previous_screen_no_defer();
}

#endif // HAS_GAMES

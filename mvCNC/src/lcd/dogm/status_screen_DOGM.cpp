/**
 * Modern Vintage CNC Firmware
 */

//
// status_screen_DOGM.cpp
// Standard Status Screen for Graphical Display
//

#include "../../inc/mvCNCConfigPre.h"

#if HAS_MVCNCUI_U8GLIB && DISABLED(LIGHTWEIGHT_UI)

  #include "dogm_Statusscreen.h"
  #include "mvcncui_DOGM.h"
  #include "../mvcncui.h"
  #include "../lcdprint.h"
  #include "../../libs/numtostr.h"

  #include "../../module/motion.h"
  #include "../../module/pwm_temp_io.h"

  #include "../../gcode/parser.h"  // for units (and volumetric)

  #if ENABLED(LCD_SHOW_E_TOTAL)
    #include "../../mvCNCCore.h"  // for jobIsActive()
  #endif

  #if ENABLED(FILAMENT_LCD_DISPLAY)
    #include "../../feature/filwidth.h"
    #include "../../module/planner.h"
  #endif

  #if HAS_LEVELING
    #include "../../module/planner.h"
  #endif

  #if HAS_CUTTER
    #include "../../feature/spindle_laser.h"
  #endif

  #if EITHER(HAS_COOLER, LASER_COOLANT_FLOW_METER)
    #include "../../feature/cooler.h"
  #endif

  #if DO_DRAW_AMMETER
    #include "../../feature/ammeter.h"
  #endif

  #if HAS_POWER_MONITOR
    #include "../../feature/power_monitor.h"
  #endif

  #if ENABLED(SDSUPPORT)
    #include "../../sd/cardreader.h"
  #endif

  #if HAS_PRINT_PROGRESS
    #include "../../module/jobcounter.h"
  #endif

  #if HAS_DUAL_MIXING
    #include "../../feature/mixing.h"
  #endif

  #define X_LABEL_POS 3
  #define X_VALUE_POS 11
  #define XYZ_SPACING 37

  #define X_LABEL_POS_IN (X_LABEL_POS - 2)
  #define X_VALUE_POS_IN (X_VALUE_POS - 5)
  #define XYZ_SPACING_IN (XYZ_SPACING + 9)

  #define XYZ_BASELINE    (30 + INFO_FONT_ASCENT)
  #define EXTRAS_BASELINE (40 + INFO_FONT_ASCENT)
  #define STATUS_BASELINE (LCD_PIXEL_HEIGHT - INFO_FONT_DESCENT)

  #if ANIM_HBCC
enum HeatBits : uint8_t {
  DRAWBIT_HOTEND,
  DRAWBIT_BED = HOTENDS,
  DRAWBIT_CHAMBER,
  DRAWBIT_CUTTER
};
IF<(DRAWBIT_CUTTER > 7), uint16_t, uint8_t>::type draw_bits;
  #endif

  #if ANIM_HOTEND
    #define HOTEND_ALT(N) TEST(draw_bits, DRAWBIT_HOTEND + N)
  #else
    #define HOTEND_ALT(N) false
  #endif
  #if ANIM_BED
    #define BED_ALT() TEST(draw_bits, DRAWBIT_BED)
  #else
    #define BED_ALT() false
  #endif
  #if ANIM_CHAMBER
    #define CHAMBER_ALT() TEST(draw_bits, DRAWBIT_CHAMBER)
  #else
    #define CHAMBER_ALT() false
  #endif
  #if ANIM_CUTTER
    #define CUTTER_ALT(N) TEST(draw_bits, DRAWBIT_CUTTER)
  #else
    #define CUTTER_ALT() false
  #endif

  #if DO_DRAW_HOTENDS
    #define MAX_HOTEND_DRAW _MIN(HOTENDS, ((LCD_PIXEL_WIDTH - (STATUS_LOGO_BYTEWIDTH + STATUS_FAN_BYTEWIDTH) * 8) / (STATUS_HEATERS_XSPACE)))
  #endif

  #if EITHER(DO_DRAW_BED, DO_DRAW_HOTENDS)
    #define STATUS_HEATERS_BOT (STATUS_HEATERS_Y + STATUS_HEATERS_HEIGHT - 1)
  #endif

  #if HAS_POWER_MONITOR

void display_power_monitor(const uint8_t x, const uint8_t y) {
  lcd_moveto(x, y);

    #if HAS_POWER_MONITOR_WATTS
  const bool wflag = power_monitor.power_display_enabled();
    #endif
    #if ENABLED(POWER_MONITOR_CURRENT)
  const bool iflag = power_monitor.current_display_enabled();
    #endif
    #if ENABLED(POWER_MONITOR_VOLTAGE)
  const bool vflag = power_monitor.voltage_display_enabled();
    #endif

    #if HAS_POWER_MONITOR_WATTS
  // Cycle between current, voltage, and power
  if (ELAPSED(millis(), power_monitor.display_item_ms)) {
    power_monitor.display_item_ms = millis() + 1000UL;
    ++power_monitor.display_item;
  }
    #elif ENABLED(POWER_MONITOR_CURRENT)
  power_monitor.display_item = 0;
    #elif ENABLED(POWER_MONITOR_VOLTAGE)
  power_monitor.display_item = 1;
    #endif

  // ensure we have the right one selected for display
  for (uint8_t i = 0; i < 3; i++) {
    #if ENABLED(POWER_MONITOR_CURRENT)
    if (power_monitor.display_item == 0 && !iflag) ++power_monitor.display_item;
    #endif
    #if ENABLED(POWER_MONITOR_VOLTAGE)
    if (power_monitor.display_item == 1 && !vflag) ++power_monitor.display_item;
    #endif
    #if HAS_POWER_MONITOR_WATTS
    if (power_monitor.display_item == 2 && !wflag) ++power_monitor.display_item;
    #endif
    if (power_monitor.display_item >= 3) power_monitor.display_item = 0;
  }

  switch (power_monitor.display_item) {
    #if ENABLED(POWER_MONITOR_CURRENT)  // Current
    case 0:
      if (iflag) power_monitor.draw_current();
      break;
    #endif
    #if ENABLED(POWER_MONITOR_VOLTAGE)  // Voltage
    case 1:
      if (vflag) power_monitor.draw_voltage();
      break;
    #endif
    #if HAS_POWER_MONITOR_WATTS  // Power
    case 2:
      if (wflag) power_monitor.draw_power();
      break;
    #endif
    default:
      break;
  }
}
  #endif

  #define PROGRESS_BAR_X     54
  #define PROGRESS_BAR_Y     (EXTRAS_BASELINE + 1)
  #define PROGRESS_BAR_WIDTH (LCD_PIXEL_WIDTH - PROGRESS_BAR_X)

FORCE_INLINE void _draw_centered_temp(const celsius_t temp, const uint8_t tx, const uint8_t ty) {
  if (temp < 0)
    lcd_put_u8str(tx - 3 * (INFO_FONT_WIDTH) / 2 + 1, ty, F("err"));
  else {
    const char *str   = i16tostr3rj(temp);
    const uint8_t len = str[0] != ' ' ? 3 : str[1] != ' ' ? 2
                                                          : 1;
    lcd_put_u8str(tx - len * (INFO_FONT_WIDTH) / 2 + 1, ty, &str[3 - len]);
    lcd_put_wchar(LCD_STR_DEGREE[0]);
  }
}

  #if DO_DRAW_FLOWMETER
FORCE_INLINE void _draw_centered_flowrate(const float flow, const uint8_t tx, const uint8_t ty) {
  const char *str   = ftostr11ns(flow);
  const uint8_t len = str[0] != ' ' ? 3 : str[1] != ' ' ? 2
                                                        : 1;
  lcd_put_u8str(tx - len * (INFO_FONT_WIDTH) / 2 + 1, ty, &str[3 - len]);
  lcd_put_u8str("L");
}
  #endif

  #if DO_DRAW_AMMETER
FORCE_INLINE void _draw_centered_current(const float current, const uint8_t tx, const uint8_t ty) {
  const char *str   = ftostr31ns(current);
  const uint8_t len = str[0] != ' ' ? 3 : str[1] != ' ' ? 2
                                                        : 1;
  lcd_put_u8str(tx - len * (INFO_FONT_WIDTH) / 2 + 1, ty, &str[3 - len]);
}
  #endif

  #if DO_DRAW_COOLER
FORCE_INLINE void _draw_cooler_status() {
  if (PAGE_CONTAINS(28 - INFO_FONT_ASCENT, 28 - 1))
    _draw_centered_temp(fanManager.wholeDegCooler(), STATUS_COOLER_TEXT_X, 28);
}
  #endif

  #if DO_DRAW_FLOWMETER
FORCE_INLINE void _draw_flowmeter_status() {
  if (PAGE_CONTAINS(28 - INFO_FONT_ASCENT, 28 - 1))
    _draw_centered_flowrate(cooler.flowrate, STATUS_FLOWMETER_TEXT_X, 28);
}
  #endif

  #if DO_DRAW_AMMETER
FORCE_INLINE void _draw_ammeter_status() {
  if (PAGE_CONTAINS(28 - INFO_FONT_ASCENT, 28 - 1))
    _draw_centered_current(ammeter.read(), STATUS_AMMETER_TEXT_X, 28);
}
  #endif

// Work axis
// Before homing, blink '123' <-> '???'.
// Homed but unknown... '123' <-> '   '.
// Homed and known, display constantly.
//
FORCE_INLINE void _draw_axis_value(const AxisEnum axis, const char *value, const bool blink) {
  const bool is_inch = parser.using_inch_units();
  const AxisEnum a   = axis;
  const uint8_t offs = a * (is_inch ? XYZ_SPACING_IN : XYZ_SPACING);
  lcd_put_wchar((is_inch ? X_LABEL_POS_IN : X_LABEL_POS) + offs, XYZ_BASELINE, axis_codes[axis]);
  lcd_moveto((is_inch ? X_VALUE_POS_IN : X_VALUE_POS) + offs, XYZ_BASELINE);

  // if (blink)
  //   lcd_put_u8str(value);
  // else if (axis_should_home(axis))
  //   while (const char c = *value++) lcd_put_wchar(c <= '.' ? c : '?');
  // else if (NONE(HOME_AFTER_DEACTIVATE, DISABLE_REDUCED_ACCURACY_WARNING) && !axis_is_trusted(axis))
  //   lcd_put_u8str(axis == Z_AXIS ? F("       ") : F("    "));
  // else
  lcd_put_u8str(value);
}

// Machine axis
// Before homing, blink '123' <-> '???'.
// Homed but unknown... '123' <-> '   '.
// Homed and known, display constantly.
//
FORCE_INLINE void _draw_maxis_value(const AxisEnum axis, const char *value, const bool blink) {
  const bool is_inch = parser.using_inch_units();
  const AxisEnum a   = axis;
  const uint8_t offs = a * (is_inch ? XYZ_SPACING_IN : XYZ_SPACING);
  lcd_put_wchar((is_inch ? X_LABEL_POS_IN : X_LABEL_POS) + offs, XYZ_BASELINE - 10, axis_codes[axis]);
  lcd_moveto((is_inch ? X_VALUE_POS_IN : X_VALUE_POS) + offs, XYZ_BASELINE - 10);

  // if (blink)
  //   lcd_put_u8str(value);
  // else if (axis_should_home(axis))
  //   while (const char c = *value++) lcd_put_wchar(c <= '.' ? c : '?');
  // else if (NONE(HOME_AFTER_DEACTIVATE, DISABLE_REDUCED_ACCURACY_WARNING) && !axis_is_trusted(axis))
  //   lcd_put_u8str(axis == Z_AXIS ? F("       ") : F("    "));
  // else
  lcd_put_u8str(value);
}

/**
 * Draw the Status Screen for a 128x64 DOGM (U8glib) display.
 *
 * Called as needed to update the current display stripe.
 * Use the PAGE_CONTAINS macros to avoid pointless draw calls.
 */
void mvCNCUI::draw_status_screen() {
  constexpr int xystorage = TERN(INCH_MODE_SUPPORT, 8, 5);
  static char xstring[xystorage], ystring[xystorage], zstring[8];
  static char mxstring[xystorage], mystring[xystorage], mzstring[8];

  #if HAS_PRINT_PROGRESS
    #define _SD_INFO_X(len) (LCD_PIXEL_WIDTH - (len) * (MENU_FONT_WIDTH))

  static char progress_string[5];
  static uint8_t lastElapsed = 0xFF, lastProgress = 0xFF;
  static u8g_uint_t elapsed_x_pos = 0;
  static char elapsed_string[16];
    #if ENABLED(SHOW_REMAINING_TIME)
  static u8g_uint_t estimation_x_pos = 0;
  static char estimation_string[10];
    #endif
  #endif

  // At the first page, generate new display values
  if (first_page) {
    const xyz_pos_t lpos = current_position.asLogical();
    const xyz_pos_t mpos = current_position.asNative();
    const bool is_inch   = parser.using_inch_units();
    strcpy(zstring, is_inch ? ftostr42_52(LINEAR_UNIT(lpos.z)) : ftostr52sp(lpos.z));
    strcpy(xstring, is_inch ? ftostr53_63(LINEAR_UNIT(lpos.x)) : ftostr4sign(lpos.x));
    strcpy(ystring, is_inch ? ftostr53_63(LINEAR_UNIT(lpos.y)) : ftostr4sign(lpos.y));
    strcpy(mzstring, is_inch ? ftostr42_52(LINEAR_UNIT(mpos.z)) : ftostr52sp(lpos.z));
    strcpy(mxstring, is_inch ? ftostr53_63(LINEAR_UNIT(mpos.x)) : ftostr4sign(mpos.x));
    strcpy(mystring, is_inch ? ftostr53_63(LINEAR_UNIT(mpos.y)) : ftostr4sign(mpos.y));

  // Progress / elapsed / estimation updates and string formatting to avoid float math on each LCD draw
  #if HAS_PRINT_PROGRESS
    const progress_t progress = get_progress_percent();
    duration_t elapsed        = JobTimer.duration();
    const uint8_t p = progress & 0xFF, ev = elapsed.value & 0xFF;
    if (p != lastProgress) {
      lastProgress = p;

    #if ENABLED(SHOW_SD_PERCENT)
      if (progress == 0) {
        progress_string[0] = '\0';
      #if ENABLED(SHOW_REMAINING_TIME)
        estimation_string[0] = '\0';
        estimation_x_pos     = _SD_INFO_X(0);
      #endif
      } else
        strcpy(progress_string, ui8tostr3rj(progress / (PROGRESS_SCALE)));

    #endif
    }

    constexpr bool can_show_days = DISABLED(SHOW_SD_PERCENT) || ENABLED(ROTATE_PROGRESS_DISPLAY);
    if (ev != lastElapsed) {
      lastElapsed       = ev;
      const uint8_t len = elapsed.toDigital(elapsed_string, can_show_days && elapsed.value >= 60 * 60 * 24L);
      elapsed_x_pos     = _SD_INFO_X(len);

    #if ENABLED(SHOW_REMAINING_TIME)
      if (!(ev & 0x3)) {
        uint32_t timeval = (0
      #if BOTH(LCD_SET_PROGRESS_MANUALLY, USE_M73_REMAINING_TIME)
                            + get_remaining_time()
      #endif
        );
        if (!timeval && progress > 0) timeval = elapsed.value * (100 * (PROGRESS_SCALE)-progress) / progress;
        if (!timeval) {
          estimation_string[0] = '\0';
          estimation_x_pos     = _SD_INFO_X(0);
        } else {
          duration_t estimation = timeval;
          const uint8_t len     = estimation.toDigital(estimation_string, can_show_days && estimation.value >= 60 * 60 * 24L);
          estimation_x_pos      = _SD_INFO_X(len + !BOTH(SHOW_SD_PERCENT, ROTATE_PROGRESS_DISPLAY));
        }
      }
    #endif
    }
  #endif
  }

  const bool blink = get_blink();

  // Status Menu Font
  set_font(FONT_STATUSMENU);

  #if DO_DRAW_CUTTER
    #if ANIM_CUTTER
      #define CUTTER_BITMAP(S) ((S) ? status_cutter_on_bmp : status_cutter_bmp)
    #else
      #define CUTTER_BITMAP(S) status_cutter_bmp
    #endif
  const uint8_t cuttery = STATUS_CUTTER_Y(CUTTER_ALT()),
                cutterh = STATUS_CUTTER_HEIGHT(CUTTER_ALT());
  if (PAGE_CONTAINS(cuttery, cuttery + cutterh - 1))
    u8g.drawBitmapP(STATUS_CUTTER_X, cuttery, STATUS_CUTTER_BYTEWIDTH, cutterh, CUTTER_BITMAP(CUTTER_ALT()));
  #endif

  #if DO_DRAW_FAN
    #if STATUS_FAN_FRAMES > 2
  static bool old_blink;
  static uint8_t fan_frame;
  if (old_blink != blink) {
    old_blink = blink;
    if (!fanManager.fan_speed[0] || ++fan_frame >= STATUS_FAN_FRAMES) fan_frame = 0;
  }
    #endif
  if (PAGE_CONTAINS(STATUS_FAN_Y, STATUS_FAN_Y + STATUS_FAN_HEIGHT - 1))
    u8g.drawBitmapP(STATUS_FAN_X, STATUS_FAN_Y, STATUS_FAN_BYTEWIDTH, STATUS_FAN_HEIGHT,
    #if STATUS_FAN_FRAMES > 2
                    fan_frame == 1 ? status_fan1_bmp : fan_frame == 2 ? status_fan2_bmp
                                                   :
      #if STATUS_FAN_FRAMES > 3
                                                   fan_frame == 3 ? status_fan3_bmp
                                                                  :
      #endif
    #elif STATUS_FAN_FRAMES > 1
                    blink && fanManager.fan_speed[0] ? status_fan1_bmp :
    #endif
                                                                  status_fan0_bmp);
  #endif

  //
  // Temperature Graphics and Info
  //
  if (PAGE_UNDER(6 + 1 + 12 + 1 + 6 + 1)) {
  // Laser / Spindle
  #if DO_DRAW_CUTTER
    if (cutter.isReady && PAGE_CONTAINS(STATUS_CUTTER_TEXT_Y - INFO_FONT_ASCENT, STATUS_CUTTER_TEXT_Y - 1)) {
    #if CUTTER_UNIT_IS(PERCENT)
      lcd_put_u8str(STATUS_CUTTER_TEXT_X, STATUS_CUTTER_TEXT_Y, cutter_power2str(cutter.unitPower));
    #elif CUTTER_UNIT_IS(RPM)
      lcd_put_u8str(STATUS_CUTTER_TEXT_X - 2, STATUS_CUTTER_TEXT_Y, ftostr51rj(float(cutter.unitPower) / 1000));
      lcd_put_wchar('k');
    #else
      lcd_put_u8str(STATUS_CUTTER_TEXT_X, STATUS_CUTTER_TEXT_Y, cutter_power2str(cutter.unitPower));
    #endif
    }
  #endif

  // Laser Cooler
  #if DO_DRAW_COOLER
    const uint8_t coolery = STATUS_COOLER_Y(status_cooler_bmp1),
                  coolerh = STATUS_COOLER_HEIGHT(status_cooler_bmp1);
    if (PAGE_CONTAINS(coolery, coolery + coolerh - 1))
      u8g.drawBitmapP(STATUS_COOLER_X, coolery, STATUS_COOLER_BYTEWIDTH, coolerh, blink && cooler.enabled ? status_cooler_bmp2 : status_cooler_bmp1);
  #endif

  // Laser Cooler Flow Meter
  #if DO_DRAW_FLOWMETER
    const uint8_t flowmetery = STATUS_FLOWMETER_Y(status_flowmeter_bmp1),
                  flowmeterh = STATUS_FLOWMETER_HEIGHT(status_flowmeter_bmp1);
    if (PAGE_CONTAINS(flowmetery, flowmetery + flowmeterh - 1))
      u8g.drawBitmapP(STATUS_FLOWMETER_X, flowmetery, STATUS_FLOWMETER_BYTEWIDTH, flowmeterh, blink && cooler.flowpulses ? status_flowmeter_bmp2 : status_flowmeter_bmp1);
  #endif

  // Laser Ammeter
  #if DO_DRAW_AMMETER
    const uint8_t ammetery = STATUS_AMMETER_Y(status_ammeter_bmp_mA),
                  ammeterh = STATUS_AMMETER_HEIGHT(status_ammeter_bmp_mA);
    if (PAGE_CONTAINS(ammetery, ammetery + ammeterh - 1))
      u8g.drawBitmapP(STATUS_AMMETER_X, ammetery, STATUS_AMMETER_BYTEWIDTH, ammeterh, (ammeter.current < 0.1f) ? status_ammeter_bmp_mA : status_ammeter_bmp_A);
  #endif

    // Cooler
    TERN_(DO_DRAW_COOLER, _draw_cooler_status());

    // Flowmeter
    TERN_(DO_DRAW_FLOWMETER, _draw_flowmeter_status());

    // Ammeter
    TERN_(DO_DRAW_AMMETER, _draw_ammeter_status());

  // Fan, if a bitmap was provided
  #if DO_DRAW_FAN
    if (PAGE_CONTAINS(STATUS_FAN_TEXT_Y - INFO_FONT_ASCENT, STATUS_FAN_TEXT_Y - 1)) {
      char c       = '%';
      uint16_t spd = fanManager.fan_speed[0];
      if (spd) {
    #if ENABLED(ADAPTIVE_FAN_SLOWING)
        if (!blink && fanManager.fan_speed_scaler[0] < 128) {
          spd = fanManager.scaledFanSpeed(0, spd);
          c   = '*';
        }
    #endif
        lcd_put_u8str(STATUS_FAN_TEXT_X, STATUS_FAN_TEXT_Y, i16tostr3rj(fanManager.pwmToPercent(spd)));
        lcd_put_wchar(c);
      }
    }
  #endif
  }

  #if ENABLED(SDSUPPORT)
  //
  // SD Card Symbol
  //
  if (card.isFileOpen() && PAGE_CONTAINS(42, 51)) {
    // Upper box
    u8g.drawBox(42, 42, 8, 7);  // 42-48 (or 41-47)
    // Right edge
    u8g.drawBox(50, 44, 2, 5);  // 44-48 (or 43-47)
    // Bottom hollow box
    u8g.drawFrame(42, 49, 10, 4);  // 49-52 (or 48-51)
    // Corner pixel
    u8g.drawPixel(50, 43);  // 43 (or 42)
  }
  #endif  // SDSUPPORT

  #if HAS_PRINT_PROGRESS
    //
    // SD Percent Complete
    //

    #if ENABLED(SHOW_SD_PERCENT)
  if (progress_string[0]) {
    lcd_put_u8str(55, EXTRAS_BASELINE, progress_string);  // Percent complete
    lcd_put_wchar('%');
  }
    #endif

    //
    // Elapsed Time
    //

    #if ENABLED(SHOW_REMAINING_TIME)
  if (blink && estimation_string[0]) {
    lcd_put_wchar(estimation_x_pos, EXTRAS_BASELINE, 'R');
    lcd_put_u8str(estimation_string);
  } else
    #endif
    lcd_put_u8str(elapsed_x_pos, EXTRAS_BASELINE, elapsed_string);
  #endif  // HAS_PRINT_PROGRESS

    //
    // XYZ Coordinates
    //

  #if EITHER(XYZ_NO_FRAME, XYZ_HOLLOW_FRAME)
    #define XYZ_FRAME_TOP    29
    #define XYZ_FRAME_HEIGHT INFO_FONT_ASCENT + 3
  #else
    #define XYZ_FRAME_TOP    30
    #define XYZ_FRAME_HEIGHT INFO_FONT_ASCENT + 1
  #endif

  if (PAGE_CONTAINS(XYZ_FRAME_TOP, XYZ_FRAME_TOP + XYZ_FRAME_HEIGHT - 1)) {
  #if DISABLED(XYZ_NO_FRAME)
    #if ENABLED(XYZ_HOLLOW_FRAME)
    u8g.drawFrame(0, XYZ_FRAME_TOP, LCD_PIXEL_WIDTH, XYZ_FRAME_HEIGHT);  // 8: 29-40  7: 29-39
    #else
    u8g.drawBox(0, XYZ_FRAME_TOP, LCD_PIXEL_WIDTH, XYZ_FRAME_HEIGHT);  // 8: 30-39  7: 30-37
    #endif
  #endif

    if (PAGE_CONTAINS(XYZ_BASELINE - (INFO_FONT_ASCENT - 1), XYZ_BASELINE)) {
  #if NONE(XYZ_NO_FRAME, XYZ_HOLLOW_FRAME)
      u8g.setColorIndex(0);  // white on black
  #endif

      _draw_axis_value(X_AXIS, xstring, blink);
      _draw_axis_value(Y_AXIS, ystring, blink);
      _draw_axis_value(Z_AXIS, zstring, blink);
      _draw_maxis_value(X_AXIS, mxstring, blink);
      _draw_maxis_value(Y_AXIS, mystring, blink);
      _draw_maxis_value(Z_AXIS, mzstring, blink);

  #if NONE(XYZ_NO_FRAME, XYZ_HOLLOW_FRAME)
      u8g.setColorIndex(1);  // black on white
  #endif
    }
  }

  //
  // Feedrate
  //
  #define EXTRAS_2_BASELINE (EXTRAS_BASELINE + 3)

  if (PAGE_CONTAINS(EXTRAS_2_BASELINE - INFO_FONT_ASCENT, EXTRAS_2_BASELINE - 1)) {
    set_font(FONT_MENU);
    lcd_put_wchar(3, EXTRAS_2_BASELINE, LCD_STR_FEEDRATE[0]);

    set_font(FONT_STATUSMENU);
    lcd_put_u8str(12, EXTRAS_2_BASELINE, i16tostr3rj(feedrate_percentage));
    lcd_put_wchar('%');

  //
  // Filament sensor display if SD is disabled
  //
  #if ENABLED(FILAMENT_LCD_DISPLAY) && DISABLED(SDSUPPORT)
    lcd_put_u8str(56, EXTRAS_2_BASELINE, wstring);
    lcd_put_u8str(102, EXTRAS_2_BASELINE, mstring);
    lcd_put_wchar('%');
    set_font(FONT_MENU);
    lcd_put_wchar(47, EXTRAS_2_BASELINE, LCD_STR_FILAM_DIA[0]);  // lcd_put_u8str(F(LCD_STR_FILAM_DIA));
    lcd_put_wchar(93, EXTRAS_2_BASELINE, LCD_STR_FILAM_MUL[0]);
  #endif
  }

  //
  // Status line
  //
  if (PAGE_CONTAINS(STATUS_BASELINE - INFO_FONT_ASCENT, STATUS_BASELINE + INFO_FONT_DESCENT)) {
    lcd_moveto(0, STATUS_BASELINE);

  #if BOTH(FILAMENT_LCD_DISPLAY, SDSUPPORT)
    // Alternate Status message and Filament display
    if (ELAPSED(millis(), next_filament_display)) {
      lcd_put_u8str(F(LCD_STR_FILAM_DIA));
      lcd_put_wchar(':');
      lcd_put_u8str(wstring);
      lcd_put_u8str(F("  " LCD_STR_FILAM_MUL));
      lcd_put_wchar(':');
      lcd_put_u8str(mstring);
      lcd_put_wchar('%');
      return;
    }
  #endif

    draw_status_message(blink);
  }
}

/**
 * Draw the Status Message area
 */
void mvCNCUI::draw_status_message(const bool blink) {
  // Get the UTF8 character count of the string
  uint8_t lcd_width = LCD_WIDTH, pixel_width = LCD_PIXEL_WIDTH,
          slen = utf8_strlen(status_message);

  #if HAS_POWER_MONITOR
  if (power_monitor.display_enabled()) {
    // make room at the end of the status line for the power monitor reading
    lcd_width -= 6;
    pixel_width -= (MENU_FONT_WIDTH)*6;
  }
  #endif

  #if ENABLED(STATUS_MESSAGE_SCROLLING)

  static bool last_blink = false;

  if (slen <= lcd_width) {
    // The string fits within the line. Print with no scrolling
    lcd_put_u8str(status_message);
    while (slen < lcd_width) {
      lcd_put_wchar(' ');
      ++slen;
    }
  } else {
    // String is longer than the available space
    if (blink != last_blink) {
      last_blink = blink;
      advance_status_scroll();
    }

    // Get a pointer to the next valid UTF8 character
    // and the string remaining length
    uint8_t rlen;
    const char *stat = status_and_len(rlen);
    lcd_put_u8str_max(stat, pixel_width);

    // If the remaining string doesn't completely fill the screen
    if (rlen < lcd_width) {
      uint8_t chars = lcd_width - rlen;  // Amount of space left in characters
      lcd_put_wchar(' ');                // Always at 1+ spaces left, draw a space
      if (--chars) {                     // Draw a second space if there's room
        lcd_put_wchar(' ');
        if (--chars) {  // Draw a third space if there's room
          lcd_put_wchar(' ');
          if (--chars) {  // Print a second copy of the message
            lcd_put_u8str_max(status_message, pixel_width - (rlen + 2) * (MENU_FONT_WIDTH));
            lcd_put_wchar(' ');
          }
        }
      }
    }
  }

  #else  // !STATUS_MESSAGE_SCROLLING

  UNUSED(blink);

  // Just print the string to the LCD
  lcd_put_u8str_max(status_message, pixel_width);

  // Fill the rest with spaces
  for (; slen < lcd_width; ++slen) lcd_put_wchar(' ');

  #endif  // !STATUS_MESSAGE_SCROLLING

  #if HAS_POWER_MONITOR
  display_power_monitor(pixel_width + MENU_FONT_WIDTH, STATUS_BASELINE);
  #endif
}

#endif  // HAS_MVCNCUI_U8GLIB && !LIGHTWEIGHT_UI

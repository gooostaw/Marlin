/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"

/**
 * M111: Set the debug level
 */
void GcodeSuite::M111() {
  if (parser.seenval('S')) wrcnc_debug_flags = parser.value_byte();

  static PGMSTR(str_debug_1, STR_DEBUG_ECHO);
  static PGMSTR(str_debug_2, STR_DEBUG_INFO);
  static PGMSTR(str_debug_4, STR_DEBUG_ERRORS);
  static PGMSTR(str_debug_8, STR_DEBUG_DRYRUN);
  static PGMSTR(str_debug_16, STR_DEBUG_COMMUNICATION);
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    static PGMSTR(str_debug_detail, STR_DEBUG_DETAIL);
  #endif

  static PGM_P const debug_strings[] PROGMEM = {
    str_debug_1, str_debug_2, str_debug_4, str_debug_8, str_debug_16,
    TERN_(DEBUG_LEVELING_FEATURE, str_debug_detail)
  };

  SERIAL_ECHO_START();
  SERIAL_ECHOPGM(STR_DEBUG_PREFIX);
  if (wrcnc_debug_flags) {
    uint8_t comma = 0;
    LOOP_L_N(i, COUNT(debug_strings)) {
      if (TEST(wrcnc_debug_flags, i)) {
        if (comma++) SERIAL_CHAR(',');
        SERIAL_ECHOPGM_P((char*)pgm_read_ptr(&debug_strings[i]));
      }
    }
  }
  else {
    SERIAL_ECHOPGM(STR_DEBUG_OFF);
    #if !defined(__AVR__) || !defined(USBCON)
      #if ENABLED(SERIAL_STATS_RX_BUFFER_OVERRUNS)
        SERIAL_ECHOPGM("\nBuffer Overruns: ", MYSERIAL1.buffer_overruns());
      #endif

      #if ENABLED(SERIAL_STATS_RX_FRAMING_ERRORS)
        SERIAL_ECHOPGM("\nFraming Errors: ", MYSERIAL1.framing_errors());
      #endif

      #if ENABLED(SERIAL_STATS_DROPPED_RX)
        SERIAL_ECHOPGM("\nDropped bytes: ", MYSERIAL1.dropped());
      #endif

      #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
        SERIAL_ECHOPGM("\nMax RX Queue Size: ", MYSERIAL1.rxMaxEnqueued());
      #endif
    #endif // !__AVR__ || !USBCON
  }
  SERIAL_EOL();
}

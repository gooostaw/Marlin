/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/*******************************************************
 * multi_language.h                                    *
 * By Marcio Teixeira 2019 for Aleph Objects           *
 *******************************************************/

#include "../inc/WRCNCConfigPre.h"

typedef const char Language_Str[];
#define LSTR PROGMEM Language_Str

#ifdef LCD_LANGUAGE_5
  #define NUM_LANGUAGES 5
#elif defined(LCD_LANGUAGE_4)
  #define NUM_LANGUAGES 4
#elif defined(LCD_LANGUAGE_3)
  #define NUM_LANGUAGES 3
#elif defined(LCD_LANGUAGE_2)
  #define NUM_LANGUAGES 2
#else
  #define NUM_LANGUAGES 1
#endif

// Set unused languages equal to each other so the
// compiler can optimize away the conditionals.
#ifndef LCD_LANGUAGE_2
  #define LCD_LANGUAGE_2 LCD_LANGUAGE
#endif
#ifndef LCD_LANGUAGE_3
  #define LCD_LANGUAGE_3 LCD_LANGUAGE_2
#endif
#ifndef LCD_LANGUAGE_4
  #define LCD_LANGUAGE_4 LCD_LANGUAGE_3
#endif
#ifndef LCD_LANGUAGE_5
  #define LCD_LANGUAGE_5 LCD_LANGUAGE_4
#endif

#define _GET_LANG(LANG) Language_##LANG
#define GET_LANG(LANG) _GET_LANG(LANG)

#if NUM_LANGUAGES > 1
  #define HAS_MULTI_LANGUAGE 1
  #define GET_TEXT(MSG) ( \
    ui.language == 4 ? GET_LANG(LCD_LANGUAGE_5)::MSG : \
    ui.language == 3 ? GET_LANG(LCD_LANGUAGE_4)::MSG : \
    ui.language == 2 ? GET_LANG(LCD_LANGUAGE_3)::MSG : \
    ui.language == 1 ? GET_LANG(LCD_LANGUAGE_2)::MSG : \
                       GET_LANG(LCD_LANGUAGE  )::MSG   )
  #define MAX_LANG_CHARSIZE _MAX(GET_LANG(LCD_LANGUAGE  )::CHARSIZE, \
                                 GET_LANG(LCD_LANGUAGE_2)::CHARSIZE, \
                                 GET_LANG(LCD_LANGUAGE_3)::CHARSIZE, \
                                 GET_LANG(LCD_LANGUAGE_4)::CHARSIZE, \
                                 GET_LANG(LCD_LANGUAGE_5)::CHARSIZE  )
#else
  #define GET_TEXT(MSG) GET_LANG(LCD_LANGUAGE)::MSG
  #define MAX_LANG_CHARSIZE LANG_CHARSIZE
#endif
#define GET_TEXT_F(MSG) FPSTR(GET_TEXT(MSG))

#define GET_LANGUAGE_NAME(INDEX) GET_LANG(LCD_LANGUAGE_##INDEX)::LANGUAGE
#define LANG_CHARSIZE GET_TEXT(CHARSIZE)
#define USE_WIDE_GLYPH (LANG_CHARSIZE > 2)

#define MSG_1_LINE(A)     A "\0"   "\0"
#define MSG_2_LINE(A,B)   A "\0" B "\0"
#define MSG_3_LINE(A,B,C) A "\0" B "\0" C

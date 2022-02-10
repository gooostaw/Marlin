/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif


void lv_draw_wifi_tips();
void lv_clear_wifi_tips();

typedef enum {
  TIPS_TYPE_JOINING,
  TIPS_TYPE_TAILED_JOIN,
  TIPS_TYPE_WIFI_CONECTED
} TIPS_TYPE;
extern TIPS_TYPE wifi_tips_type;

typedef struct {
  unsigned char timer;
  unsigned int timer_count;
} TIPS_DISP;
extern TIPS_DISP tips_disp;

#define TIPS_TIMER_START 1
#define TIPS_TIMER_STOP 0

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

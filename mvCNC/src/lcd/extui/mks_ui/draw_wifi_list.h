/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

void lv_draw_wifi_list();
void lv_clear_wifi_list();
void disp_wifi_list();
void cutWifiName(char *name, int len, char *outStr);
void wifi_scan_handle();

#define NUMBER_OF_PAGE 5

#define WIFI_TOTAL_NUMBER 20
#define WIFI_NAME_BUFFER_SIZE 33

typedef struct {
  int8_t getNameNum;
  int8_t nameIndex;
  int8_t currentWifipage;
  int8_t getPage;
  int8_t RSSI[WIFI_TOTAL_NUMBER];
  uint8_t wifiName[WIFI_TOTAL_NUMBER][WIFI_NAME_BUFFER_SIZE];
  uint8_t wifiConnectedName[WIFI_NAME_BUFFER_SIZE];
} WIFI_LIST;
extern WIFI_LIST wifi_list;

typedef struct list_menu_disp {
  const char *title;
  const char *file_pages;
} list_menu_def;
extern list_menu_def list_menu;

typedef struct keyboard_menu_disp {
  const char *title;
  const char *apply;
  const char *password;
  const char *letter;
  const char *digital;
  const char *symbol;
  const char *space;
} keyboard_menu_def;
extern keyboard_menu_def keyboard_menu;

typedef struct tips_menu_disp {
  const char *joining;
  const char *failedJoin;
  const char *wifiConected;
} tips_menu_def;
extern tips_menu_def tips_menu;

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

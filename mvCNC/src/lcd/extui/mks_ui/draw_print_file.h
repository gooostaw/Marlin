/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

typedef struct {
  int cur_page_first_offset;
  int cur_page_last_offset;
  int curPage;
} DIR_OFFSET;
extern DIR_OFFSET dir_offset[10];

#define FILE_NUM 6
#define SHORT_NAME_LEN 13
#define NAME_CUT_LEN 23

#define MAX_DIR_LEVEL  10

typedef struct {
  char file_name[FILE_NUM][SHORT_NAME_LEN * MAX_DIR_LEVEL + 1];
  char curDirPath[SHORT_NAME_LEN * MAX_DIR_LEVEL + 1];
  char long_name[FILE_NUM][SHORT_NAME_LEN * 2 + 1];
  bool IsFolder[FILE_NUM];
  char Sd_file_cnt;
  char sd_file_index;
  char Sd_file_offset;
} LIST_FILE;
extern LIST_FILE list_file;

void disp_gcode_icon(uint8_t file_num);
void lv_draw_print_file();
uint32_t lv_open_gcode_file(char *path);
void lv_gcode_file_read(uint8_t *data_buf);
void lv_close_gcode_file();
void cutFileName(char *path, int len, int bytePerLine, char *outStr);
int ascii2dec_test(char *ascii);
void lv_clear_print_file();
void lv_gcode_file_seek(uint32_t pos);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

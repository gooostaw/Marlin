/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * @file lcd/extui/mks_ui/tft_lvgl_configuration.h
 * @date 2020-02-21
 */

#ifdef __cplusplus
  extern "C" {
#endif

#include <lvgl.h>

//#define TFT_ROTATION TFT_ROTATE_180

extern uint8_t bmp_public_buf[14 * 1024];
extern uint8_t public_buf[513];

void tft_lvgl_init();
void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);
bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);
bool my_mousewheel_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

void LCD_Clear(uint16_t Color);
void tft_set_point(uint16_t x, uint16_t y, uint16_t point);
void LCD_setWindowArea(uint16_t StartX, uint16_t StartY, uint16_t width, uint16_t height);
void LCD_WriteRAM_Prepare();
void lcd_draw_logo();
void lv_encoder_pin_init();
void lv_update_encoder();

lv_fs_res_t spi_flash_open_cb(lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode);
lv_fs_res_t spi_flash_close_cb(lv_fs_drv_t * drv, void * file_p);
lv_fs_res_t spi_flash_read_cb(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
lv_fs_res_t spi_flash_seek_cb(lv_fs_drv_t * drv, void * file_p, uint32_t pos);
lv_fs_res_t spi_flash_tell_cb(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

lv_fs_res_t sd_open_cb(lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode);
lv_fs_res_t sd_close_cb(lv_fs_drv_t * drv, void * file_p);
lv_fs_res_t sd_read_cb(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
lv_fs_res_t sd_seek_cb(lv_fs_drv_t * drv, void * file_p, uint32_t pos);
lv_fs_res_t sd_tell_cb(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

void lv_fill_rect(lv_coord_t x1, lv_coord_t y1, lv_coord_t x2, lv_coord_t y2, lv_color_t bk_color);

bool get_lcd_dma_lock();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif

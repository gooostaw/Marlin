/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * LPC1768 LCD-specific defines
 */

// The following are optional depending on the platform.

// definitions of HAL specific com and device drivers.
uint8_t u8g_com_HAL_LPC1768_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);
uint8_t u8g_com_HAL_LPC1768_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);
uint8_t u8g_com_HAL_LPC1768_ST7920_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);
uint8_t u8g_com_HAL_LPC1768_ST7920_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);
uint8_t u8g_com_HAL_LPC1768_ssd_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);


// connect U8g com generic com names to the desired driver
#define U8G_COM_HW_SPI u8g_com_HAL_LPC1768_hw_spi_fn  // use LPC1768 specific hardware SPI routine
#define U8G_COM_SW_SPI u8g_com_HAL_LPC1768_sw_spi_fn  // use LPC1768 specific software SPI routine
#define U8G_COM_ST7920_HW_SPI u8g_com_HAL_LPC1768_ST7920_hw_spi_fn
#define U8G_COM_ST7920_SW_SPI u8g_com_HAL_LPC1768_ST7920_sw_spi_fn
#define U8G_COM_SSD_I2C u8g_com_HAL_LPC1768_ssd_hw_i2c_fn

// let these default for now
#define U8G_COM_PARALLEL u8g_com_null_fn
#define U8G_COM_T6963 u8g_com_null_fn
#define U8G_COM_FAST_PARALLEL u8g_com_null_fn
#define U8G_COM_UC_I2C u8g_com_null_fn

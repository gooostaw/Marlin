/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <stdint.h>

#include HAL_PATH(../HAL, mvCNCSPI.h)

#define W25X_WriteEnable        0x06
#define W25X_WriteDisable       0x04
#define W25X_ReadStatusReg      0x05
#define W25X_WriteStatusReg     0x01
#define W25X_ReadData           0x03
#define W25X_FastReadData       0x0B
#define W25X_FastReadDual       0x3B
#define W25X_PageProgram        0x02
#define W25X_BlockErase         0xD8
#define W25X_SectorErase        0x20
#define W25X_ChipErase          0xC7
#define W25X_PowerDown          0xB9
#define W25X_ReleasePowerDown   0xAB
#define W25X_DeviceID           0xAB
#define W25X_ManufactDeviceID   0x90
#define W25X_JedecDeviceID      0x9F

#define WIP_Flag                0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte              0xA5

#define SPI_FLASH_SectorSize         4096
#define SPI_FLASH_PageSize           256
#define SPI_FLASH_PerWritePageSize   256

class W25QXXFlash {
private:
  static mvCNCSPI mySPI;
public:
  void init(uint8_t spiRate);
  static uint8_t spi_flash_Rec();
  static uint8_t spi_flash_read_write_byte(uint8_t data);
  static void spi_flash_Read(uint8_t *buf, uint16_t nbyte);
  static void spi_flash_Send(uint8_t b);
  static void spi_flash_SendBlock(uint8_t token, const uint8_t *buf);
  static uint16_t W25QXX_ReadID(void);
  static void SPI_FLASH_WriteEnable();
  static void SPI_FLASH_WaitForWriteEnd();
  static void SPI_FLASH_SectorErase(uint32_t SectorAddr);
  static void SPI_FLASH_BlockErase(uint32_t BlockAddr);
  static void SPI_FLASH_BulkErase();
  static void SPI_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
  static void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
  static void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
};

extern W25QXXFlash W25QXX;

/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../inc/mvCNCConfig.h"

#include "SdInfo.h"
#include "disk_io_driver.h"

bool SDIO_Init();
bool SDIO_ReadBlock(uint32_t block, uint8_t *dst);
bool SDIO_WriteBlock(uint32_t block, const uint8_t *src);
bool SDIO_IsReady();
uint32_t SDIO_GetCardSize();

class DiskIODriver_SDIO : public DiskIODriver {
  public:
    bool init(const uint8_t sckRateID=0, const pin_t chipSelectPin=0) override { return SDIO_Init(); }

    bool readCSD(csd_t *csd)                              override { return false; }

    bool readStart(const uint32_t block)                  override { curBlock = block; return true; }
    bool readData(uint8_t *dst)                           override { return readBlock(curBlock++, dst); }
    bool readStop()                                       override { curBlock = -1; return true; }

    bool writeStart(const uint32_t block, const uint32_t) override { curBlock = block; return true; }
    bool writeData(const uint8_t *src)                    override { return writeBlock(curBlock++, src); }
    bool writeStop()                                      override { curBlock = -1; return true; }

    bool readBlock(uint32_t block, uint8_t *dst)          override { return SDIO_ReadBlock(block, dst); }
    bool writeBlock(uint32_t block, const uint8_t *src)   override { return SDIO_WriteBlock(block, src); }

    uint32_t cardSize()                                   override { return SDIO_GetCardSize(); }

    bool isReady()                                        override { return SDIO_IsReady(); }

    void idle()                                           override {}
  private:
    uint32_t curBlock;
};

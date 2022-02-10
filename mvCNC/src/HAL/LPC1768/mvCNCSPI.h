/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <SPI.h>

/**
 * mvCNC currently requires 3 SPI classes:
 *
 * SPIClass:
 *  This class is normally provided by frameworks and has a semi-default interface.
 *  This is needed because some libraries reference it globally.
 *
 * SPISettings:
 *  Container for SPI configs for SPIClass. As above, libraries may reference it globally.
 *
 * These two classes are often provided by frameworks so we cannot extend them to add
 * useful methods for mvCNC.
 *
 * mvCNCSPI:
 *  Provides the default SPIClass interface plus some mvCNC goodies such as a simplified
 *  interface for SPI DMA transfer.
 *
 */

using mvCNCSPI = SPIClass;

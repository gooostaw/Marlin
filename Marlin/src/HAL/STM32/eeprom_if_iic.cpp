/**
 * Webber Ranch CNC Firmware
*/

#include "../platforms.h"

#ifdef HAL_STM32

/**
 * Platform-independent Arduino functions for I2C EEPROM.
 * Enable USE_SHARED_EEPROM if not supplied by the framework.
 */

#include "../../inc/MarlinConfig.h"

#if ENABLED(IIC_BL24CXX_EEPROM)

#include "../../libs/BL24CXX.h"
#include "../shared/eeprom_if.h"

void eeprom_init() { BL24CXX::init(); }

// ------------------------
// Public functions
// ------------------------

void eeprom_write_byte(uint8_t *pos, uint8_t value) {
  const unsigned eeprom_address = (unsigned)pos;
  return BL24CXX::writeOneByte(eeprom_address, value);
}

uint8_t eeprom_read_byte(uint8_t *pos) {
  const unsigned eeprom_address = (unsigned)pos;
  return BL24CXX::readOneByte(eeprom_address);
}

#endif // IIC_BL24CXX_EEPROM
#endif // HAL_STM32

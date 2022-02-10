/**
 * Webber Ranch CNC Firmware
*/

/**
 * HAL_LPC1768/include/i2c_util.c
 */

#ifdef TARGET_LPC1768

#include "i2c_util.h"

#define U8G_I2C_OPT_FAST 16  // from u8g.h

#ifdef __cplusplus
  extern "C" {
#endif

void configure_i2c(const uint8_t clock_option) {
  /**
   * Init I2C pin connect
   */
  PINSEL_CFG_Type PinCfg;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Portnum = 0;
  #if I2C_MASTER_ID == 0
    PinCfg.Funcnum = 1;
    PinCfg.Pinnum = 27;     // SDA0 / D57  AUX-1 ... SCL0 / D58  AUX-1
  #elif I2C_MASTER_ID == 1
    PinCfg.Funcnum = 3;
    PinCfg.Pinnum = 0;      // SDA1 / D20 SCA ... SCL1 / D21 SCL
  #elif I2C_MASTER_ID == 2
    PinCfg.Funcnum = 2;
    PinCfg.Pinnum = 10;     // SDA2 / D38  X_ENABLE_PIN ... SCL2 / D55  X_DIR_PIN
  #endif
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum += 1;
  PINSEL_ConfigPin(&PinCfg);

  // Initialize I2C peripheral
  I2C_Init(I2CDEV_M, (clock_option & U8G_I2C_OPT_FAST) ? 400000: 100000);  // LCD data rates

  // Enable Master I2C operation
  I2C_Cmd(I2CDEV_M, I2C_MASTER_MODE, ENABLE);
}

#ifdef __cplusplus
  }
#endif

#endif // TARGET_LPC1768

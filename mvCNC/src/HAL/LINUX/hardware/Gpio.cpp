/**
 * Modern Vintage CNC Firmware
*/
#ifdef __PLAT_LINUX__

#include "Gpio.h"

pin_data Gpio::pin_map[Gpio::pin_count+1] = {};
IOLogger* Gpio::logger = nullptr;

#endif // __PLAT_LINUX__

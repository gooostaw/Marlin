/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfigPre.h"

#if ENABLED(BARICUDA)

#include "baricuda.h"

uint8_t baricuda_valve_pressure = 0,
        baricuda_e_to_p_pressure = 0;

#endif // BARICUDA

/**
 * Webber Ranch CNC Firmware
*/

#include "../../../inc/MarlinConfig.h"

#if ENABLED(BARICUDA)

#include "../../gcode.h"
#include "../../../feature/baricuda.h"

#if HAS_HEATER_1

  /**
   * M126: Heater 1 valve open
   */
  void GcodeSuite::M126() { baricuda_valve_pressure = parser.byteval('S', 255); }

  /**
   * M127: Heater 1 valve close
   */
  void GcodeSuite::M127() { baricuda_valve_pressure = 0; }

#endif // HAS_HEATER_1

#if HAS_HEATER_2

  /**
   * M128: Heater 2 valve open
   */
  void GcodeSuite::M128() { baricuda_e_to_p_pressure = parser.byteval('S', 255); }

  /**
   * M129: Heater 2 valve close
   */
  void GcodeSuite::M129() { baricuda_e_to_p_pressure = 0; }

#endif // HAS_HEATER_2

#endif // BARICUDA

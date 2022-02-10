/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_PRUSA_MMU2

#include "../../gcode.h"
#include "../../../feature/mmu/mmu2.h"

/**
 * M403: Set filament type for MMU2
 *
 * Valid filament type values:
 *
 *  0   Default
 *  1   Flexible
 *  2   PVA
 */
void GcodeSuite::M403() {
  int8_t index = parser.intval('E', -1),
         type = parser.intval('F', -1);

  if (WITHIN(index, 0, EXTRUDERS - 1) && WITHIN(type, 0, 2))
    mmu2.set_filament_type(index, type);
  else
    SERIAL_ECHO_MSG("M403 - bad arguments.");
}

#endif // HAS_PRUSA_MMU2

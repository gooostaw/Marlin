/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfig.h"

#if ENABLED(Z_PROBE_SLED)

#include "../gcode.h"
#include "../../module/probe.h"

/**
 * G31: Deploy the Z probe
 */
void GcodeSuite::G31() { probe.deploy(); }

/**
 * G32: Stow the Z probe
 */
void GcodeSuite::G32() { probe.stow(); }

#endif // Z_PROBE_SLED

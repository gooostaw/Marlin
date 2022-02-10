/**
 * Modern Vintage CNC Firmware
*/

#include "../gcode.h"
#include "../../module/endstops.h"

/**
 * M120: Enable endstops and set non-homing endstop state to "enabled"
 */
void GcodeSuite::M120() { endstops.enable_globally(true); }

/**
 * M121: Disable endstops and set non-homing endstop state to "disabled"
 */
void GcodeSuite::M121() { endstops.enable_globally(false); }

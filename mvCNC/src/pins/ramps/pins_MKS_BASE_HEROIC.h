/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * MKS BASE with Heroic HR4982 stepper drivers
 */

#include "pins_MKS_BASE_15.h" // ... MKS_BASE_common ... RAMPS

/**
 * Some new boards use HR4982 (Heroic) instead of the A4982 (Allegro) stepper drivers.
 * Most the functionality is similar, the HR variant obviously doesn't work with diode
 * smoothers (no fast decay). And the Heroic has a 128 µStepping mode where the A4982
 * is doing quarter steps (MS1=0, MS2=1).
 */
#define HEROIC_STEPPER_DRIVERS

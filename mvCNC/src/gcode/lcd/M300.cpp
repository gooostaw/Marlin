/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if HAS_BUZZER

#include "../gcode.h"

#include "../../lcd/mvcncui.h" // i2c-based BUZZ
#include "../../libs/buzzer.h"  // Buzzer, if possible

/**
 * M300: Play beep sound S<frequency Hz> P<duration ms>
 */
void GcodeSuite::M300() {
  uint16_t const frequency = parser.ushortval('S', 260);
  uint16_t duration = parser.ushortval('P', 1000);

  // Limits the tone duration to 0-5 seconds.
  NOMORE(duration, 5000U);

  BUZZ(duration, frequency);
}

#endif // HAS_BUZZER

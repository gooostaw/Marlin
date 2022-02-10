/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/MarlinConfigPre.h"

#if ANY(COOLANT_MIST, COOLANT_FLOOD, AIR_ASSIST)

#include "../gcode.h"
#include "../../module/planner.h"

#if ENABLED(COOLANT_MIST)
  /**
   * M7: Mist Coolant On
   */
  void GcodeSuite::M7() {
    planner.synchronize();                            // Wait for move to arrive
    WRITE(COOLANT_MIST_PIN, !(COOLANT_MIST_INVERT));  // Turn on Mist coolant
  }
#endif

#if EITHER(COOLANT_FLOOD, AIR_ASSIST)

  #if ENABLED(AIR_ASSIST)
    #include "../../feature/spindle_laser.h"
  #endif

  /**
   * M8: Flood Coolant / Air Assist ON
   */
  void GcodeSuite::M8() {
    planner.synchronize();                            // Wait for move to arrive
    #if ENABLED(COOLANT_FLOOD)
      WRITE(COOLANT_FLOOD_PIN, !(COOLANT_FLOOD_INVERT)); // Turn on Flood coolant
    #endif
    #if ENABLED(AIR_ASSIST)
      cutter.air_assist_enable();                     // Turn on Air Assist
    #endif
  }

#endif

/**
 * M9: Coolant / Air Assist OFF
 */
void GcodeSuite::M9() {
  planner.synchronize();                              // Wait for move to arrive
  #if ENABLED(COOLANT_MIST)
    WRITE(COOLANT_MIST_PIN, COOLANT_MIST_INVERT);     // Turn off Mist coolant
  #endif
  #if ENABLED(COOLANT_FLOOD)
    WRITE(COOLANT_FLOOD_PIN, COOLANT_FLOOD_INVERT);   // Turn off Flood coolant
  #endif
  #if ENABLED(AIR_ASSIST)
    cutter.air_assist_disable();                      // Turn off Air Assist
  #endif
}

#endif // COOLANT_MIST | COOLANT_FLOOD | AIR_ASSIST

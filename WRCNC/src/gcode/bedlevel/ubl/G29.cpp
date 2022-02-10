/**
 * Webber Ranch CNC Firmware
*/

/**
 * G29.cpp - Unified Bed Leveling
 */

#include "../../../inc/WRCNCConfig.h"

#if ENABLED(AUTO_BED_LEVELING_UBL)

#include "../../gcode.h"
#include "../../../feature/bedlevel/bedlevel.h"

#if ENABLED(REPORT_STATUS_TO_HOST)
  #include "../../../module/motion.h"
#endif

void GcodeSuite::G29() {

  TERN_(REPORT_STATUS_TO_HOST, set_and_report_grblstate(M_PROBE));

  ubl.G29();

  TERN_(REPORT_STATUS_TO_HOST, set_and_report_grblstate(M_IDLE));
}

#endif // AUTO_BED_LEVELING_UBL

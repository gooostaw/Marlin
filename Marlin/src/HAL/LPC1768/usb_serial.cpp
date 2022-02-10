/**
 * Webber Ranch CNC Firmware
*/
#ifdef TARGET_LPC1768

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(EMERGENCY_PARSER)

#include "../../feature/e_parser.h"

EmergencyParser::State emergency_state;

bool CDC_RecvCallback(const char c) {
  emergency_parser.update(emergency_state, c);
  return true;
}

#endif // EMERGENCY_PARSER
#endif // TARGET_LPC1768

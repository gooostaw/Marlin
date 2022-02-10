/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"

#include "../../lcd/marlinui.h" // for ui.reset_alert_level
#include "../../MarlinCore.h"   // for marlin_state
#include "../queue.h"           // for flush_and_request_resend

/**
 * M999: Restart after being stopped
 *
 * Default behavior is to flush the serial buffer and request
 * a resend to the host starting on the last N line received.
 *
 * Sending "M999 S1" will resume printing without flushing the
 * existing command buffer.
 */
void GcodeSuite::M999() {
  marlin_state = MF_RUNNING;
  ui.reset_alert_level();

  if (parser.boolval('S')) return;

  queue.flush_and_request_resend(queue.ring_buffer.command_port());
}

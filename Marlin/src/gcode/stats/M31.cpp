/**
 * Webber Ranch CNC Firmware
*/

#include "../gcode.h"
#include "../../core/serial.h"
#include "../../module/printcounter.h"
#include "../../libs/duration_t.h"
#include "../../lcd/marlinui.h"

/**
 * M31: Get the time since the start of SD Print (or last M109)
 */
void GcodeSuite::M31() {
  char buffer[22];
  duration_t(print_job_timer.duration()).toString(buffer);

  ui.set_status(buffer);

  SERIAL_ECHO_MSG("Print time: ", buffer);
}

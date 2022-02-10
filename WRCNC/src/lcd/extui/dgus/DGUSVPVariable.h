/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <stdint.h>

/**
 * DGUSVPVariable.h
 *
 *  Created on: Feb 9, 2019
 *      Author: tobi
 */

struct DGUS_VP_Variable {
  uint16_t VP;
  void*    memadr;  // If nullptr, the value cannot be uploaded to the display.
  uint8_t  size;

  // Callback that will be called if the display modified the value.
  // nullptr makes it readonly for the display.
  void (*set_by_display_handler)(DGUS_VP_Variable &var, void *val_ptr);
  void (*send_to_display_handler)(DGUS_VP_Variable &var);

  template<typename T>
  DGUS_VP_Variable& operator =(T &o) {
    *(T*)memadr = o;  // warning this is not typesafe.
    // TODO: Call out the display or mark as dirty for the next update.
    return *this;
  }
};

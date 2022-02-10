/**
 * Webber Ranch CNC Firmware
*/
#pragma once

/**
 * lcd/extui/dgus/DGUSDisplayDef.h
 * Defines the interaction between Marlin and the display firmware
 */

#include "DGUSVPVariable.h"

#include <stdint.h>

// Information on which screen which VP is displayed.
// As this is a sparse table, two arrays are needed:
// one to list the VPs of one screen and one to map screens to the lists.
// (Strictly this would not be necessary, but allows to only send data the display needs and reducing load on Marlin)
struct VPMapping {
  const uint8_t screen;
  const uint16_t *VPList;  // The list is null-terminated.
};

extern const struct VPMapping VPMap[];

// List of VPs handled by Marlin / The Display.
extern const struct DGUS_VP_Variable ListOfVP[];

#include "../../../inc/MarlinConfig.h"

#if ENABLED(DGUS_LCD_UI_ORIGIN)
  #include "origin/DGUSDisplayDef.h"
#elif ENABLED(DGUS_LCD_UI_MKS)
  #include "mks/DGUSDisplayDef.h"
#elif ENABLED(DGUS_LCD_UI_FYSETC)
  #include "fysetc/DGUSDisplayDef.h"
#elif ENABLED(DGUS_LCD_UI_HIPRECY)
  #include "hiprecy/DGUSDisplayDef.h"
#endif

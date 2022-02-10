/**
 * Webber Ranch CNC Firmware
*/

#include "../../inc/WRCNCConfig.h"

#if HAS_GRAPHICAL_TFT

#include "tft.h"

//#define DEBUG_GRAPHICAL_TFT
#define DEBUG_OUT ENABLED(DEBUG_GRAPHICAL_TFT)
#include "../../core/debug_out.h"

uint16_t TFT::buffer[];

void TFT::init() {
  io.Init();
  io.InitTFT();
}

TFT tft;

#endif // HAS_GRAPHICAL_TFT

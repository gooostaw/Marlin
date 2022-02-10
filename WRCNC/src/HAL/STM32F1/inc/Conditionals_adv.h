/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef USE_USB_COMPOSITE
  //#warning "SD_CHECK_AND_RETRY isn't needed with USE_USB_COMPOSITE."
  #undef SD_CHECK_AND_RETRY
  #if DISABLED(NO_SD_HOST_DRIVE)
    #define HAS_SD_HOST_DRIVE 1
  #endif
#endif

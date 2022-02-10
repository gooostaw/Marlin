/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include "../inc/WRCNCConfig.h"
#include "../module/probe.h"

#if !WITHIN(TRAMMING_SCREW_THREAD, 30, 51) || TRAMMING_SCREW_THREAD % 10 > 1
  #error "TRAMMING_SCREW_THREAD must be equal to 30, 31, 40, 41, 50, or 51."
#endif

constexpr xy_pos_t tramming_points[] = TRAMMING_POINT_XY;

#define G35_PROBE_COUNT COUNT(tramming_points)
static_assert(WITHIN(G35_PROBE_COUNT, 3, 6), "TRAMMING_POINT_XY requires between 3 and 6 XY positions.");

#define VALIDATE_TRAMMING_POINT(N) static_assert(N >= G35_PROBE_COUNT || Probe::build_time::can_reach(tramming_points[N]), \
  "TRAMMING_POINT_XY point " STRINGIFY(N) " is not reachable with the default NOZZLE_TO_PROBE offset and PROBING_MARGIN.")
VALIDATE_TRAMMING_POINT(0); VALIDATE_TRAMMING_POINT(1); VALIDATE_TRAMMING_POINT(2); VALIDATE_TRAMMING_POINT(3); VALIDATE_TRAMMING_POINT(4); VALIDATE_TRAMMING_POINT(5);

extern const char point_name_1[], point_name_2[], point_name_3[]
  #ifdef TRAMMING_POINT_NAME_4
    , point_name_4[]
    #ifdef TRAMMING_POINT_NAME_5
      , point_name_5[]
      #ifdef TRAMMING_POINT_NAME_6
        , point_name_6[]
      #endif
    #endif
  #endif
;

#define _NR_TRAM_NAMES 2
#ifdef TRAMMING_POINT_NAME_3
  #undef _NR_TRAM_NAMES
  #define _NR_TRAM_NAMES 3
  #ifdef TRAMMING_POINT_NAME_4
    #undef _NR_TRAM_NAMES
    #define _NR_TRAM_NAMES 4
    #ifdef TRAMMING_POINT_NAME_5
      #undef _NR_TRAM_NAMES
      #define _NR_TRAM_NAMES 5
      #ifdef TRAMMING_POINT_NAME_6
        #undef _NR_TRAM_NAMES
        #define _NR_TRAM_NAMES 6
      #endif
    #endif
  #endif
#endif
static_assert(_NR_TRAM_NAMES >= G35_PROBE_COUNT, "Define enough TRAMMING_POINT_NAME_s for all TRAMMING_POINT_XY entries.");
#undef _NR_TRAM_NAMES

extern PGM_P const tramming_point_name[];

#ifdef ASSISTED_TRAMMING_WAIT_POSITION
  void move_to_tramming_wait_pos();
#else
  inline void move_to_tramming_wait_pos() {}
#endif

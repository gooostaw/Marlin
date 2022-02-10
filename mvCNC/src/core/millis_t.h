/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <stdint.h>

typedef uint32_t millis_t;

#define SEC_TO_MS(N) millis_t((N)*1000UL)
#define MIN_TO_MS(N) SEC_TO_MS((N)*60UL)
#define MS_TO_SEC(N) millis_t((N)/1000UL)

#define PENDING(NOW,SOON) ((int32_t)(NOW-(SOON))<0)
#define ELAPSED(NOW,SOON) (!PENDING(NOW,SOON))

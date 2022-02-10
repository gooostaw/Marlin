/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;

#define DEFAULT_WIFI_HOSTNAME "wrcnc"

void wifi_init();

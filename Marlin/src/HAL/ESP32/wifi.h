/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;

#define DEFAULT_WIFI_HOSTNAME "marlin"

void wifi_init();

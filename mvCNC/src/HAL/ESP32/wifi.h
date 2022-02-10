/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;

#define DEFAULT_WIFI_HOSTNAME "mvcnc"

void wifi_init();

/**
 * Webber Ranch CNC Firmware
*/
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/WRCNCConfigPre.h"

#if BOTH(WIFISUPPORT, WEBSUPPORT)

#include "../../inc/WRCNCConfig.h"

#undef DISABLED  // esp32-hal-gpio.h
#include <SPIFFS.h>
#include "wifi.h"

AsyncEventSource events("/events"); // event source (Server-Sent events)

void onNotFound(AsyncWebServerRequest *request) {
  request->send(404);
}

void web_init() {
  server.addHandler(&events);       // attach AsyncEventSource
  server.serveStatic("/", SPIFFS, "/www").setDefaultFile("index.html");
  server.onNotFound(onNotFound);
}

#endif // WIFISUPPORT && WEBSUPPORT
#endif // ARDUINO_ARCH_ESP32

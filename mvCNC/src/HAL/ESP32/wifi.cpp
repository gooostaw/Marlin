/**
 * Modern Vintage CNC Firmware
*/
#ifdef ARDUINO_ARCH_ESP32

#include "../../core/serial.h"
#include "../../inc/mvCNCConfigPre.h"

#if ENABLED(WIFISUPPORT)

#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include "wifi.h"

AsyncWebServer server(80);

#ifndef WIFI_HOSTNAME
  #define WIFI_HOSTNAME DEFAULT_WIFI_HOSTNAME
#endif

void wifi_init() {

  SERIAL_ECHO_MSG("Starting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    SERIAL_ERROR_MSG("Unable to connect to WiFi with SSID '" WIFI_SSID "', restarting.");
    delay(5000);
    ESP.restart();
  }

  delay(10);
  if (!MDNS.begin(WIFI_HOSTNAME)) {
    SERIAL_ERROR_MSG("Unable to start mDNS with hostname '" WIFI_HOSTNAME "', restarting.");
    delay(5000);
    ESP.restart();
  }

  MDNS.addService("http", "tcp", 80);

  SERIAL_ECHOLNPGM("Successfully connected to WiFi with SSID '" WIFI_SSID "', hostname: '" WIFI_HOSTNAME "', IP address: ", WiFi.localIP().toString().c_str());
}

#endif // WIFISUPPORT
#endif // ARDUINO_ARCH_ESP32

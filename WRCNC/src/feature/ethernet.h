/**
 * Webber Ranch CNC Firmware
*/
#pragma once

#ifdef __IMXRT1062__
  #include <NativeEthernet.h>
#endif

// Teensy 4.1 uses internal MAC Address

class WRCNCEthernet {
  public:
    static bool hardware_enabled, have_telnet_client;
    static IPAddress ip, myDns, gateway, subnet;
    static EthernetClient telnetClient;
    static void init();
    static void check();
};

extern WRCNCEthernet ethernet;
